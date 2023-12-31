// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Level1HUD.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API AHUD_Level1HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_Level1HUD();

protected:
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ShowInteractionInfo(const FText& InteractiveObjectInfo, const FText& PlayerInteractActionInfo);
	UFUNCTION(BlueprintCallable)
	void HideInteractionInfo();

	UFUNCTION(BlueprintCallable)
	bool ShowMessage(const FText& Message, float MainTime = 3.0f, float AppearTime = 1.0f, float DisappearTime = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ShowWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo);
	UFUNCTION(BlueprintCallable)
	void HideWeaponInfo();
	UFUNCTION(BlueprintCallable)
	void UpdateWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo);

	UFUNCTION(BlueprintCallable)
	void ShowPauseScreen();
	UFUNCTION(BlueprintCallable)
	void HidePauseScreen();

protected:
	class AMainPlayerController* OwningPlayerController;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class UPlayerInfoUI> PlayerInfoUIClass;
	UPROPERTY()
	class UPlayerInfoUI* PlayerInfoUI;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class UInteractionInfoUI> InteractionInfoUIClass;
	UPROPERTY()
	class UInteractionInfoUI* InteractionInfoUI;
	
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class UWeaponInfoUI> WeaponInfoUIClass;
	UPROPERTY()
	class UWeaponInfoUI* WeaponInfoUI;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class UMessageUI> MessageUIClass;
	UPROPERTY()
	class UMessageUI* MessageUI;
	
	UFUNCTION()
	void OnMessageCompleted();

	UPROPERTY(EditAnywhere, Category = "Pause Screen")
	TSubclassOf<class UGamePauseUI> GamePauseUIClass;
	UPROPERTY()
	class UGamePauseUI* GamePauseUI;
};
