// Fill out your copyright notice in the Description page of Project Settings.


#include "Toy.h"

// Sets default values
AToy::AToy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ToyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Toy Mesh"));
	ToyMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Toy Material"));


	ConstructorHelpers::FObjectFinder<UStaticMesh>ToyAsset(TEXT("/Game/Game_Assets/Item_Assets/SM_Globe"));

	ConstructorHelpers::FObjectFinder<UMaterial>ToyAssetMaterial(TEXT("/Game/Game_Assets/Item_Assets/M_Globe"));



	if (ToyAsset.Succeeded())
	{
		ToyMesh->SetStaticMesh(ToyAsset.Object);


	}

	if (ToyAssetMaterial.Succeeded())
	{
		ToyMaterial = ToyAssetMaterial.Object;

		ToyMesh->SetMaterial(0, ToyMaterial);
	}

	FoodValue = FMath::RandRange(5, 10);


}

int AToy::GetFoodValue()
{
	return FoodValue;
}

// Called when the game starts or when spawned
void AToy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();


	if (GetActorLocation().Z > 20)
	{

		Location.Z -= 1;

	}

	SetActorLocation(Location);

}

