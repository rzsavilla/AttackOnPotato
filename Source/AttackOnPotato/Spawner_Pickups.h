// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawner_Pickups.generated.h"

UCLASS()
class ATTACKONPOTATO_API ASpawner_Pickups : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner_Pickups();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	/** Returns a random point within the box component */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	/** Minimum Spawn Delay */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float fSpawnDelayMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float fSpawnDelayMax;
private:
	/** Used to specify where pickups will spawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))
	class UBoxComponent* WhereToSpawn;

	/** Spawn a new pickup*/
	void SpawnPickup();

	/** Current spawn delay */
	float fSpawnDelay;
};
