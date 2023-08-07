// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	//EquippedWeapon = CreateDefaultSubobject<UWeapon>(TEXT("Weapon"));
	//EquippedWeapon->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Size: %d"), sizeof(UActorComponent));
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MainPlayer_MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MainPlayer_MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("MainPlayer_Turn", this, &AMainPlayer::Turn);
	PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainPlayer::LookUp);

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
	if (bUsesWeapon)
	{
		EquippedWeapon->Fire();
	}
}

void AMainPlayer::Reload()
{
	if (bUsesWeapon)
	{
		EquippedWeapon->Reload();
	}
}

void AMainPlayer::SetItem1()
{
	if (Weapons.Num() > 0)
	{
		EquippedWeapon = CreateDefaultSubobject<UWeapon>(TEXT("Weapon"));
		EquippedWeapon->SetupAttachment(RootComponent);
		
		EquippedWeapon->Initialize(Weapons[0]);
	}
}

