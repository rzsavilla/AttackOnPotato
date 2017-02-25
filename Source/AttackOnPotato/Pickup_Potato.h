// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Pickup_Potato.generated.h"

/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APickup_Potato : public APickup
{
	GENERATED_BODY()

public:
	//Constructor
	APickup_Potato();


	void Collect_Implementation() override;
	
};
