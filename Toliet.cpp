// Fill out your copyright notice in the Description page of Project Settings.


#include "Toliet.h"

// Sets default values
AToliet::AToliet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TolietMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Toliet Mesh"));
	TolietMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Toliet Material"));


	ConstructorHelpers::FObjectFinder<UStaticMesh>TolietAsset(TEXT("/Game/Game_Assets/Item_Assets/SM_InkWell"));

	ConstructorHelpers::FObjectFinder<UMaterial>TolietAssetMaterial(TEXT("/Game/Game_Assets/Item_Assets/M_InkBottle"));



	if (TolietAsset.Succeeded())
	{
		TolietMesh->SetStaticMesh(TolietAsset.Object);


	}

	if (TolietAssetMaterial.Succeeded())
	{
		TolietMaterial = TolietAssetMaterial.Object;

		TolietMesh->SetMaterial(0, TolietMaterial);
	}

	FoodValue = 5;

}

int AToliet::GetFoodValue()
{
	return FoodValue;
}

// Called when the game starts or when spawned
void AToliet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToliet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();


	if (GetActorLocation().Z > 20)
	{

		Location.Z -= 1;

	}

	SetActorLocation(Location);

}

