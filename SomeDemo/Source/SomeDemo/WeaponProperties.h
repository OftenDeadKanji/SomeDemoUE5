// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponProperties.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponProperties : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float TimeBetweenShots;
	UPROPERTY(EditAnywhere)
		bool bIsHitScan;
	UPROPERTY(EditAnywhere)
		float BaseDamagePerShot;
	UPROPERTY(EditAnywhere)
		int32 ClipSize;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmo;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* Mesh;
};
