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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
		class UTextBlock* PlayerWeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
		class UTextBlock* PlayerAmmo;
};
