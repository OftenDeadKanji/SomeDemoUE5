// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePauseUI.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API UGamePauseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UButton* ExitGameButton;

protected:
	UFUNCTION()
	void ContinueGame();
	
	UFUNCTION()
	void ExitGame();
};
