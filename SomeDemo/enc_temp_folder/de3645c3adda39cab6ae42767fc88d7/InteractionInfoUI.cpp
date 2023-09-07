// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionInfoUI.h"
#include "Components/TextBlock.h"

void UInteractionInfoUI::SetInteractionInfo(const FText& InteractiveObjectInfo, const FText& PlayerInteractActionInfo)
{
	InteractiveObjectInfoText->Text = InteractiveObjectInfo;
	PlayerInteractActionInfoText->Text = FText::Format(INVTEXT("Press 'E' to {0}"), PlayerInteractActionInfo);
}
