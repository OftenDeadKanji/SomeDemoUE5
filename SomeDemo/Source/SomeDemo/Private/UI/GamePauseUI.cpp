// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GamePauseUI.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MainPlayer/MainPlayer.h"

void UGamePauseUI::NativeConstruct()
{
	Super::NativeConstruct();

	ContinueGameButton->OnClicked.AddDynamic(this, &UGamePauseUI::ContinueGame);
	ExitGameButton->OnClicked.AddDynamic(this, &UGamePauseUI::ExitGame);
}

void UGamePauseUI::ContinueGame()
{
	if (auto* mainPlayer = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		mainPlayer->ToggleGamePause();
	}
}

void UGamePauseUI::ExitGame()
{
	auto* World = GetWorld();
	auto* PlayerController = UGameplayStatics::GetPlayerController(World, 0);

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}
