// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Inventory/Inventory.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "../MainPlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../GamePauseUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Location"));
	WeaponLocation->SetupAttachment(FirstPersonCamera);

	WeaponShotStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Shot Start Location"));
	WeaponShotStartLocation->SetupAttachment(FirstPersonCamera);

	PlayerHUD = nullptr;
	PlayerHUDClass = nullptr;

	GamePauseUI = nullptr;
	GamePauseUIClass = nullptr;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerHUD = CreateWidget<UMainPlayerHUD>(PC, PlayerHUDClass);
	PlayerHUD->AddToPlayerScreen();

	UpdateWeaponInfoUI();
	PlayerHUD->Message->SetRenderOpacity(0.0f);
	MessageCurrentTime = MessageMaxTime;

	GamePauseUI = CreateWidget<UGamePauseUI>(PC, GamePauseUIClass, FName(TEXT("GamePauseUI")));
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMessage(DeltaTime);
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("MainPlayer_MoveForward", this, &AMainPlayer::MoveForward);
	//PlayerInputComponent->BindAxis("MainPlayer_MoveRight", this, &AMainPlayer::MoveRight);
	//PlayerInputComponent->BindAxis("MainPlayer_Turn", this, &AMainPlayer::Turn);
	//PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainPlayer::LookUp);
	//
	//PlayerInputComponent->BindAction("MainPlayer_Fire", IE_Pressed, this, &AMainPlayer::Fire);
	//PlayerInputComponent->BindAction("MainPlayer_Reload", IE_Pressed, this, &AMainPlayer::Reload);
	//PlayerInputComponent->BindAction("MainPlayer_SetItem1", IE_Pressed, this, &AMainPlayer::SetItem1);
	//
	//auto& binding = PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &AMainPlayer::ToggleGamePause);
}

void AMainPlayer::AddWeapon(FWeaponInstance Weapon)
{
	if (Weapon.WeaponClass != Weapon1.WeaponClass && Weapon.WeaponClass != Weapon2.WeaponClass && Weapon.WeaponClass != Weapon3.WeaponClass)
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
			PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo)));
		}
	}
}

void AMainPlayer::Reload()
{
	if (EquippedWeaponActor)
	{
		FWeaponInstance& Instance = EquippedWeaponInstanceIndex == 0 ? Weapon1 : EquippedWeaponInstanceIndex == 1 ? Weapon2 : Weapon3;

		EquippedWeaponActor->Reload(Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo);
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo)));
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

				PlayerHUD->PlayerWeaponName->SetText(FText::FromString(EquippedWeaponActor->GetWeaponName()));
				PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Weapon1.CurrentClipAmmo, Weapon1.CurrentRemainingAmmo)));
			}
		}
	}
	else
	{
		GetWorld()->DestroyActor(EquippedWeaponActor);
		EquippedWeaponActor = nullptr;

		EquippedWeaponInstanceIndex = -1;

		PlayerHUD->PlayerWeaponName->SetText(FText::FromString(TEXT("")));
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(TEXT("")));
	}

}

void AMainPlayer::UpdateWeaponInfoUI()
{
	if (EquippedWeaponActor == nullptr)
	{
		PlayerHUD->PlayerWeaponName->SetText(FText::FromString(TEXT("")));
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		PlayerHUD->PlayerWeaponName->SetText(FText::FromString(EquippedWeaponActor->GetWeaponName()));

		FWeaponInstance& Instance = EquippedWeaponInstanceIndex == 0 ? Weapon1 : EquippedWeaponInstanceIndex == 1 ? Weapon2 : Weapon3;
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Instance.CurrentClipAmmo, Instance.CurrentRemainingAmmo)));
	}
}

void AMainPlayer::UpdateMessage(float DelatTime)
{
	if (MessageCurrentTime < MessageMaxTime)
	{
		float Opacity = 1.0f;
		if (MessageCurrentTime < MessageAppearTime)
		{
			Opacity = FMath::Lerp(0.0f, 1.0f, MessageCurrentTime / MessageAppearTime);
		}
		else if (MessageCurrentTime > MessageMaxTime - MessageDisappearTime)
		{
			Opacity = FMath::Lerp(1.0f, 0.0f, (MessageCurrentTime - (MessageMaxTime - MessageDisappearTime)) / MessageDisappearTime);
		}
		
		PlayerHUD->Message->SetRenderOpacity(Opacity);

		MessageCurrentTime += DelatTime;
	}
}

void AMainPlayer::ToggleGamePause()
{
	auto* World = GetWorld();
	auto* PC = UGameplayStatics::GetPlayerController(World, 0);

	if(bIsGamePauseScreenOn)
	{
		GamePauseUI->RemoveFromViewport();
		bIsGamePauseScreenOn = false;

		UGameplayStatics::SetGamePaused(World, false);
		PC->bShowMouseCursor = false;

		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	}
	else
	{
		GamePauseUI->AddToViewport();
		bIsGamePauseScreenOn = true;

		UGameplayStatics::SetGamePaused(World, true);
		PC->bShowMouseCursor = true;

		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
	}
}

bool AMainPlayer::ShowMessage(FText Message)
{
	if (MessageCurrentTime >= MessageMaxTime)
	{
		this->PlayerHUD->Message->SetText(Message);
		MessageCurrentTime = 0.0f;

		return true;
	}

	return false;
}

