// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/LockedDoor.h"
#include "Door/LockedDoorInteractionComponent.h"

void ALockedDoor::InitInteractionComponent()
{
	InteractionComponent = NewObject<ULockedDoorInteractionComponent>(this, TEXT("InteractionComponent"));
	InteractionComponent->RegisterComponent();

	InteractionComponent->ObjectDescriptionToDisplay = INVTEXT("Door");
	InteractionComponent->InteractActionToDisplay = INVTEXT("unlock");
}

void ALockedDoor::ChangeState()
{
	if(State == DoorState::Closed && bIsLocked)
	{
		return;
	}

	Super::ChangeState();
}

bool ALockedDoor::Unlock(DoorKeyType KeyType)
{
	if (KeyType == UnlockedBy)
	{
		bIsLocked = false;
		InteractionComponent->InteractActionToDisplay = INVTEXT("open");

		return true;
	}

	return false;
}

DoorKeyType ALockedDoor::GetUnlockedBy() const
{
	return UnlockedBy;
}
