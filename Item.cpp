// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Item Material"));


	ConstructorHelpers::FObjectFinder<UStaticMesh>ItemAsset(TEXT("/Game/Game_Assets/Item_Assets/SM_Item"));

	ConstructorHelpers::FObjectFinder<UMaterial>ItemAssetMaterial(TEXT("/Game/Game_Assets/Item_Assets/M_Item_Material"));



	if (ItemAsset.Succeeded())
	{
		ItemMesh->SetStaticMesh(ItemAsset.Object);


	}

	if (ItemAssetMaterial.Succeeded())
	{
		ItemMaterial = ItemAssetMaterial.Object;

		ItemMesh->SetMaterial(0, ItemMaterial);
	}

	FoodValue = FMath::RandRange(20, 30);

}

int AItem::GetFoodValue()
{
	return FoodValue;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();


	if(GetActorLocation().Z > 70)
	{

		Location.Z -= 1;

	}

	SetActorLocation(Location);

}

