// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEDEMO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsInInteractionRange(const FVector& Location);
	UFUNCTION(BlueprintCallable)
	void Interact(class AActor* InteractingActor, bool ForceInteraction);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractInternal(class AActor* InteractingActor);
	void InteractInternal_Implementation(class AActor* InteractingActor);
	UFUNCTION(BlueprintCallable)
	bool AreInteractionConditionsMet(class AActor* InteractingActor, bool ForceInteraction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange = 200;
	float InteractionRangeSquared;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bInteractableOnlyInRange = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText ObjectDescriptionToDisplay;
};
