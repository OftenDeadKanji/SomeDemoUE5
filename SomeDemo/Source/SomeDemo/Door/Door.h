// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class SOMEDEMO_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void StartOpening();

	UFUNCTION(BlueprintCallable)
		void StartClosing();

	UFUNCTION(BlueprintCallable)
		void ChangeState();

	UFUNCTION(BlueprintCallable)
		bool IsOpening() const;
	UFUNCTION(BlueprintCallable)
		bool IsOpen() const;
	UFUNCTION(BlueprintCallable)
		bool IsClosed() const;

	DECLARE_EVENT(ADoor, FDoorOpen)
		FDoorOpen OnDoorOpen;
	DECLARE_EVENT(ADoor, FDoorStartOpening)
		FDoorStartOpening OnDoorStartOpening;
	DECLARE_EVENT(ADoor, FDoorClose)
		FDoorClose OnDoorClose;
	DECLARE_EVENT(ADoor, FDoorStartClosing)
		FDoorStartClosing OnDoorStartClosing;
protected:
	UPROPERTY()
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		bool bIsOpening;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float Speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float OpenClosedFactor = 0.0f; // 0 - fully closed, 1 - fully open

	UPROPERTY(EditAnywhere)
		FTransform RelativeTransformWhenClosed;
	
	UPROPERTY(EditAnywhere)
		FTransform RelativeTransformWhenOpen;

	UPROPERTY(EditAnywhere)
		bool bEnabled = true;

};
