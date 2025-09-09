

#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hosting Game");

	GetWorld()->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IP)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Joining Game at %s"), *IP));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->ClientTravel(IP, TRAVEL_Absolute);
	}
}

