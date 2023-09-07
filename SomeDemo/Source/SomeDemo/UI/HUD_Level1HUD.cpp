// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Level1HUD.h"
#include "Blueprint/UserWidget.h"
#include "../Characters/MainPlayer/MainPlayerController.h"
#include "InteractionInfoUI.h"
#include "MainPlayerHUD.h"
#include "GamePauseUI.h"

AHUD_Level1HUD::AHUD_Level1HUD()
{
	InteractionInfoUIClass = nullptr;
	InteractionInfoUI = nullptr;

	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	GamePauseUIClass = nullptr;
	GamePauseUI = nullptr;
}

void AHUD_Level1HUD::BeginPlay()
{
	Super::BeginPlay();

	CreateMainPlayerHUD();
}

void AHUD_Level1HUD::CreateMainPlayerHUD()
{
	if (!PlayerHUD)
	{
		auto* PC = Cast<AMainPlayerController>(GetOwningPlayerController());

		PlayerHUD = CreateWidget<UMainPlayerHUD>(PC, PlayerHUDClass);
		PlayerHUD->AddToViewport();
	}
}

bool AHUD_Level1HUD::ShowMessage(const FText& Message, float MainTime, float AppearTime, float DisappearTime)
{
	return PlayerHUD->ShowMessage(Message, MainTime, AppearTime, DisappearTime);
}

void AHUD_Level1HUD::ShowWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo)
{
	PlayerHUD->ShowWeaponInfo(WeaponName, ClipAmmo, RemainingAmmo);
}

void AHUD_Level1HUD::HideWeaponInfo()
{
	PlayerHUD->HideWeaponInfo();
}

void AHUD_Level1HUD::UpdateWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo)
{
	PlayerHUD->UpdateWeaponAmmunitionInfo(ClipAmmo, RemainingAmmo);
}

void AHUD_Level1HUD::ShowInteractionInfo(const FText& InteractiveObjectInfo, const FText& PlayerInteractActionInfo)
{
	if (!InteractionInfoUI)
	{
		auto* PC = Cast<AMainPlayerController>(GetOwningPlayerController());

		InteractionInfoUI = CreateWidget<UInteractionInfoUI>(PC, InteractionInfoUIClass);
		InteractionInfoUI->AddToViewport();
	}
	InteractionInfoUI->SetInteractionInfo(InteractiveObjectInfo, PlayerInteractActionInfo);
}

void AHUD_Level1HUD::HideInteractionInfo()
{
	if (InteractionInfoUI)
	{
		InteractionInfoUI->RemoveFromViewport();
		InteractionInfoUI = nullptr;
	}
}

void AHUD_Level1HUD::ShowPauseScreen()
{
	if (!GamePauseUI)
	{
		auto* PC = Cast<AMainPlayerController>(GetOwningPlayerController());

		GamePauseUI = CreateWidget<UGamePauseUI>(PC, GamePauseUIClass);
		GamePauseUI->AddToViewport();
	}
}

void AHUD_Level1HUD::HidePauseScreen()
{
	if (GamePauseUI)
	{
		GamePauseUI->RemoveFromViewport();
		GamePauseUI = nullptr;
	}
}

