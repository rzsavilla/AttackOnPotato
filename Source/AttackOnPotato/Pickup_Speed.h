// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Pickup_Speed.generated.h"

/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APickup_Speed : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_Speed();

	void Collect_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float fDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float fSpeed;
};
