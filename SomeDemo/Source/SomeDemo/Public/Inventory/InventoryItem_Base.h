// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem_Base.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SOMEDEMO_API UInventoryItem_Base : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bStackable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count = 1;
};
