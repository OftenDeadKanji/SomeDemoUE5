// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "MainPlayer.generated.h"

UCLASS()
class SOMEDEMO_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	
	void Fire();
	void Reload();

	void SetItem1();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float LookUpLimitMin = -89.9f;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float LookUpLimitMax = 89.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bUsesWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class UWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TArray<FWeaponProperties> Weapons;
};
