// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProperties.h"
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

	UFUNCTION(BlueprintCallable)
		void InitializeWeapon(FWeaponProperties& Properties);

	UFUNCTION(BlueprintCallable)
		void Fire();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bIsHitscan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Sound")
		class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Sound")
		float Volume = 1.0f;
};
