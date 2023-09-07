// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Inventory/Inventory.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "../../UI/MainPlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../../UI/GamePauseUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../Interaction/InteractionComponent.h"
#include "../../UI/InteractionInfoUI.h"
#include "../../UI/HUD_Level1HUD.h"

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Location"));
	WeaponLocation->SetupAttachment(FirstPersonCamera);

	WeaponShotStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Shot Start Location"));
	WeaponShotStartLocation->SetupAttachment(FirstPersonCamera);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	HUD = PC->GetHUD<AHUD_Level1HUD>();
	check(HUD);

	UpdateWeaponInfoUI();
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLineTracedActor();
}

void AMainPlayer::AddWeapon(FWeaponInstance Weapon)
{
	if (Weapon.WeaponClass != Weapon1.WeaponClass && Weapon.WeaponClass != Weapon2.WeaponClass && Weapon.WeaponClass != Weapon3.WeaponClass) // trying to add weapon that player can't have
	{
		return;
	}

	FWeaponInstance& Instance = Weapon.WeaponClass == Weapon1.WeaponClass ? Weapon1 : Weapon.WeaponClass == Weapon2.WeaponClass ? Weapon2 : Weapon3;

	if (Instance.bIsAvailable)
	{
		Instance.CurrentRemainingAmmo += Weapon.CurrentRemainingAmmo + Weapon.CurrentClipAmmo;

		if (auto* DefaultWeapon = Cast<AWeapon>(Instance.WeaponClass->GetDefaultObject()))
		{
			Instance.CurrentRemainingAmmo = FMath::Min(Instance.CurrentRemainingAmmo, DefaultWeapon->MaxAmmo);
		}
	}
	else
	{
		Instance.bIsAvailable = true;
		Instance.CurrentClipAmmo = Weapon.CurrentClipAmmo;
		Instance.CurrentRemainingAmmo = Weapon.CurrentRemainingAmmo;
	}

	UpdateWeaponInfoUI();
}

void AMainPlayer::MoveForward(float Value)
{
	auto* movementComp = GetMovementComponent();
	if (movementComp)
	{
		movementComp->AddInputVector(GetActorForwardVector() * Value, false);
	}
}

void AMainPlayer::MoveRight(float Value)
{
	auto* movementComp = GetMovementComponent();
	if (movementComp)
	{
		movementComp->AddInputVector(GetActorRightVector() * Value, false);
	}
}

void AMainPlayer::Turn(float Value)
{
	FRotator rotation = GetActorRotation();

	rotation.Yaw += Value;

	SetActorRotation(rotation);
}

void AMainPlayer::LookUp(float Value)
{
	if (FirstPersonCamera)
	{
		auto cameraRotation = FirstPersonCamera->GetRelativeRotation();

		cameraRotation.Pitch = FMath::Clamp(cameraRotation.Pitch + Value, LookUpLimitMin, LookUpLimitMax);

		FirstPersonCamera->SetRelativeRotation(cameraRotation);
	}
}

void AMainPlayer::Fire()
{
	if (EquippedWeaponActor)
	{
		FWeaponInstance& Instance = EquippedWeaponInstanceIndex == 0 ? Weapon1 : EquippedWeaponInstanceIndex == 1 ? Weapon2 : Weapon3;

		bool fired = EquippedWeaponActor->Fire(Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
		if (fired)
		{
			HUD->UpdateWeaponAmmunitionInfo(Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
		}
	}
}

void AMainPlayer::Reload()
{
	if (EquippedWeaponActor)
	{
		FWeaponInstance& Instance = EquippedWeaponInstanceIndex == 0 ? Weapon1 : EquippedWeaponInstanceIndex == 1 ? Weapon2 : Weapon3;

		EquippedWeaponActor->Reload(Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
		HUD->UpdateWeaponAmmunitionInfo(Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
	}
}

void AMainPlayer::SetItem1()
{
	if(EquippedWeaponActor == nullptr)
	{
		if (Weapon1.bIsAvailable)
		{
			auto* World = GetWorld();

			FVector location = WeaponLocation->GetRelativeLocation();
			FRotator rotation = WeaponLocation->GetRelativeRotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = this;
			AWeapon* spawned = Cast<AWeapon>(World->SpawnActor(Weapon1.WeaponClass, &location, &rotation, SpawnParams));
			if (spawned)
			{
				EquippedWeaponActor = spawned;

				FAttachmentTransformRules rulez(EAttachmentRule::KeepRelative, true);

				EquippedWeaponActor->AttachToComponent(FirstPersonCamera, rulez);
				EquippedWeaponActor->SetOwnerActor(this);

				FVector ShotRelativeLocation = UKismetMathLibrary::InverseTransformLocation(EquippedWeaponActor->GetTransform(), FirstPersonCamera->GetComponentLocation());
				EquippedWeaponActor->SetShotStartRelativeLocation(ShotRelativeLocation);

				FVector ShotRelativeDirection = UKismetMathLibrary::InverseTransformDirection(EquippedWeaponActor->GetTransform(), FirstPersonCamera->GetForwardVector());
				EquippedWeaponActor->SetShotStartRelativeDirection(ShotRelativeDirection);

				EquippedWeaponInstanceIndex = 0;

				HUD->ShowWeaponInfo(EquippedWeaponActor->GetWeaponName(), Weapon1.CurrentClipAmmo, Weapon1.CurrentRemainingAmmo);
			}
		}
	}
	else
	{
		GetWorld()->DestroyActor(EquippedWeaponActor);
		EquippedWeaponActor = nullptr;

		EquippedWeaponInstanceIndex = -1;

		HUD->HideWeaponInfo();
	}

}

void AMainPlayer::UpdateWeaponInfoUI()
{
	if (EquippedWeaponActor == nullptr)
	{
		HUD->HideWeaponInfo();
	}
	else
	{
		FWeaponInstance& Instance = EquippedWeaponInstanceIndex == 0 ? Weapon1 : EquippedWeaponInstanceIndex == 1 ? Weapon2 : Weapon3;
		HUD->ShowWeaponInfo(EquippedWeaponActor->GetWeaponName(), Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
	}
}

void AMainPlayer::UpdateLineTracedActor()
{
	auto* World = GetWorld();
	
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	const float TRACE_DISTANCE = 1000.0f;
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetForwardVector() * TRACE_DISTANCE;

	if (World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Camera, CollisionParams))
	{
		LineTracedActor = Hit.GetActor();

		auto* InteractionComp = LineTracedActor->GetComponentByClass(UInteractionComponent::StaticClass());
		LineTracedInteractionComponent = Cast<UInteractionComponent>(InteractionComp);

		bool ShowInteractionInfo = false;

		if (LineTracedInteractionComponent)
		{
			ShowInteractionInfo = LineTracedInteractionComponent->IsInInteractionRange(GetActorLocation());
		}

		if(ShowInteractionInfo)
		{
			HUD->ShowInteractionInfo(LineTracedInteractionComponent->ObjectDescriptionToDisplay, LineTracedInteractionComponent->InteractActionToDisplay);
		}
		else
		{
			HUD->HideInteractionInfo();
		}
	}
}

void AMainPlayer::Interact()
{
	if (LineTracedInteractionComponent)
	{
		LineTracedInteractionComponent->Interact(this, false);
	}
}

void AMainPlayer::ToggleGamePause()
{
	auto* World = GetWorld();
	auto* PC = UGameplayStatics::GetPlayerController(World, 0);

	if(bIsGamePauseScreenOn)
	{
		HUD->HidePauseScreen();
		bIsGamePauseScreenOn = false;
	
		UGameplayStatics::SetGamePaused(World, false);
		PC->bShowMouseCursor = false;
	
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	}
	else
	{
		HUD->ShowPauseScreen();
		bIsGamePauseScreenOn = true;
	
		UGameplayStatics::SetGamePaused(World, true);
		PC->bShowMouseCursor = true;
	
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
	}
}

bool AMainPlayer::ShowMessage(FText Message)
{
	return HUD->ShowMessage(Message, MessageMaxTime - MessageAppearTime - MessageDisappearTime, MessageAppearTime, MessageDisappearTime);
}

