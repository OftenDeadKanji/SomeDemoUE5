// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutomaticDoor.generated.h"

UCLASS()
class SOMEDEMO_API AAutomaticDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutomaticDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* DoorVolume;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		bool bIsOpening;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float OpeningParameter = 0.0f; // 0 - fully closed, 1 - fully open

	UPROPERTY(EditAnywhere)
		FVector RelativePositionWhenClosed;

	UPROPERTY(EditAnywhere)
		FVector RelativePositionWhenOpen;

	UPROPERTY(EditAnywhere)
		bool bEnabled = true;
};
