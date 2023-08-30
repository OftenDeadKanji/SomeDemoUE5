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
	AMainPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddWeapon(FWeaponInstance Weapon);
	

	UFUNCTION(BlueprintCallable)
	bool ShowMessage(FText Message);

#pragma region Inputs
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);
	UFUNCTION(BlueprintCallable)
	void Turn(float Value);
	UFUNCTION(BlueprintCallable)
	void LookUp(float Value);

	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void SetItem1();

	UFUNCTION(BlueprintCallable)
	void Interact();
	UFUNCTION(BlueprintCallable)
	void ToggleGamePause();

#pragma endregion
protected:
	void UpdateWeaponInfoUI();

	void UpdateLineTracedActor();
	void UpdateMessage(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookUpLimitMin = -89.99f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float LookUpLimitMax = 89.99f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	class UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	class AActor* LineTracedActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	class UInteractionComponent* LineTracedInteractionComponent;

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
	TSubclassOf<class UInteractionInfoUI> InteractionInfoUIClass;
	UPROPERTY()
	class UInteractionInfoUI* InteractionInfoUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UMainPlayerHUD> PlayerHUDClass;
	UPROPERTY()
	class UMainPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UGamePauseUI> GamePauseUIClass;
	UPROPERTY()
	class UGamePauseUI* GamePauseUI;

	bool bIsGamePauseScreenOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float MessageMaxTime = 5.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageCurrentTime = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageAppearTime = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float MessageDisappearTime = 1.0f;
};
