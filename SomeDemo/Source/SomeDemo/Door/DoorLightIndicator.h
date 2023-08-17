// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorLightIndicator.generated.h"

UCLASS(Blueprintable)
class SOMEDEMO_API ADoorLightIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorLightIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = Light)
		class UPointLightComponent* PointLight;
	UPROPERTY(EditAnywhere, Category = Light)
		FLinearColor ColorWhenDoorIsOpen;
	UPROPERTY(EditAnywhere, Category = Light)
		FLinearColor ColorWhenDoorIsClosed;
	UPROPERTY(EditAnywhere, Category = Light)
		FLinearColor ColorWhenDoorIsChangingState;
	UPROPERTY(VisibleAnywhere)
		bool bIsFlickering = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FlickeringSpeed = 5.0f;
	UPROPERTY(EditAnywhere)
		class ADoor* Door;


	void ChangeToColorWhenOpen();
	void ChangeToColorWhenClosed();
	void ChangeToColorWhenChangingState();

};
