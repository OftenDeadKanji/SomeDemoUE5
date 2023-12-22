// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionRangeSquared = InteractionRange * InteractionRange;
}

bool UInteractionComponent::IsInInteractionRange(const FVector& Location)
{
	auto OwnerLocation = GetOwner()->GetActorLocation();

	float DistSq = FVector::DistSquared(Location, OwnerLocation);

	return DistSq <= InteractionRangeSquared;
}

void UInteractionComponent::Interact(AActor* InteractingActor, bool ForceInteraction)
{
	if (AreInteractionConditionsMet(InteractingActor, ForceInteraction))
	{
		InteractInternal(InteractingActor);
	}
}

void UInteractionComponent::InteractInternal_Implementation(AActor * InteractingActor)
{}

bool UInteractionComponent::AreInteractionConditionsMet(AActor* InteractingActor, bool ForceInteraction)
{
	if (ForceInteraction)
	{
		return true;
	}

	bool IsInRange = IsInInteractionRange(InteractingActor->GetActorLocation());

	return !bInteractableOnlyInRange || IsInRange;
}

