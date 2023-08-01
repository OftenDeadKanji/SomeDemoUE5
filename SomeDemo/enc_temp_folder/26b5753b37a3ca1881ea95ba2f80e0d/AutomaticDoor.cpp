// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticDoor.h"
#include <Components/BoxComponent.h>
#include "MainPlayer.h"

// Sets default values
AAutomaticDoor::AAutomaticDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorTriggerValume"));
	RootComponent = DoorVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAutomaticDoor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorVolume->OnComponentBeginOverlap.AddDynamic(this, &AAutomaticDoor::OverlapBegin);
	DoorVolume->OnComponentEndOverlap.AddDynamic(this, &AAutomaticDoor::OverlapEnd);
}

// Called every frame
void AAutomaticDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnabled)
	{
		OpeningParameter += Speed * bIsOpening ? DeltaTime : -DeltaTime;
		OpeningParameter = FMath::Clamp(OpeningParameter, 0.0f, 1.0f);

		FVector position = FMath::Lerp(RelativePositionWhenClosed, RelativePositionWhenOpen, OpeningParameter);
		Mesh->SetRelativeLocation(position);
	}
}

void AAutomaticDoor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainPlayer>(OtherActor))
	{
		bIsOpening = true;
	}
}

void AAutomaticDoor::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMainPlayer>(OtherActor))
	{
		bIsOpening = false;
	}
}

