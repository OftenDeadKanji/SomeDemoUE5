// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API UPlayerInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* Crosshair;
};
