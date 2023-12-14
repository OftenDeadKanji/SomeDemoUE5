// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Inventory/InventoryItem_Base.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddItem(UInventoryItem_Base* Item)
{
	Items.Push(Item);
}

void UInventory::RemoveItem(UInventoryItem_Base* Item)
{
	Items.Remove(Item);
}

bool UInventory::Contains(UInventoryItem_Base* Item)
{
	return Items.Contains(Item);
}

