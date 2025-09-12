

#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainMenu.h"
#include "UI/PauseMenu.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My Session Name");

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
	
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	if (Subsystem != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,FString::Printf(TEXT("Found Subsystem: %s"), *Subsystem->GetSubsystemName().ToString()));
		
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
		}
	}
}

void UPuzzlePlatformsGameInstance::Host() const
{
	if (SessionInterface.IsValid())
	{
		const auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			const FOnlineSessionSettings SessionSettings;
			SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		}
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, const bool Success)
{
	if (!Success) return;
	
	if (MainMenu)
	{
		MainMenu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hosting Game");

	GetWorld()->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		if (SessionInterface.IsValid())
		{
			const FOnlineSessionSettings SessionSettings;
			SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		}
	}
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


