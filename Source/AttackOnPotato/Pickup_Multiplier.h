// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Pickup_Multiplier.generated.h"

/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APickup_Multiplier : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_Multiplier();

	void APickup_Multiplier::Collect_Implementation();


	FString sType;
private:
	
};
