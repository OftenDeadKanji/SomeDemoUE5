// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "Components/SphereComponent.h"
#include "../Characters/MainPlayer.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PickupArea = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Area"));
	PickupArea->SetupAttachment(Root);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(Root);	
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
	PickupArea->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapBegin);

	if (WeaponToPickup.WeaponClass)
	{
		if (auto* weapon = Cast<AWeapon>(WeaponToPickup.WeaponClass->GetDefaultObject()))
		{
			WeaponMesh->SetStaticMesh(weapon->GetWeaponMesh());
		}
	}

	StartingZ = GetActorLocation().Z;
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float heightDelta = FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * FloatHeight;
	
	FVector location = GetActorLocation();
	location.Z = StartingZ + heightDelta;
	SetActorLocation(location);

	FRotator rotation = GetActorRotation();
	rotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(rotation);
}

void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* player = Cast<AMainPlayer>(OtherActor))
	{
		player->AddWeapon(WeaponToPickup);
	}

	GetWorld()->DestroyActor(this);
}

