// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door/DoorInteractionComponent.h"
#include "LockedDoorInteractionComponent.generated.h"

class ALockedDoor;
class AMainPlayer;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class SOMEDEMO_API ULockedDoorInteractionComponent : public UDoorInteractionComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void InteractInternal_Implementation(class AActor* InteractingActor) override;

protected:
	bool TryToUnlockDoor(const AMainPlayer* Player);
	void ShowMissingKeyMessage();

	ALockedDoor* OwnerLockedDoor;
};
