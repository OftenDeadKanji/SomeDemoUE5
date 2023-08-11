// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("Fired!"));
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound, Volume);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::InitializeWeapon(FWeaponProperties& Properties)
{
	//if (Mesh && Properties.Mesh)
	//{
	//	Mesh->SetStaticMesh(Properties.Mesh);
	//}
	//
	//bIsHitscan = Properties.bIsHitScan;
}

