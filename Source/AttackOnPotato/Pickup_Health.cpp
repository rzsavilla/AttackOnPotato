// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Health.h"
#include "AttackOnPotatoCharacter.h"

APickup_Health::APickup_Health()
{
	GetMesh()->SetSimulatePhysics(true);
	iHealthValue = 10;
	sType = "Health";
}

void APickup_Health::Collect_Implementation()
{
	Super::Collect_Implementation();

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAttackOnPotatoCharacter* character = Cast<AAttackOnPotatoCharacter>(myCharacter);

	character->addHealth(iHealthValue);

	//Destroy the pickup
	Destroy();
}