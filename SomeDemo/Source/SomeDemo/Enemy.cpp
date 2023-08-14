// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateHealthBar();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::DoDamage_Implementation(float Value)
{
	Health -= Value;

	if (Health <= 0.0f)
	{
		GetWorld()->DestroyActor(this);
		return;
	}

	UpdateHealthBar();
}

void AEnemy::UpdateHealthBar()
{
	auto* progressBar = Cast<UProgressBar>(HealthBar->GetWidget()->WidgetTree->FindWidget(ProgressBarWidgetName));
	if (progressBar)
	{
		progressBar->SetPercent(Health / MaxHealth);
	}
}

