// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/Door.h"
#include "Door/DoorInteractionComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void ADoor::BeginPlay()
{
	InitInteractionComponent();
}

void ADoor::InitInteractionComponent()
{
	InteractionComponent = NewObject<UDoorInteractionComponent>(this, TEXT("InteractionComponent"));
	InteractionComponent->RegisterComponent();

	InteractionComponent->ObjectDescriptionToDisplay = INVTEXT("Door");
	InteractionComponent->InteractActionToDisplay = INVTEXT("open");
}

void ADoor::ChangeState()
{
	if (bIsEnabled)
	{
		if (State == DoorState::Open)
		{
			State = DoorState::Closing;

			OnDoorStartClosing.Broadcast();
		}
		else if (State == DoorState::Closed)
		{
			State = DoorState::Opening;

			OnDoorStartOpening.Broadcast();
		}
	}
}

bool ADoor::IsOpening() const
{
	return State == DoorState::Opening;
}

bool ADoor::IsClosing() const
{
	return State == DoorState::Closing;
}

bool ADoor::IsOpen() const
{
	return State == DoorState::Open;
}

bool ADoor::IsClosed() const
{
	return State == DoorState::Closed;
}

bool ADoor::IsEnabled() const
{
	return bIsEnabled;
}

void ADoor::SetIsEnabled(bool Enabled)
{
	bIsEnabled = Enabled;
}
