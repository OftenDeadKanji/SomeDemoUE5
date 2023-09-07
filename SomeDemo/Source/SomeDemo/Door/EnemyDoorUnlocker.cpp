// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDoorUnlocker.h"
#include "../Characters/Enemy/Enemy.h"
#include "Door.h"

// Sets default values
AEnemyDoorUnlocker::AEnemyDoorUnlocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AEnemyDoorUnlocker::BeginPlay()
{
	Super::BeginPlay();
	
	EnemiesToUnlockDoor = ObservedEnemies.Num();
	for (const auto& Enemy : ObservedEnemies)
	{
		Enemy->OnDestroyed.AddUniqueDynamic(this, &AEnemyDoorUnlocker::ObservedEnemyDestroyed);
	}
}

// Called every frame
void AEnemyDoorUnlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyDoorUnlocker::ObservedEnemyDestroyed(AActor* Destroyed)
{
	EnemiesToUnlockDoor--;

	if (EnemiesToUnlockDoor == 0)
	{
		ConnectedDoor->StartOpening();
	}
}

