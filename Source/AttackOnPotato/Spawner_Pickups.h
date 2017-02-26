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

	/**  Spawn specified pickups in box*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void Spawn();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void setSpawnCount(int num);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Determines pickup to be spawned*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	/** Minimum Spawn Delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float fSpawnDelayMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float fSpawnDelayMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bInfiniteSpawn;
private:
	/** Used to specify where pickups will spawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))
	class UBoxComponent* WhereToSpawn;

	/** Spawn a new pickup*/
	void SpawnPickup();

	/** Current spawn delay */
	float fSpawnDelay;

	/** Number of pickups to spawn */
	int iSpawnCount;

	void spawnMultiple(int num);
};
