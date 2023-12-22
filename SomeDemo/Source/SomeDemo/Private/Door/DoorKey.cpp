// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorKey.h"
#include "Door/DoorKeyInteractionComponent.h"
#include "Inventory/InventoryItem_DoorKey.h"

FText DoorKeyTypeToFText(DoorKeyType Type)
{
	switch (Type)
	{
		case DoorKeyType::Universal:
			return FText::FromString("Universal");
		case DoorKeyType::Brass:
			return FText::FromString("Brass");
	}

	return FText::FromString("Invalid");
}

ADoorKey::ADoorKey()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionComponent = CreateDefaultSubobject<UDoorKeyInteractionComponent>(TEXT("InteractionComponent"));
}

DoorKeyType ADoorKey::GetType() const
{
	return Type;
}

void ADoorKey::GetInventoryItemData(UInventoryItem_DoorKey* Item) const
{
	Item->Type = Type;
}