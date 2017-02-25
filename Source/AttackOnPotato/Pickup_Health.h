// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Pickup_Health.generated.h"

/**
 * 
 */
UCLASS()
class ATTACKONPOTATO_API APickup_Health : public APickup
{
	GENERATED_BODY()
	
	
public:
	APickup_Health();
	
	void Collect_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	int iHealthValue;
private:

};
