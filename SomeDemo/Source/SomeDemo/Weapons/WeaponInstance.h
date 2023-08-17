#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponInstance.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInstance
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentClipAmmo;
};