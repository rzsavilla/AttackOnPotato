// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "Pickup_Speed.h"
#include "AttackOnPotatoCharacter.h"

APickup_Speed::APickup_Speed()
{
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	fSpeed = 5000.0f;
	fDuration = 2.0f;
	sType = "Speed";
}

void APickup_Speed::Collect_Implementation() {
	Super::Collect_Implementation();

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAttackOnPotatoCharacter* character = Cast<AAttackOnPotatoCharacter>(myCharacter);

	character->boostSpeed(fSpeed, fDuration);

	//Destroy the pickup
	Destroy();
}