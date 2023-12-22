// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionComponent.h"
#include "DoorInteractionComponent.generated.h"

class ADoor;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class SOMEDEMO_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()
	
	friend ADoor;
protected:
	virtual void BeginPlay() override;

public:
	virtual void InteractInternal_Implementation(class AActor* InteractingActor) override;

protected:
	ADoor* Door;
};
