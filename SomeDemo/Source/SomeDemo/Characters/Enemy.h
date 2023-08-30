// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Damageable.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageTake, class AActor*, DamagingActor, float, DamageValue);

UCLASS()
class SOMEDEMO_API AEnemy : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void DoDamage_Implementation(class AActor* DamagingActor, float DamageValue) override;

	UPROPERTY(BlueprintAssignable)
	FDamageTake OnDamageTake;

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar();
protected:
	UFUNCTION()
	void OnCatchingPlayerAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCatchingPlayerAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UWidgetComponent* HealthBar;
	UPROPERTY(EditAnywhere, Category = "UI")
	FName ProgressBarWidgetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UCapsuleComponent* CatchingPlayerArea;
};
