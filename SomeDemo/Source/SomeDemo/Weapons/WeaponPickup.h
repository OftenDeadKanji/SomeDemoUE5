// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInstance.h"
#include "WeaponPickup.generated.h"

UCLASS(Blueprintable)
class SOMEDEMO_API AWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		class USphereComponent* PickupArea;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloatHeight = 50.0f;
	float StartingZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloatSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWeaponInstance WeaponToPickup;

};
