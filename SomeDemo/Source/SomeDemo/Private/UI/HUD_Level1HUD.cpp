// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD_Level1HUD.h"
#include "Blueprint/UserWidget.h"
#include "Characters/MainPlayer/MainPlayerController.h"
#include "UI/InteractionInfoUI.h"
#include "UI/MainPlayerHUD.h"
#include "UI/GamePauseUI.h"
#include "UI/WeaponInfoUI.h"
#include "UI/MessageUI.h"
#include "UI/PlayerInfoUI.h"

AHUD_Level1HUD::AHUD_Level1HUD()
{
	InteractionInfoUIClass = nullptr;
	InteractionInfoUI = nullptr;

	MessageUIClass = nullptr;
	MessageUI = nullptr;

	WeaponInfoUIClass = nullptr;
	WeaponInfoUI = nullptr;

	GamePauseUIClass = nullptr;
	GamePauseUI = nullptr;
}

void AHUD_Level1HUD::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerController = Cast<AMainPlayerController>(GetOwningPlayerController());

	PlayerInfoUI = CreateWidget<UPlayerInfoUI>(OwningPlayerController, PlayerInfoUIClass);
	PlayerInfoUI->AddToViewport();
}

bool AHUD_Level1HUD::ShowMessage(const FText& Message, float MainTime, float AppearTime, float DisappearTime)
{
	if (!MessageUI)
	{
		MessageUI = CreateWidget<UMessageUI>(OwningPlayerController, MessageUIClass);
		MessageUI->AddToViewport();

		MessageUI->OnMessageCompleted.AddUObject(this, &AHUD_Level1HUD::OnMessageCompleted);
	}

	return MessageUI->ShowMessage(Message, MainTime, AppearTime, DisappearTime);
}

void AHUD_Level1HUD::ShowWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo)
{
	if (!WeaponInfoUI)
	{
		WeaponInfoUI = CreateWidget<UWeaponInfoUI>(OwningPlayerController, WeaponInfoUIClass);
		WeaponInfoUI->AddToViewport();
	}
	WeaponInfoUI->SetWeaponInfo(WeaponName, ClipAmmo, RemainingAmmo);
}

void AHUD_Level1HUD::HideWeaponInfo()
{
	if (WeaponInfoUI)
	{
		WeaponInfoUI->RemoveFromViewport();
		WeaponInfoUI = nullptr;
	}
}

void AHUD_Level1HUD::UpdateWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo)
{
	if (WeaponInfoUI)
	{
		WeaponInfoUI->SetWeaponAmmunitionInfo(ClipAmmo, RemainingAmmo);
	}
}

void AHUD_Level1HUD::ShowInteractionInfo(const FText& InteractiveObjectInfo, const FText& PlayerInteractActionInfo)
{
	if (!InteractionInfoUI)
	{
		InteractionInfoUI = CreateWidget<UInteractionInfoUI>(OwningPlayerController, InteractionInfoUIClass);
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
		GamePauseUI = CreateWidget<UGamePauseUI>(OwningPlayerController, GamePauseUIClass);
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

void AHUD_Level1HUD::OnMessageCompleted()
{
	if (MessageUI)
	{
		MessageUI->RemoveFromViewport();
		MessageUI = nullptr;
	}
}

