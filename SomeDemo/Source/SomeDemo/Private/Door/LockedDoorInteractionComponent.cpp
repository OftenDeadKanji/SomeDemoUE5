// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/LockedDoorInteractionComponent.h"
#include "Door/LockedDoor.h"
#include "Characters/MainPlayer/MainPlayer.h"
#include "Inventory/Inventory.h"
#include "Inventory/InventoryItem_Base.h"
#include "Inventory/InventoryItem_DoorKey.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD_Level1HUD.h"

void ULockedDoorInteractionComponent::BeginPlay()
{
	OwnerLockedDoor = Cast<ALockedDoor>(GetOwner());
}

void ULockedDoorInteractionComponent::InteractInternal_Implementation(AActor* InteractingActor)
{
	auto* Player = Cast<AMainPlayer>(InteractingActor);
	if (!Player)
	{
		return;
	}

	if (TryToUnlockDoor(Player))
	{
		Door->ChangeState();
	}
	else
	{
		ShowMissingKeyMessage();
	}
}

bool ULockedDoorInteractionComponent::TryToUnlockDoor(const AMainPlayer* Player)
{
	const auto* PlayerInventory = Player->GetInventory();
	const auto& InventoryItems = PlayerInventory->GetItems();
	
	for (const auto* Item : InventoryItems)
	{
		if (const auto* DoorKey = Cast<UInventoryItem_DoorKey>(Item))
		{
			auto KeyType = DoorKey->GetDoorKeyType();
			if (KeyType == OwnerLockedDoor->GetUnlockedBy())
			{
				OwnerLockedDoor->Unlock(KeyType);
				return true;
			}
		}
	}

	return false;
}

void ULockedDoorInteractionComponent::ShowMissingKeyMessage()
{
	auto RequiredKeyType = OwnerLockedDoor->GetUnlockedBy();
	FText RequiredKeyTypeAsFText = DoorKeyTypeToFText(RequiredKeyType);

	FText Message = FText::Format(INVTEXT("{0} key is missing."), RequiredKeyTypeAsFText);

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto* HUD = PC->GetHUD();
	if (auto* Level1HUD = Cast<AHUD_Level1HUD>(HUD))
	{
		Level1HUD->ShowMessage(Message);
	}
}
