// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItem_Base.h"
#include "Door/DoorKey.h"
#include "InventoryItem_DoorKey.generated.h"

class ADoorKey;
/**
 * 
 */
UCLASS()
class SOMEDEMO_API UInventoryItem_DoorKey : public UInventoryItem_Base
{
	GENERATED_BODY()

	friend ADoorKey;
public:

	DoorKeyType GetDoorKeyType() const;
protected:
	DoorKeyType Type;
};
