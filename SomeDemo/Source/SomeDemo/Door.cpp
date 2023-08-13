// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (bIsOpening)
	{
		if (OpenClosedFactor == 1.0f)
		{
			OnDoorOpen.Broadcast();
		}
		else
		{
			OnDoorStartOpening.Broadcast();
		}
	}
	else
	{
		if (OpenClosedFactor == 0.0f)
		{
			OnDoorClose.Broadcast();
		}
		else
		{
			OnDoorStartClosing.Broadcast();
		}
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnabled)
	{
		bool needToOpen = bIsOpening && OpenClosedFactor != 1.0f;
		bool needToClose = !bIsOpening && OpenClosedFactor != 0.0f;

		if (needToOpen || needToClose)
		{
			if (OpenClosedFactor == 0.0f)
			{
				OnDoorStartOpening.Broadcast();
			}
			else if (OpenClosedFactor == 1.0f)
			{
				OnDoorStartClosing.Broadcast();
			}

			OpenClosedFactor += Speed * bIsOpening ? DeltaTime : -DeltaTime;
			OpenClosedFactor = FMath::Clamp(OpenClosedFactor, 0.0f, 1.0f);

			FTransform transform(
				FMath::Lerp(RelativeTransformWhenClosed.GetRotation(), RelativeTransformWhenOpen.GetRotation(), OpenClosedFactor),
				FMath::Lerp(RelativeTransformWhenClosed.GetLocation(), RelativeTransformWhenOpen.GetLocation(), OpenClosedFactor),
				FMath::Lerp(RelativeTransformWhenClosed.GetScale3D(),  RelativeTransformWhenOpen.GetScale3D(),  OpenClosedFactor)
				);

			Mesh->SetRelativeTransform(transform);

			if (bIsOpening && OpenClosedFactor == 1.0f)
			{
				OnDoorOpen.Broadcast();
			}
			else if (!bIsOpening && OpenClosedFactor == 0.0f)
			{
				OnDoorClose.Broadcast();
			}
		}
	}
}

void ADoor::StartOpening()
{
	bIsOpening = true;
}

void ADoor::StartClosing()
{
	bIsOpening = false;
}

void ADoor::ChangeState()
{
	bIsOpening = !bIsOpening;
}

bool ADoor::IsOpening() const
{
	return bIsOpening;
}

bool ADoor::IsOpen() const
{
	return OpenClosedFactor == 1.0f;
}

bool ADoor::IsClosed() const
{
	return OpenClosedFactor == 0.0f;
}

