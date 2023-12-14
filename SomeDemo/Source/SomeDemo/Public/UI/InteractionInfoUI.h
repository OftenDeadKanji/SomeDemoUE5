// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionInfoUI.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SOMEDEMO_API UInteractionInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetInteractionInfo(const FText& InteractiveObjectInfo, const FText& PlayerInteractActionInfo);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InteractiveObjectInfoText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerInteractActionInfoText;
};
