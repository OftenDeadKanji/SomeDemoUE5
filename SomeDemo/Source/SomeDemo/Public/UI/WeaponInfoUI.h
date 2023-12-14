// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API UWeaponInfoUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo);

	UFUNCTION(BlueprintCallable)
	void SetWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerWeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerAmmo;
};
