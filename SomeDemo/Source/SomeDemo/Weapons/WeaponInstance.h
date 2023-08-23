#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponInstance.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInstance
{
	GENERATED_BODY();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAvailable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentRemainingAmmo; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentClipAmmo;
};