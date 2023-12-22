// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorKeyInteractionComponent.h"
#include "Characters/MainPlayer/MainPlayer.h"
#include "Door/DoorKey.h"
#include "Inventory/InventoryItem_DoorKey.h"
#include "Inventory/Inventory.h"

void UDoorKeyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Owner = GetOwner();
	OwnerDoorKey = Cast<ADoorKey>(Owner);
}

void UDoorKeyInteractionComponent::InteractInternal_Implementation(AActor* InteractingActor)
{
	auto* Player = Cast<AMainPlayer>(InteractingActor);
	if (!Player)
	{
		return;
	}

	UInventoryItem_DoorKey* DoorKeyItem = NewObject<UInventoryItem_DoorKey>(Player, TEXT("DoorKey"));
	Player->GetInventory()->AddItem(DoorKeyItem);
	
	OwnerDoorKey->Destroy();
}
