// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "DoorKey.generated.h"

class UInventoryItem_DoorKey;
class UDoorKeyInteractionComponent;

UENUM(BlueprintType)
enum class DoorKeyType
{
	Universal,
	Brass
};

FText DoorKeyTypeToFText(DoorKeyType Type);

UCLASS(Blueprintable)
class SOMEDEMO_API ADoorKey : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	ADoorKey();

	DoorKeyType GetType() const;

	void GetInventoryItemData(UInventoryItem_DoorKey* Item) const;
protected:
	UPROPERTY(VisibleAnywhere)
	UDoorKeyInteractionComponent* InteractionComponent;

	UPROPERTY(EditInstanceOnly, Category = "Gameplay")
	DoorKeyType Type;
};
