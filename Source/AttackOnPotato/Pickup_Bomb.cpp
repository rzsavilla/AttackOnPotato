// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Bomb.h"

APickup_Bomb::APickup_Bomb() 
{
	GetMesh()->SetSimulatePhysics(true);
}

void APickup_Bomb::Collect_Implementation()
{
	Super::Collect_Implementation();

	//Destroy the pickup
	Destroy();
}
