// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "ThrownProjectile.h"

UThrownProjectile::UThrownProjectile()
{
	this->InitialSpeed = 3000.0f;
	this->MaxSpeed = 3000.0f;
	this->bRotationFollowsVelocity = true;
	this->bShouldBounce = true;
	this->Bounciness = 0.3f;
}