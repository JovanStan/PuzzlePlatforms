
#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}
 

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			const float Length = (GlobalTargetLocation - GlobalStartLocation).Size();
			const float Traveled = (Location - GlobalStartLocation).Size();
		
			if ( Traveled >= Length)
			{
				const FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			const FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Direction * Speed * DeltaSeconds;
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
