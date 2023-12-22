// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionComponent.h"
#include "DoorKeyInteractionComponent.generated.h"

class ADoorKey;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class SOMEDEMO_API UDoorKeyInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void InteractInternal_Implementation(class AActor* InteractingActor) override;

protected:
	ADoorKey* OwnerDoorKey;
};
