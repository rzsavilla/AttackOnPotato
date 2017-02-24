// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AttackOnPotato.h"
#include "AttackOnPotatoGameMode.h"
#include "AttackOnPotatoPawn.h"

AAttackOnPotatoGameMode::AAttackOnPotatoGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAttackOnPotatoPawn::StaticClass();
}

