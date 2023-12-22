// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Damageable/Damageable.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AWeapon::Fire(int32& ClipAmmo, int32& Ammo)
{
	if (ClipAmmo > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FireSound, Volume);
		ClipAmmo -= 1;

		FHitResult hit;
		FVector StartLocation = UKismetMathLibrary::TransformLocation(GetTransform(), ShotStartRelativeLocation);
		FVector Direction = UKismetMathLibrary::TransformDirection(GetTransform(), RelativeDirection);

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(OwnerActor);
		if (GetWorld()->LineTraceSingleByChannel(hit, StartLocation, StartLocation + Direction * MaxRange, ECollisionChannel::ECC_Camera, CollisionParams))
		{
			auto* hitActor = hit.GetActor();
			if (IDamageable* damageable = Cast<IDamageable>(hitActor))
			{
				damageable->Execute_DoDamage(hitActor, OwnerActor, BaseDamage);
			}
		}

		return true;
	}

	return false;
}

void AWeapon::Reload(int32& ClipAmmo, int32& Ammo)
{
	int32 AmmoToAddToClip = ClipSize - ClipAmmo;
	AmmoToAddToClip = FMath::Min(AmmoToAddToClip, Ammo);

	ClipAmmo += AmmoToAddToClip;
	Ammo -= AmmoToAddToClip;
}

void AWeapon::SetShotStartRelativeLocation(FVector RelativeLocation)
{
	ShotStartRelativeLocation = RelativeLocation;
}

void AWeapon::SetShotStartRelativeDirection(FVector Direction)
{
	RelativeDirection = Direction;
}

void AWeapon::SetOwnerActor(AActor* Actor)
{
	OwnerActor = Actor;
}

const FText& AWeapon::GetWeaponName() const
{
	return Name;
}

UStaticMesh* AWeapon::GetWeaponMesh()
{
	return Mesh->GetStaticMesh();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
