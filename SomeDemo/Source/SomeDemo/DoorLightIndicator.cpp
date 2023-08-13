// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorLightIndicator.h"
#include "Components/PointLightComponent.h"
#include "Door.h"

// Sets default values
ADoorLightIndicator::ADoorLightIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetStaticMesh(Mesh);
	MeshComponent->SetMaterial(0, Material);
	MeshComponent->SetupAttachment(Root);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADoorLightIndicator::BeginPlay()
{
	Super::BeginPlay();

	if (Door)
	{
		Door->OnDoorOpen.AddUObject(this, &ADoorLightIndicator::ChangeToColorWhenOpen);
		Door->OnDoorClose.AddUObject(this, &ADoorLightIndicator::ChangeToColorWhenClosed);

		Door->OnDoorStartOpening.AddUObject(this, &ADoorLightIndicator::ChangeToColorWhenChangingState);
		Door->OnDoorStartClosing.AddUObject(this, &ADoorLightIndicator::ChangeToColorWhenChangingState);

		//init state
		if (Door->IsOpen())
		{
			ChangeToColorWhenOpen();
		}
		else if (Door->IsClosed())
		{
			ChangeToColorWhenClosed();
		}
		else
		{
			ChangeToColorWhenChangingState();
		}
	}
}

// Called every frame
void ADoorLightIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFlickering)
	{
		float t = (FMath::Sin(GetGameTimeSinceCreation() * FlickeringSpeed) + 1.0f) * 0.5f;

		PointLight->SetLightColor(ColorWhenDoorIsChangingState * t);
	}
}

void ADoorLightIndicator::ChangeToColorWhenOpen()
{
	PointLight->SetLightColor(ColorWhenDoorIsOpen);

	bIsFlickering = false;
}

void ADoorLightIndicator::ChangeToColorWhenClosed()
{
	PointLight->SetLightColor(ColorWhenDoorIsClosed);

	bIsFlickering = false;
}

void ADoorLightIndicator::ChangeToColorWhenChangingState()
{
	bIsFlickering = true;
}

