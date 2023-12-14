// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM()
enum class DoorState : uint8
{
	Open,
	Opening,

	Closed,
	Closing
};

UCLASS()
class SOMEDEMO_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ChangeState();

	UFUNCTION(BlueprintCallable)
	bool IsOpening() const;
	UFUNCTION(BlueprintCallable)
	bool IsClosing() const;
	UFUNCTION(BlueprintCallable)
	bool IsOpen() const;
	UFUNCTION(BlueprintCallable)
	bool IsClosed() const;

	UFUNCTION(BlueprintCallable)
	void DoorClosed();

	UFUNCTION(BlueprintCallable)
	void DoorOpened();


	DECLARE_EVENT(ADoor, FDoorOpen)
	FDoorOpen OnDoorOpen;
	DECLARE_EVENT(ADoor, FDoorStartOpening)
	FDoorStartOpening OnDoorStartOpening;
	DECLARE_EVENT(ADoor, FDoorClose)
	FDoorClose OnDoorClose;
	DECLARE_EVENT(ADoor, FDoorStartClosing)
	FDoorStartClosing OnDoorStartClosing;

protected:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	DoorState State = DoorState::Closed;

};
