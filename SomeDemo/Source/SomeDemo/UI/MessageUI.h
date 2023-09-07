// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageUI.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API UMessageUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

	// Message will be shown for: AppearTime + MessageTimeInSeconds + DisappearTime
	UFUNCTION(BlueprintCallable)
	bool ShowMessage(const FText& MessageText, float MainTime = 3.0f, float AppearTime = 1.0f, float DisappearTime = 1.0f);

	DECLARE_EVENT(UMessageUI, FMessageComplete)
	FMessageComplete OnMessageCompleted;
protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Message;

	UPROPERTY(VisibleAnywhere)
	bool bIsShowingMessage = false;
	UPROPERTY(VisibleAnywhere)
	float MessageCurrentTime;
	UPROPERTY(VisibleAnywhere)
	float MessageMainTime;
	UPROPERTY(VisibleAnywhere)
	float MessageAppearTime;
	UPROPERTY(VisibleAnywhere)
	float MessageDisappearTime;
};
