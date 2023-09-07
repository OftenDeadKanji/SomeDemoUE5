// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerHUD.h"
#include "Components/TextBlock.h"

bool UMainPlayerHUD::ShowMessage(float MainTime, float AppearTime, float DisappearTime)
{
    if (bIsShowingMessage)
    {
        return false;
    }
    bIsShowingMessage = true;

    MessageMainTime = MainTime;
    MessageAppearTime = AppearTime;
    MessageDisappearTime = DisappearTime;

    MessageCurrentTime = 0.0f;

    return true;
}

void UMainPlayerHUD::ShowWeaponInfo(const FText& WeaponName, int32 ClipAmmo, int32 RemainingAmmo)
{
    PlayerWeaponName->Visibility = ESlateVisibility::Visible;
    PlayerWeaponName->Text = WeaponName;

    PlayerAmmo->Visibility = ESlateVisibility::Visible;
    PlayerAmmo->Text = FText::Format(INVTEXT("{0}/{1}"), ClipAmmo, RemainingAmmo);
}

void UMainPlayerHUD::HideWeaponInfo()
{
    PlayerWeaponName->Visibility = ESlateVisibility::Hidden;
    PlayerAmmo->Visibility = ESlateVisibility::Hidden;
}

void UMainPlayerHUD::UpdateWeaponAmmunitionInfo(int ClipAmmo, int RemainingAmmo)
{
    PlayerAmmo->Text = FText::Format(INVTEXT("{0}/{1}"), ClipAmmo, RemainingAmmo);
}

void UMainPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    if (bIsShowingMessage)
    {
        MessageCurrentTime += InDeltaTime;

        float Opacity = 1.0f;
        if (MessageCurrentTime <= MessageAppearTime)
        {
            Opacity = FMath::Lerp(0.0f, 1.0f, MessageCurrentTime / MessageAppearTime);
        }
        else if (MessageCurrentTime > MessageAppearTime + MessageMainTime)
        {
            Opacity = FMath::Lerp(1.0f, 0.0f, (MessageCurrentTime - (MessageAppearTime + MessageMainTime)) / MessageDisappearTime);
        }

        Message->SetRenderOpacity(Opacity);
        
        if (MessageCurrentTime > MessageAppearTime + MessageMainTime + MessageDisappearTime)
        {
            bIsShowingMessage = false;
        }
    }
}
