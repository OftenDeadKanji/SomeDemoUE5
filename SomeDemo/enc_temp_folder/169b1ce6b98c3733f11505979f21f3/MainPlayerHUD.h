// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPlayerHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SOMEDEMO_API UMainPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// Message will be shown for: AppearTime + MessageTimeInSeconds + DisappearTime
	UFUNCTION(BlueprintCallable)
	bool ShowMessage(float MainTime = 3.0f, float AppearTime = 1.0f, float DisappearTime = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ShowWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo);
	UFUNCTION(BlueprintCallable)
	void HideWeaponInfo();

	UFUNCTION(BlueprintCallable)
	void UpdateWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo);
protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerWeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Message;

	UPROPERTY(VisibleAnywhere)
	bool bIsShowingMessage = false;
	UPROPERTY(VisibleAnywhere)
	float MessageCurrentTime;
	UPROPERTY(VisibleAnywhere)
	float MessageMainTime;
	UPROPERTY(VisibleAnywhere)
	float MessageAppearTime;
	UPROPERTY(VisibleAnywhere)
	float MessageDisappearTime;
};
