// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UDoorInteractionComponent;
class USkeletalMeshComponent;

UENUM()
enum class DoorState : uint8
{
	Open,
	Opening,

	Closed,
	Closing
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorStartOpening);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorClose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorStartClosing);

UCLASS()
class SOMEDEMO_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;
	virtual void InitInteractionComponent();

public:
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState();

	UFUNCTION(BlueprintCallable)
	bool IsOpening() const;
	UFUNCTION(BlueprintCallable)
	bool IsClosing() const;
	UFUNCTION(BlueprintCallable)
	bool IsOpen() const;
	UFUNCTION(BlueprintCallable)
	bool IsClosed() const;

	UFUNCTION(BlueprintCallable)
	bool IsEnabled() const;
	UFUNCTION(BlueprintCallable)
	void SetIsEnabled(bool Enabled);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDoorOpen OnDoorOpen;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDoorStartOpening OnDoorStartOpening;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDoorClose OnDoorClose;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDoorStartClosing OnDoorStartClosing;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDoorInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	bool bIsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	DoorState State = DoorState::Closed;

};
