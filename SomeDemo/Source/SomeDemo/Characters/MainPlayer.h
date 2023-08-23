// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/WeaponInstance.h"
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

	UFUNCTION(BlueprintCallable)
	void AddWeapon(FWeaponInstance Weapon);
	
	void ToggleGamePause();

	UFUNCTION(BlueprintCallable)
	bool ShowMessage(FString Message);
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Fire();
	void Reload();

	void SetItem1();

	void UpdateWeaponInfoUI();

	void UpdateMessage(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookUpLimitMin = -89.99f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookUpLimitMax = 89.99f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	class UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FWeaponInstance Weapon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FWeaponInstance Weapon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FWeaponInstance Weapon3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	class AWeapon* EquippedWeaponActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	int32 EquippedWeaponInstanceIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class USceneComponent* WeaponLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class USceneComponent* WeaponShotStartLocation;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UMainPlayerHUD> PlayerHUDClass;
	UPROPERTY()
	class UMainPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UGamePauseUI> GamePauseUIClass;
	UPROPERTY()
	class UGamePauseUI* GamePauseUI;

	bool bIsGamePauseScreenOn = false;

//public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float MessageMaxTime = 5.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageCurrentTime = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageAppearTime = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageDisappearTime = 1.0f;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	//FString Message;
};
