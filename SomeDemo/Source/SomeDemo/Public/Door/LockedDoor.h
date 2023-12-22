// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door/Door.h"
#include "Door/DoorKey.h"
#include "LockedDoor.generated.h"

//class ADoorKey;

/**
 * 
 */
UCLASS(Blueprintable)
class SOMEDEMO_API ALockedDoor : public ADoor
{
	GENERATED_BODY()
	
protected:
	virtual void InitInteractionComponent();

public:
	virtual void ChangeState() override;
	bool Unlock(DoorKeyType KeyType);

	DoorKeyType GetUnlockedBy() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bIsLocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	DoorKeyType UnlockedBy = DoorKeyType::Universal;
};
