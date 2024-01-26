// Fill out your copyright notice in the Description page of Project Settings.


#include "Mamepetto.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMamepetto::AMamepetto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MamepettoMesh = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("Mamepetto Mesh"));

	Location.Z = 20;
	UpdateTick = 0;
	MameUpdateSpeed = 100;
	MameMoveSpeed = 100;
	MameDirection = EDirectionState::SOUTH;


}

void AMamepetto::Movement(float DeltaTime)
{

	MovementCheckBoundries();


	switch (MameDirection)
	{
	case EDirectionState::IDLE:
		MameDirString = "IDLE";
		break;

	case EDirectionState::NORTH:
		MameDirString = "NORTH";
		Location.X += MameMoveSpeed *DeltaTime;
		SetActorRotation(North);
		break;

	case EDirectionState::NORTHEAST:
		MameDirString = "NORTHEAST";
		Location.X += MameMoveSpeed * DeltaTime;
		Location.Y += MameMoveSpeed * DeltaTime;
		SetActorRotation(NorthEast);
		break;

	case EDirectionState::EAST:
		MameDirString = "EAST";
		Location.Y += MameMoveSpeed * DeltaTime;
		SetActorRotation(East);
		break;

	case EDirectionState::SOUTHEAST:
		MameDirString = "SOUTHEAST";
		Location.X -= MameMoveSpeed * DeltaTime;
		Location.Y += MameMoveSpeed * DeltaTime;
		SetActorRotation(SouthEast);
		break;

	case EDirectionState::SOUTH:
		MameDirString = "SOUTH";
		Location.X -= MameMoveSpeed * DeltaTime;
		SetActorRotation(South);
		break;

	case EDirectionState::SOUTHWEST:
		MameDirString = "SOUTHWEST";
		Location.X -= MameMoveSpeed * DeltaTime;
		Location.Y -= MameMoveSpeed * DeltaTime;
		SetActorRotation(SouthWest);
		break;

	case EDirectionState::WEST:
		MameDirString = "WEST";
		Location.Y -= MameMoveSpeed * DeltaTime;
		SetActorRotation(West);
		break;

	case EDirectionState::NORTHWEST:
		MameDirString = "NORTHWEST";
		Location.X += MameMoveSpeed * DeltaTime;
		Location.Y -= MameMoveSpeed * DeltaTime;
		SetActorRotation(NorthWest);
		break;


	case EDirectionState::GOTOLOC:
		MameDirString = "GOTOLOC";

		MovementGoToLocation(DeltaTime);

		break;

	case EDirectionState::RESTING:
		MameDirString = "RESTING";

		MamepettoExhaustion();

		break;

	case EDirectionState::EATING:
		MameDirString = "EATING";

		MamepettoEat();

		break;

	case EDirectionState::PLAYING:
		MameDirString = "PLAYING";

		MamepettoPlay();

		break;

	case EDirectionState::RELIEVING:
		MameDirString = "RELIEVING";

		MamepettoToliet();

		break;

	case EDirectionState::DEAD:
		MameDirString = "DEAD";

		DeadState();
		break;


	}
	

	SetActorLocation(Location);
}

void AMamepetto::MovementCheckBoundries()
{
	

	if (Location.X >= 450)
	{

		MameDirection = EDirectionState::SOUTH;

	}
	else if (Location.X <= -450)
	{
		MameDirection = EDirectionState::NORTH;

	}

	if (Location.Y >= 450)
	{

		MameDirection = EDirectionState::WEST;

	}
	else if (Location.Y <= -450)
	{
		MameDirection = EDirectionState::EAST;

	}

}

void AMamepetto::MovementGoToLocation(float DeltaTime)
{
	bool bHasEaten = false;
      int XDifference = 0;
      int YDifference = 0;

	  if (Food == true)
	  {

		  if (Location.X > TargetFood->GetActorLocation().X)
		  {
			  Location.X -= MameMoveSpeed * DeltaTime;

			  XDifference = Location.X - TargetFood->GetActorLocation().X;
			  SetActorRotation(South);
		  }

		  else
		  {
			  Location.X += MameMoveSpeed * DeltaTime;
			  XDifference = TargetFood->GetActorLocation().X - Location.X;
			  SetActorRotation(North);

		  }

		  if (Location.Y > TargetFood->GetActorLocation().Y)
		  {
			  Location.Y -= MameMoveSpeed * DeltaTime;
			  YDifference = Location.Y - TargetFood->GetActorLocation().Y;
			  SetActorRotation(West);

		  }

		  else
		  {
			  Location.Y += MameMoveSpeed * DeltaTime;
			  YDifference = TargetFood->GetActorLocation().Y - Location.Y;
			  SetActorRotation(East);
		  }

		  if (XDifference < 10 && YDifference < 10)
		  {

			  MameDirection = EDirectionState::EATING;

			
		  }
	  }

	  if (Toy == true && Food == false)
	  {

		  if (Location.X > TargetToy->GetActorLocation().X)
		  {
			  Location.X -= MameMoveSpeed * DeltaTime;

			  XDifference = Location.X - TargetToy->GetActorLocation().X;
			  SetActorRotation(South);
		  }

		  else
		  {
			  Location.X += MameMoveSpeed * DeltaTime;
			  XDifference = TargetToy->GetActorLocation().X - Location.X;
			  SetActorRotation(North);

		  }

		  if (Location.Y > TargetToy->GetActorLocation().Y)
		  {
			  Location.Y -= MameMoveSpeed * DeltaTime;
			  YDifference = Location.Y - TargetToy->GetActorLocation().Y;
			  SetActorRotation(West);

		  }

		  else
		  {
			  Location.Y += MameMoveSpeed * DeltaTime;
			  YDifference = TargetToy->GetActorLocation().Y - Location.Y;
			  SetActorRotation(East);
		  }

		  if (XDifference < 10 && YDifference < 10)
		  {

			  MameDirection = EDirectionState::PLAYING;
		  }
	  }
	  if (Bathroom == true && Toy == false && Food == false)
	  {
		  if (Location.X > TargetToliet->GetActorLocation().X)
		  {
			  Location.X -= MameMoveSpeed * DeltaTime;

			  XDifference = Location.X - TargetToliet->GetActorLocation().X;
			  SetActorRotation(South);
		  }

		  else
		  {
			  Location.X += MameMoveSpeed * DeltaTime;
			  XDifference = TargetToliet->GetActorLocation().X - Location.X;
			  SetActorRotation(North);

		  }

		  if (Location.Y > TargetToliet->GetActorLocation().Y)
		  {
			  Location.Y -= MameMoveSpeed * DeltaTime;
			  YDifference = Location.Y - TargetToy->GetActorLocation().Y;
			  SetActorRotation(West);

		  }

		  else
		  {
			  Location.Y += MameMoveSpeed * DeltaTime;
			  YDifference = TargetToliet->GetActorLocation().Y - Location.Y;
			  SetActorRotation(East);
		  }

		  if (XDifference < 10 && YDifference < 10 && Bathroom == true)
		  {
			  MameDirection = EDirectionState::RELIEVING;
		  }
	  }


}

void AMamepetto::MamepettoEat()
{
	if (TargetFood->bHasBeenEaten == false && Energy <= 100 && Update == false)
	{

		PetState = "Eating";
		Energy += TargetFood->GetFoodValue();
		TargetFood->bHasBeenEaten = true;
		Eating = true;
		TargetFood->bHasBeenEaten = false;
		Update = true;

	}

	else if (Energy >= 100)
	{
		PetState = "Normal";
		Eating = false;
		Food = false;
		TargetFood->Destroy();
	}

}

void AMamepetto::MamepettoPlay()
{
	if (TargetToy->bHasBeenEaten == false && Mood <= 100 && Update == false)
	{
		PetState = "Playing";
		Mood += TargetToy->GetFoodValue();
		TargetToy->bHasBeenEaten = true;
		Playing = true;
		TargetToy->bHasBeenEaten = false;
		Update = true;
	}

	else if (Mood >= 100)
	{
		PetState = "Normal";
		Playing = false;
		Toy = false;
		TargetToy->Destroy();
	}

}

void AMamepetto::MamepettoToliet()
{


	if (TargetToliet->bHasBeenEaten == false && Toilet >= 0 && Update == false)
	{

		PetState = "Relieving";
		Toilet -= TargetToliet->GetFoodValue();
		TargetToliet->bHasBeenEaten = true;
		Exreeting = true;
		TargetToliet->bHasBeenEaten = false;
		Update = true;

	}

	if (Toilet <= 0)
	{
		PetState = "Normal";
		Exreeting = false;
		Bathroom = false;
		TargetToliet->Destroy();
	}

}

void AMamepetto::MamepettoExhaustion()
{
	if (Exhaustion >= 0 && Update == false)
	{
		Exhaustion = Exhaustion - 5;

		Update = true;
	}



}

void AMamepetto::CheckForFood()
{
	TSubclassOf<AActor> WorldClassObject = AFood::StaticClass();

	TArray<AActor*> Foods;


	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, Foods);

	if (Foods.Num() > 0 && Energy <= 50 && Eating == false)
	{
		PetState = "Hungry";
		Food = true;
		TargetFood = Cast<AFood>(Foods[0]);
		MameDirection = EDirectionState::GOTOLOC;


	}

	else if (Eating == true)
	{
		TargetFood = Cast<AFood>(Foods[0]);
		MameDirection = EDirectionState::EATING;


	}


}

void AMamepetto::CheckForToy()
{
	TSubclassOf<AActor> WorldClassObject = AToy::StaticClass();

	TArray<AActor*> Toys;


	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, Toys);

	if (Toys.Num() > 0 && Mood <= 50)
	{
		PetState = "Bored";
		Toy = true;
		TargetToy = Cast<AToy>(Toys[0]);
		MameDirection = EDirectionState::GOTOLOC;


	}
	else if ( Playing == true)
	{
		TargetToy = Cast<AToy>(Toys[0]);
		MameDirection = EDirectionState::PLAYING;


	}


}

void AMamepetto::CheckForToliet()
{
	TSubclassOf<AActor> WorldClassObject = AToliet::StaticClass();

	TArray<AActor*> Toliets;


	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, Toliets);

	if (Toliets.Num() > 0 && Toilet >= 60)
	{
		PetState = "Urgency";
		Bathroom = true;
		TargetToliet = Cast<AToliet>(Toliets[0]);
		MameDirection = EDirectionState::GOTOLOC;


	}

	if (Exreeting == true)
	{
		TargetToliet = Cast<AToliet>(Toliets[0]);
		MameDirection = EDirectionState::RELIEVING;


	}


}

void AMamepetto::CheckForExhaustion()
{

	if (Exhaustion >= 80 && Sleeping == false)
	{

		PetState = "Sleeping";
		Sleeping = true;
		SetActorRotation(Sleep);
	}

	if (Sleeping == true && Exhaustion <= 0)
	{
		PetState = "Normal";
		Sleeping = false;
		SetActorRotation(Awake);

	}

	if (Sleeping == true)
	{

		MameDirection = EDirectionState::RESTING;

	}


}

void AMamepetto::CheckStats()
{

	DeadConditions();
	if (Death == false)
	{

		if (Eating == false)
		{
			Energy--;
		}

		if (Sleeping == false)
		{
			Exhaustion++;
		}

		if (Playing == false)
		{
			Mood--;
		}

		if (Exreeting == false)
		{
			Toilet++;
		}

		if (Sleeping == true)
		{
			CheckForExhaustion();

		}

		if (Eating == true)
		{
			CheckForFood();


		}

		if (Playing == true)
		{
			CheckForToy();


		}
#
		if (Exreeting == true)
		{
			CheckForToliet();


		}

		else
		{

			MameDirection = EDirectionState(FMath::RandRange(0, 8));
			CheckForFood();
			CheckForToliet();
			CheckForToy();
			CheckForExhaustion();
		}
	}

}

void AMamepetto::DeadConditions()
{
	if (Energy < 0 || Mood < 0 || Exhaustion > 100)
	{
		MameDirection = EDirectionState::DEAD;

	}

}

void AMamepetto::DeadState()
{

	SetActorRotation(Dead);
	PetState = "Dead";

}

float AMamepetto::GetMamepettoEnergy()
{
	return Energy;
}

float AMamepetto::GetMamepettoExhaustion()
{
	return Exhaustion;
}

float AMamepetto::GetMamepettoMood()
{
	return Mood;
}

float AMamepetto::GetMamepettoToilet()
{
	return Toilet;
}



// Called when the game starts or when spawned
void AMamepetto::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello Petto"))
	
}

// Called every frame
void AMamepetto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UpdateTick >= MameUpdateSpeed)
	{
		Update = false;
		UpdateTick = 0;
		CheckStats();


	}
	Movement(DeltaTime);

	UpdateTick++;

}

