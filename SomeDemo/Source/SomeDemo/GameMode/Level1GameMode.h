// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Characters/MainPlayer/MainPlayer.h"
#include "../UI/HUD_Level1HUD.h"
#include "Level1GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOMEDEMO_API ALevel1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALevel1GameMode();

	void InitGameState() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMainPlayer> DefaultPawn;// = AMainPlayer::StaticClass();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHUD_Level1HUD> HUD;// = AHUD_Level1HUD::StaticClass();
};
