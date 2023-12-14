// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::ChangeState()
{
	if (bEnabled)
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

void ADoor::DoorClosed()
{
	State = DoorState::Closed;

	OnDoorClose.Broadcast();
}

void ADoor::DoorOpened()
{
	State = DoorState::Open;

	OnDoorOpen.Broadcast();
}

