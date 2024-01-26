// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Food.h"
#include "Toliet.h"
#include "Toy.h"
#include "ItemSpawner.generated.h"

UCLASS()
class MAMEPETTO_3A_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AFood*> SpawnedFoods;
	TArray<AToliet*> SpawnedToliets;
	TArray<AToy*> SpawnedToys;

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParameters;

	void SpawnItems();

private:

	int DecideItem;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
