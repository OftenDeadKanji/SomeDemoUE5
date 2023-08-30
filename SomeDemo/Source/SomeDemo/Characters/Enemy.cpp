// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/CapsuleComponent.h"
#include "MainPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(RootComponent);

	CatchingPlayerArea = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CatchingPlayerArea"));
	CatchingPlayerArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CatchingPlayerArea->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCatchingPlayerAreaOverlapBegin);
	CatchingPlayerArea->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnCatchingPlayerAreaOverlapEnd);

	UpdateHealthBar();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::DoDamage_Implementation(AActor* DamagingActor, float DamageValue)
{
	Health -= DamageValue;

	if (Health <= 0.0f)
	{
		GetWorld()->DestroyActor(this);
		return;
	}

	UpdateHealthBar();

	OnDamageTake.Broadcast(DamagingActor, DamageValue);
}

void AEnemy::UpdateHealthBar()
{
	auto* progressBar = Cast<UProgressBar>(HealthBar->GetWidget()->WidgetTree->FindWidget(ProgressBarWidgetName));
	if (progressBar)
	{
		progressBar->SetPercent(Health / MaxHealth);
	}
}

void AEnemy::OnCatchingPlayerAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* Player = Cast<AMainPlayer>(OtherActor))
	{
		auto* World = GetWorld();
		//auto* PC = UGameplayStatics::GetPlayerController(World, 0);
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
		//UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, false);
	}
}

void AEnemy::OnCatchingPlayerAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{}

