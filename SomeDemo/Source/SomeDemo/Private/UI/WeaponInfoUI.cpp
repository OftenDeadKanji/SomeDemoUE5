// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponInfoUI.h"
#include "Components/TextBlock.h"

void UWeaponInfoUI::SetWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo)
{
    PlayerWeaponName->SetText(WeaponName);

    PlayerAmmo->SetVisibility(ESlateVisibility::Visible);
    PlayerAmmo->SetText(FText::Format(INVTEXT("{0}/{1}"), ClipAmmo, RemainingAmmo));
}
void UWeaponInfoUI::SetWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo)
{
    PlayerAmmo->SetText(FText::Format(INVTEXT("{0}/{1}"), ClipAmmo, RemainingAmmo));
}