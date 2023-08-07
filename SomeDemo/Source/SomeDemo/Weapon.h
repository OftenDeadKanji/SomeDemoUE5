// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"


USTRUCT(BlueprintType)
struct FWeaponProperties
{
	GENERATED_BODY()
public:
	UPROPERTY()
		float TimeBetweenShots;
	UPROPERTY()
		float CurrentShotCooldown;
	UPROPERTY()
		bool bIsHitScan = true;
	UPROPERTY()
		float BaseDamagePerShot = true;
	UPROPERTY()
		int32 ClipAmmo;
	UPROPERTY()
		int32 LeftAmmo;
	UPROPERTY()
		int32 ClipSize;
	UPROPERTY()
		int32 MaxAmmo;

	UPROPERTY()
		class UStaticMeshComponent* Mesh;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEDEMO_API UWeapon : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Fire();
	UFUNCTION(BlueprintCallable)
		void Reload();

	UFUNCTION(BlueprintCallable)
		void Initialize(FWeaponProperties& Properties);
protected:
	//UPROPERTY(EditAnywhere)
	//	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FWeaponProperties WeaponProperties;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//	FVector ShotStartLocation;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//	float TimeBetweenShots;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//	float CurrentShotCooldown;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//	bool bIsHitScan = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//	float BaseDamagePerShot = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
	//	int32 ClipAmmo;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
	//	int32 LeftAmmo;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
	//	int32 ClipSize;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
	//	int32 MaxAmmo;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class UStaticMeshComponent* ProjectileMesh;
	//Animation
	//Sound
};
