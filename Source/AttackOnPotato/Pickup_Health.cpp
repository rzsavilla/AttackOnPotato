// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Health.h"

APickup_Health::APickup_Health() 
{
	GetMesh()->SetSimulatePhysics(true);
}