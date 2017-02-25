// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Potato.h"

APickup_Potato::APickup_Potato() 
{
	GetMesh()->SetSimulatePhysics(true);
}

void APickup_Potato::Collect_Implementation()
{
	Super::Collect_Implementation();

	//Destroy the pickup
	Destroy();
}