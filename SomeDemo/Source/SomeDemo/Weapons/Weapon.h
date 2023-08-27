// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class SOMEDEMO_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//returns true if fired successfully (had any ammo), false otherwise
	UFUNCTION(BlueprintCallable)
	bool Fire(int32& ClipAmmo, int32& Ammo);
	UFUNCTION(BlueprintCallable)
	void Reload(int32& ClipAmmo, int32& Ammo);

	void SetShotStartRelativeLocation(FVector Location);
	void SetShotStartRelativeDirection(FVector Direction);

	void SetOwnerActor(class AActor* Actor);

	const FString& GetWeaponName() const;

	UStaticMesh* GetWeaponMesh();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bIsHitscan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MaxRange = 10000.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float BaseDamage = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 ClipSize;

	FVector ShotStartRelativeLocation;
	FVector RelativeDirection;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Sound")
	class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Sound")
	float Volume = 1.0f;
};
