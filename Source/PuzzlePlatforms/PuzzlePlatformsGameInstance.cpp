

#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainMenu.h"
#include "UI/PauseMenu.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	MainMenuBpClass = MenuBPClass.Class;
	
	const ConstructorHelpers::FClassFinder<UUserWidget> PauseBPClass(TEXT("/Game/MenuSystem/WBP_Pause"));
	PauseMenuBPClass = PauseBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::Host() const
{
	if (MainMenu)
	{
		MainMenu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hosting Game");

	GetWorld()->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IP) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Joining Game at %s"), *IP));
	if (MainMenu)
	{
		MainMenu->Teardown();
	}
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->ClientTravel(IP, TRAVEL_Absolute);
	}
}



void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MainMenuBpClass)
	{
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuBpClass);
		if (MainMenu)
		{
			MainMenu->Setup();
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadPauseMenu()
{
	if (PauseMenuBPClass)
	{
		PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuBPClass);
		if (PauseMenu)
		{
			PauseMenu->Setup();
		}
	}
}

