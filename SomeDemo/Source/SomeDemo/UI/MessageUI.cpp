// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageUI.h"
#include "Components/TextBlock.h"

void UMessageUI::NativeConstruct()
{
    Super::NativeConstruct();

    if (!bIsShowingMessage)
    {
        Message->SetVisibility(ESlateVisibility::Collapsed);
    }
}

bool UMessageUI::ShowMessage(const FText& MessageText, float MainTime, float AppearTime, float DisappearTime)
{
    if (bIsShowingMessage)
    {
        return false;
    }
    bIsShowingMessage = true;

    Message->SetText(MessageText);
    Message->SetVisibility(ESlateVisibility::Visible);

    MessageMainTime = MainTime;
    MessageAppearTime = AppearTime;
    MessageDisappearTime = DisappearTime;

    MessageCurrentTime = 0.0f;

    return true;
}

void UMessageUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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
            OnMessageCompleted.Broadcast();
        }
    }
}
