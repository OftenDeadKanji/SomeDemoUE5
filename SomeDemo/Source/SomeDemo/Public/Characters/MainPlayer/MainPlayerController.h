// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();

	void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerPawn(class AMainPlayer* PlayerPawnToControll);
protected:
	void CallMoveForward(float Val);
	void CallMoveRight(float Val);
	void CallTurn(float Val);
	void CallLookUp(float Val);

	void CallFire();
	void CallReload();
	void CallSetItem1();

	void CallInteract();
	void CallToggleGamePause();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMainPlayer* PlayerPawn;
};
