// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Food Mesh"));
	FoodMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Food Material"));


	ConstructorHelpers::FObjectFinder<UStaticMesh>FoodAsset(TEXT("/Game/Game_Assets/Item_Assets/SM_Mamepetto_Food"));

	ConstructorHelpers::FObjectFinder<UMaterial>FoodAssetMaterial(TEXT("/Game/Game_Assets/Item_Assets/M_Mamepetto_Food"));



	if (FoodAsset.Succeeded())
	{
		FoodMesh->SetStaticMesh(FoodAsset.Object);


	}

	if (FoodAssetMaterial.Succeeded())
	{
		FoodMaterial = FoodAssetMaterial.Object;

		FoodMesh->SetMaterial(0, FoodMaterial);
	}

	FoodValue = FMath::RandRange(5, 10);

}

int AFood::GetFoodValue()
{
	return FoodValue;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();


	if (GetActorLocation().Z > 20)
	{

		Location.Z -= 1;

	}

	SetActorLocation(Location);

}