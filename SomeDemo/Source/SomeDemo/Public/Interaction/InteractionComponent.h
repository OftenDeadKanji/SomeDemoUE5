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
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	bool IsInInteractionRange(const FVector& Location);
	UFUNCTION(BlueprintCallable)
	void Interact(class AActor* InteractingActor, bool ForceInteraction);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractInternal(class AActor* InteractingActor);
	virtual void InteractInternal_Implementation(class AActor* InteractingActor);
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractActionToDisplay;
};
