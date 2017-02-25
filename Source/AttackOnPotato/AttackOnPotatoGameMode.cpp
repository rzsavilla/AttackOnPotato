// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AttackOnPotato.h"
#include "AttackOnPotatoGameMode.h"
#include "AttackOnPotatoCharacter.h"

AAttackOnPotatoGameMode::AAttackOnPotatoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/AttackOnPotato/Blueprints/BP_AttackOnPotatoCharacter.BP_AttackOnPotatoCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

