// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Damageable.h"
#include "Enemy.generated.h"

UCLASS()
class SOMEDEMO_API AEnemy : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DoDamage_Implementation(float Value) override;

	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* HealthBar;
	UPROPERTY(EditAnywhere, Category = "UI")
		FName ProgressBarWidgetName;

};
