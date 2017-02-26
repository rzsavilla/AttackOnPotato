// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Multiplier.h"

APickup_Multiplier::APickup_Multiplier() 
{
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void APickup_Multiplier::Collect_Implementation()
{
	Super::Collect_Implementation();

	//Destroy the pickup
	Destroy();
}
