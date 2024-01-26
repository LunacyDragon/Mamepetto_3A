// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Food.h"
#include "Toy.h"
#include "Toliet.h"
#include "Mamepetto.generated.h"

UCLASS()
class MAMEPETTO_3A_API AMamepetto : public AActor
{
	GENERATED_BODY()

	enum EDirectionState : int8
	{
		IDLE,
		NORTH,
		NORTHEAST,
		EAST,
		SOUTHEAST,
		SOUTH,
		SOUTHWEST,
		WEST,
		NORTHWEST,
		GOTOLOC,
		RESTING,
		EATING,
		PLAYING,
		RELIEVING,
		DEAD
	};
	
public:	
	// Sets default values for this actor's properties
	AMamepetto();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mamepetto Mesh")
		class UStaticMeshComponent* MamepettoMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mamepetto Speed")
		int MameUpdateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mamepetto Speed")
		int MameMoveSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
		float MaxFood = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
		float Energy = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaustion")
		float MaxExhaustion = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exhaustion")
		float Exhaustion = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mood")
		float MaxMood = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mood")
		float Mood = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toilet")
		float MaxToilet = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toilet")
		float Toilet = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		FName PetState = "Normal";




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction North")
		FQuat North;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction North East")
		FQuat NorthEast;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction East")
		FQuat East;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction South East")
		FQuat SouthEast;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction South")
		FQuat South;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction South West")
		FQuat SouthWest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction West")
		FQuat West;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction North West")
		FQuat NorthWest;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Awake")
		FQuat Awake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sleep")
		FQuat Sleep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dead")
		FQuat Dead;



private:


	float UpdateTick;


	bool Food;
	bool Toy;
	bool Bathroom;

	bool Eating;
	bool Playing;
	bool Exreeting;
	bool Sleeping;
	bool Death;
	bool Update;


	EDirectionState MameDirection;
	FString MameDirString;

	FVector Location;
	

	AFood* TargetFood;
	AToy* TargetToy;
	AToliet* TargetToliet;


	void Movement(float DeltaTime);
	void MovementCheckBoundries();
	void MovementGoToLocation(float DeltaTime);

	void MamepettoEat();
	void MamepettoPlay();
	void MamepettoToliet();
	void MamepettoExhaustion();

	void CheckForFood();
	void CheckForToy();
	void CheckForToliet();
	void CheckForExhaustion();
	void CheckStats();

	void DeadConditions();
	void DeadState();

public:

	float GetMamepettoEnergy();
	float GetMamepettoExhaustion();
	float GetMamepettoMood();
	float GetMamepettoToilet();




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
