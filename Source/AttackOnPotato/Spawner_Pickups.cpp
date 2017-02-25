// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Spawner_Pickups.h"
#include "Pickup.h"
#include "Kismet/KismetMathLibrary.h"	//For FRANDRANGE

// Sets default values
ASpawner_Pickups::ASpawner_Pickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create box component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawwn"));
	RootComponent = WhereToSpawn;	//Set box as root component

	//Set Default values
	fSpawnDelayMin = 1.0f;
	fSpawnDelayMax = 2.0f;
}

// Called when the game starts or when spawned
void ASpawner_Pickups::BeginPlay()
{
	Super::BeginPlay();

	fSpawnDelay = FMath::FRandRange(fSpawnDelayMin, fSpawnDelayMax);

	//Will timed random spawn
	//GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawner_Pickups::SpawnPickup, fSpawnDelay, false);
}

// Called every frame
void ASpawner_Pickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawner_Pickups::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawner_Pickups::spawnMultiple(int num)
{
	for (int i = 0; i < num; i++) {
		//If something is set to spawwn:
		if (WhatToSpawn != NULL) {
			//Check for valid world:
			UWorld* const World = GetWorld();
			if (World) {
				//Set spawn parameters
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;

				//Get a random location to spawn at
				FVector SpawnLocation = GetRandomPointInVolume();

				//Get a random rotation for the spawned item
				FRotator SpawnRotation;
				SpawnRotation.Yaw = FMath::FRand() * 360.0f;
				SpawnRotation.Pitch = FMath::FRand() * 360.0f;
				SpawnRotation.Roll = FMath::FRand() * 360.0f;

				//Spawn pickup
				APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
	}
}

void ASpawner_Pickups::Spawn()
{
	spawnMultiple(iSpawnCount);
}

void ASpawner_Pickups::setSpawnCount(int num)
{
	iSpawnCount = num;
}

void ASpawner_Pickups::SpawnPickup() 
{
	//If something is set to spawwn:
	if (WhatToSpawn != NULL) {
		//Check for valid world:
		UWorld* const World = GetWorld();
		if (World) {
			//Set spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Get a random location to spawn at
			FVector SpawnLocation = GetRandomPointInVolume();

			//Get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			//Spawn pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			//Reset spawn timer
			fSpawnDelay = FMath::FRandRange(fSpawnDelayMin, fSpawnDelayMax);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawner_Pickups::SpawnPickup, fSpawnDelay, false);
		}
	}
}