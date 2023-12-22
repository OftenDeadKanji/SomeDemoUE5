// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorInteractionComponent.h"
#include "Door/Door.h"

void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Door = Cast<ADoor>(GetOwner());
}

void UDoorInteractionComponent::InteractInternal_Implementation(AActor* InteractingActor)
{
	Door->ChangeState();
}
