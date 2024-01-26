// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Toliet.generated.h"

UCLASS()
class MAMEPETTO_3A_API AToliet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToliet();

private:
	int FoodValue;

public:
	int GetFoodValue();

	bool bHasBeenEaten;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* TolietMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UMaterial* TolietMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
