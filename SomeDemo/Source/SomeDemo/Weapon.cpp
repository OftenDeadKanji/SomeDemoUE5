// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Damageable.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WeaponProperties.CurrentShotCooldown > 0.0f)
	{
		WeaponProperties.CurrentShotCooldown -= DeltaTime;
	}
}

void UWeapon::Fire()
{
	if (WeaponProperties.CurrentShotCooldown > 0.0f)
	{
		return;
	}
	
	if (WeaponProperties.ClipAmmo == 0)
	{
		//play "no ammo in clip" sound
		return;
	}
	
	FVector location = GetComponentLocation();
	FVector forward = GetForwardVector();
	
	auto* world = GetWorld();
	
	FHitResult hitResult;
	if (world->LineTraceSingleByChannel(hitResult, location, location + forward * 10000.0f, ECollisionChannel::ECC_Visibility))
	{
		if (auto* damageable = Cast<IDamageable>(hitResult.GetActor()))
		{
			damageable->DoDamage(WeaponProperties.BaseDamagePerShot);
	
			WeaponProperties.CurrentShotCooldown = WeaponProperties.TimeBetweenShots;
		}
	}
}

void UWeapon::Reload()
{
	if (WeaponProperties.LeftAmmo == 0 || WeaponProperties.ClipAmmo == WeaponProperties.ClipSize)
	{
		return;
	}
	
	int32 ammoToFillClip = WeaponProperties.ClipSize - WeaponProperties.ClipAmmo;
	if (WeaponProperties.LeftAmmo < ammoToFillClip)
	{
		ammoToFillClip = WeaponProperties.LeftAmmo;
	}
	
	WeaponProperties.LeftAmmo -= ammoToFillClip;
	WeaponProperties.ClipAmmo += ammoToFillClip;
}

void UWeapon::Initialize(FWeaponProperties& Properties)
{
	WeaponProperties = Properties;
}
