// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "GameFramework\Character.h"
#include "BadPotato.h"

//void ABadPotato::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser, bool bKilled)
//{
//}

ABadPotato::ABadPotato(const FObjectInitialize & ObjectInitializer) : Super(ObjectInitializer)
{
	//sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;

	/* Ignore this channel or it will absorb the trace impacts instead of the skeletal mesh */
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f, false);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);

	/* These values are matched up to the CapsuleComponent above and are used to find navigation paths */
	GetMovementComponent()->NavAgentProps.AgentRadius = 42;
	GetMovementComponent()->NavAgentProps.AgentHeight = 192;


	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->SetRelativeLocation(FVector(45, 0, 25));
	MeleeCollisionComp->SetCapsuleHalfHeight(60);
	MeleeCollisionComp->SetCapsuleRadius(35, false);
	MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeCollisionComp->SetupAttachment(GetCapsuleComponent());

	Health = 100;
	MeleeDamage = 24.0f;
	MeleeStrikeCooldown = 1.0f;
	SprintingSpeedModifier = 3.0f;


}


void ABadPotato::BeginPlay()
{
	Super::BeginPlay();

	//binds the delegates to the component

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ABadPotato::OnSeePlayer);
	}
	if (MeleeCollisionComp)
	{
		MeeleCollisionComp->OnComponentBeginOverlap.AddDynamic(This, &ABadPotato::OnMeleeCompBeginOverlap);
	}
}

//void ABadPotato::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaSeconds);
	// implement if we need to stop the characters from endless following
//}

//bool ABadPotato::IsSprinting() const
//{
	//return false;
//}

void ABadPotato::OnSeePlayer(APawn * Pawn)
{
	if (!IsAlive())
	{
		return;
	}

	bSensedTarget = true;

	APotatoAIController* AIController = Cast<ABadPotato>(GetController());
	ABaseCharacter* SensedPawn = Cast<ABaseCharacter>(Pawn); // change to adapt to the player class
	if (AIController && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(SensedPawn);
	}
}

/*void ABadPotato::OnMeleeCompBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	stop any timers
	TimerHandle_MeleeAttack.Invalidate();

	PerformMeleeStrike(OtherActor);

	//set re trigger timer to recheck overlapping pawns at melee attack rate interval
	GetWorldTimerManager().SetTimer(TimerHandle_MeleeAttack, this, &ABadPotato::OnRetriggerMeleeStrike, MeleeStrikeCooldown, true);
}

void ABadPotato::OnRetriggerMeleeStrike()
{
	// apply damage
	//TO DO: 
	  Apply damage to a single random pawn in range. 
	TArray<AActor*> Overlaps;
	MeleeCollisionComp->GetOverlappingActors(Overlaps, ASBaseCharacter::StaticClass());
	for (int32 i = 0; i < Overlaps.Num(); i++)
	{
		ASBaseCharacter* OverlappingPawn = Cast<ASBaseCharacter>(Overlaps[i]);
		if (OverlappingPawn)
		{
			PerformMeleeStrike(OverlappingPawn);
			//break; /* Uncomment to only attack one pawn maximum 
		}
	}

	No pawns in range, cancel the retrigger timer 
	if (Overlaps.Num() == 0)
	{
		TimerHandle_MeleeAttack.Invalidate();
	}
}

void ABadPotato::PerformMeleeStrike(AActor * HitActor)
{
	if (LastMeeleAttackTime > GetWorld->GetTimeSeconds() - MeleeStrikeCooldown)
	{

		//set the timer to start attacking
		if (!TimerHandle_MeleeAttack.IsValid())
		{
			// set timer?
		}
	}

	if (HitActor && HitActor != && IsAlive())
	{
		ACharcter * OtherPawn = Cast<ACharacter>(HitActor);
		if (OtherPawn)
		{
			// get team number, don't attack the other zombies
			// TO DO A Base Class for States
		}

		//prevent zombies from attacking multiple times instantly
		LastMeleeAttackTime = GetWorld()->GetTimeSeconds();

		FPointDamageEvent DmgEvent;
		DmgEvent.DamageTypeClass = PunchDamageType;
		DmgEvent.Damage = MeleeDamage;

		HitActor->TakeDamage(DmgEvent.Damage, DmgEvent, GetController(), this);

		SimulateMeeleStriker(); // animation
	}
	
}

void ABadPotato::SimulateMeleeStrike()
{
}

void ABadPotato::SimulateMeleeStrike_Implementation()
{
	//PlayAnimMontage(MeleeAnimMontage);
}*/

void ABadPotato::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;

	APotatoAIController* AIController = Cast<ABadPotato>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}

}