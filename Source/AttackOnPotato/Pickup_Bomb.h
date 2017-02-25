// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Pickup_Bomb.generated.h"

/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APickup_Bomb : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_Bomb();
	void Collect_Implementation() override;
};
