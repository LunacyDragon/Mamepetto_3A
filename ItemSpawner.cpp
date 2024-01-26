// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemSpawner::SpawnItems()
{
	SpawnLocation = FVector(FMath::RandRange(-400, 400), FMath::RandRange(-400, 400), 400);
	DecideItem = FMath::RandRange(0, 2);

	SpawnParameters.OverrideLevel = GetLevel();

	if (DecideItem == 0)
	{

		SpawnedFoods.Add((AFood*)GetWorld()->SpawnActor(AFood::StaticClass(),
			&SpawnLocation, &SpawnRotation, SpawnParameters));

	}

	if (DecideItem == 1)
	{
		SpawnedToliets.Add((AToliet*)GetWorld()->SpawnActor(AToliet::StaticClass(),
			&SpawnLocation, &SpawnRotation, SpawnParameters));
	}
	
	if (DecideItem == 2)
	{
		SpawnedToys.Add((AToy*)GetWorld()->SpawnActor(AToy::StaticClass(),
			&SpawnLocation, &SpawnRotation, SpawnParameters));
	}

}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (FMath::RandRange(0, 666) == 1)
	{

		SpawnItems();

	}

}

