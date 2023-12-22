// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainPlayer/MainPlayerController.h"
#include "Characters/MainPlayer/MainPlayer.h"

AMainPlayerController::AMainPlayerController()
{
	AutoReceiveInput = EAutoReceiveInput::Player0;
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MainPlayer_MoveForward", this, &AMainPlayerController::CallMoveForward);
	InputComponent->BindAxis("MainPlayer_MoveRight", this, &AMainPlayerController::CallMoveRight);
	InputComponent->BindAxis("MainPlayer_Turn", this, &AMainPlayerController::CallTurn);
	InputComponent->BindAxis("MainPlayer_LookUp", this, &AMainPlayerController::CallLookUp);

	InputComponent->BindAction("MainPlayer_Fire", IE_Pressed, this, &AMainPlayerController::CallFire);
	InputComponent->BindAction("MainPlayer_Reload", IE_Pressed, this, &AMainPlayerController::CallReload);
	InputComponent->BindAction("MainPlayer_SetItem1", IE_Pressed, this, &AMainPlayerController::CallSetItem1);

	InputComponent->BindAction("MainPlayer_Interact", IE_Pressed, this, &AMainPlayerController::CallInteract);
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AMainPlayerController::CallToggleGamePause);
}

void AMainPlayerController::SetPlayerPawn(AMainPlayer* PlayerPawnToControll)
{
	Possess(PlayerPawnToControll);
	PlayerPawn = PlayerPawnToControll;
}

void AMainPlayerController::CallMoveForward(float Val)
{
	if (PlayerPawn)
	{
		PlayerPawn->MoveForward(Val);
	}
}

void AMainPlayerController::CallMoveRight(float Val)
{
	if (PlayerPawn)
	{
		PlayerPawn->MoveRight(Val);
	}
}

void AMainPlayerController::CallTurn(float Val)
{
	if (PlayerPawn)
	{
		PlayerPawn->Turn(Val);
	}
}

void AMainPlayerController::CallLookUp(float Val)
{
	if (PlayerPawn)
	{
		PlayerPawn->LookUp(Val);
	}
}

void AMainPlayerController::CallFire()
{
	if (PlayerPawn)
	{
		PlayerPawn->Fire();
	}
}

void AMainPlayerController::CallReload()
{
	if (PlayerPawn)
	{
		PlayerPawn->Reload();
	}
}

void AMainPlayerController::CallSetItem1()
{
	if (PlayerPawn)
	{
		PlayerPawn->SetItem1();
	}
}

void AMainPlayerController::CallInteract()
{
	if (PlayerPawn)
	{
		PlayerPawn->Interact();
	}
}

void AMainPlayerController::CallToggleGamePause()
{
	if (PlayerPawn)
	{
		PlayerPawn->ToggleGamePause();
	}
}
