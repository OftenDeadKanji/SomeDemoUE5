// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyDoorUnlocker.generated.h"

UCLASS()
class SOMEDEMO_API AEnemyDoorUnlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyDoorUnlocker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UFUNCTION()
		void ObservedEnemyDestroyed(AActor* Destroyed);

	UPROPERTY(EditAnywhere)
		TArray<class AEnemy*> ObservedEnemies;
	UPROPERTY(VisibleAnywhere)
		int EnemiesToUnlockDoor;

	UPROPERTY(EditAnywhere)
		class ADoor* ConnectedDoor;
};
