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
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerHUD = CreateWidget<UMainPlayerHUD>(PC, PlayerHUDClass);
	PlayerHUD->AddToPlayerScreen();

	if (EquippedWeaponActor == nullptr)
	{
		PlayerHUD->PlayerWeaponName->SetText(FText::FromString(TEXT("")));
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		PlayerHUD->PlayerWeaponName->SetText(FText::FromString(EquippedWeaponActor->GetWeaponName()));
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo)));
	}
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MainPlayer_MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MainPlayer_MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("MainPlayer_Turn", this, &AMainPlayer::Turn);
	PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainPlayer::LookUp);

	PlayerInputComponent->BindAction("MainPlayer_Fire", IE_Pressed, this, &AMainPlayer::Fire);
	PlayerInputComponent->BindAction("MainPlayer_Reload", IE_Pressed, this, &AMainPlayer::Reload);
	PlayerInputComponent->BindAction("MainPlayer_SetItem1", IE_Pressed, this, &AMainPlayer::SetItem1);

}

void AMainPlayer::AddWeapon(FWeaponInstance Weapon)
{
	Weapons.Add(Weapon);
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
		bool fired = EquippedWeaponActor->Fire(Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo);
		if (fired)
		{
			PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo)));
		}
	}
}

void AMainPlayer::Reload()
{
	if (EquippedWeaponActor)
	{
		EquippedWeaponActor->Reload(Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo);
		PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo)));
	}
}

void AMainPlayer::SetItem1()
{
	if(EquippedWeaponActor == nullptr)
	{
		if (Weapons.Num() > 0)
		{
			auto* World = GetWorld();

			FVector location = WeaponLocation->GetRelativeLocation();
			FRotator rotation = WeaponLocation->GetRelativeRotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = this;
			AWeapon* spawned = Cast<AWeapon>(World->SpawnActor(Weapons[0].WeaponClass, &location, &rotation, SpawnParams));
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
			}

			EquippedWeaponInstanceIndex = 0;

			PlayerHUD->PlayerWeaponName->SetText(FText::FromString(EquippedWeaponActor->GetWeaponName()));
			PlayerHUD->PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Weapons[EquippedWeaponInstanceIndex].CurrentClipAmmo, Weapons[EquippedWeaponInstanceIndex].CurrentRemainingAmmo)));
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
