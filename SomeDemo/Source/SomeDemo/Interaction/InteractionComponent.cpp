// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractionRangeSquared = InteractionRange * InteractionRange;
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

