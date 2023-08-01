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
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnabled)
	{
		OpenClosedFactor += Speed * bIsOpening ? DeltaTime : -DeltaTime;
		OpenClosedFactor = FMath::Clamp(OpenClosedFactor, 0.0f, 1.0f);

		//auto transform = FMath::Lerp(RelativeTransformWhenClosed, RelativeTransformWhenOpen, OpenClosedFactor);
		FTransform transform(
			FMath::Lerp(RelativeTransformWhenClosed.GetRotation(), RelativeTransformWhenOpen.GetRotation(), OpenClosedFactor),
			FMath::Lerp(RelativeTransformWhenClosed.GetLocation(), RelativeTransformWhenOpen.GetLocation(), OpenClosedFactor),
			FMath::Lerp(RelativeTransformWhenClosed.GetScale3D(), RelativeTransformWhenOpen.GetScale3D(), OpenClosedFactor)
			);

		Mesh->SetRelativeTransform(transform);
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

bool ADoor::IsOpening() const
{
	return bIsOpening;
}

