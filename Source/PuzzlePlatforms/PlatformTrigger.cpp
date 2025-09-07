

#include "PlatformTrigger.h"

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	RootComponent = BoxComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(BoxComponent);
}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	for (const auto Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Actor %s has entered the trigger"), *OtherActor->GetName()));
}

void APlatformTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	for (const auto Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Actor %s has exited the trigger"), *OtherActor->GetName()));
}

