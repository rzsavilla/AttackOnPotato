// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "AttackOnPotatoCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Pickup.h"
#include "ThrownProjectile.h"


// Sets default values
AAttackOnPotatoCharacter::AAttackOnPotatoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/AttackOnPotato/Textures/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Create Collection Shere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetSphereRadius(200.0f);
	//Set Collection sphere for on overlap
	CollectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAttackOnPotatoCharacter::OnOverlap);
	CollectionSphere->SetupAttachment(RootComponent);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	fSpeedBoostDuration = 0.0f;	//Time until speed boost ends
	iNormalSpeed = 250.0f;
	iMaxSpeed = 500.0f;
	iHealth = 10;
	iMaxHealth = 10;
}

// Called every frame
void AAttackOnPotatoCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params;
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AAttackOnPotatoCharacter::setTwoMultiplier(bool state)
{
	bMultiplierTwo = state;
}

void AAttackOnPotatoCharacter::setFiveMultiplier(bool state)
{
	bMultiplierFive = state;
}

void AAttackOnPotatoCharacter::setThreeMultiplier(bool state)
{
	bMultiplierTen = state;
}

void AAttackOnPotatoCharacter::throwBomb()
{
	// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			// Get the camera transform
			FVector CameraLoc;
			FRotator CameraRot;
			GetActorEyesViewPoint(CameraLoc, CameraRot);
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
			//FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
			FVector const MuzzleLocation = CameraLoc;
			//MuzzleLocation = CameraLoc
			FRotator MuzzleRotation = CameraRot;
			MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
			UWorld* const World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;
				// spawn the projectile at the muzzle
				UThrownProjectile* const Projectile = World->SpawnActor<UThrownProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				if (Projectile)
				{
					// find launch direction
					FVector const LaunchDir = MuzzleRotation.Vector();
					//Projectile->InitVelocity(LaunchDir);
				}
			}
		}
}

//Player will collect pickups within collection sphere
void AAttackOnPotatoCharacter::CollectPickups()
{
	//Get All overlapping actors and store into array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	//Iterate through array (Foreach actor to collect)
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected) {
		//Cast actor to APickup
		APickup* const TestPickup = Cast<APickup>(CollectedActors[iCollected]);
		//If Cast successful
		//If Pickup valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			NotifyType(TestPickup->GetSType());
			TestPickup->Collect();	//Call the Collect function
			//Deactivate pickup
			TestPickup->SetActive(false);	//Prevent spam collections
		}
	}
}

void AAttackOnPotatoCharacter::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APickup::StaticClass())) {
		APickup* pickup = Cast<APickup>(OtherActor);
		NotifyType(pickup->GetSType());
		pickup->Collect();	//Collect Pickup
	}
}

void AAttackOnPotatoCharacter::setHealth(int newHealth) {
	iHealth = newHealth;
}

void AAttackOnPotatoCharacter::addHealth(int health) {
	if ((iHealth + health) > iMaxHealth) {
		iHealth = iMaxHealth;
	}
	else {
		iHealth += health;
	}
}

void AAttackOnPotatoCharacter::setMaxHealth(int newMaxHealth) {
	iMaxHealth = newMaxHealth;
}

void AAttackOnPotatoCharacter::setSpeed(int newSpeed) {
	iSpeed = newSpeed;
	GetCharacterMovement()->MaxWalkSpeed = newSpeed;
}

void AAttackOnPotatoCharacter::boostSpeed() {
	GetCharacterMovement()->MaxWalkSpeed = iMaxSpeed;
	//fSpeedBoostDuration = duration;

	//Timer to end speed boost
	//GetWorldTimerManager().SetTimer(SpeedBoostTimer, this, &AAttackOnPotatoCharacter::endSpeedBoost, fSpeedBoostDuration, false);
}

void AAttackOnPotatoCharacter::addBomb(int iNum)
{
}

void AAttackOnPotatoCharacter::setMaxBomb(int iNum)
{

}

void AAttackOnPotatoCharacter::setMaxSpeed(int newSpeed) {
	iMaxSpeed = newSpeed;
}

void AAttackOnPotatoCharacter::endSpeedBoost() {
	GetCharacterMovement()->MaxWalkSpeed = iNormalSpeed;
}