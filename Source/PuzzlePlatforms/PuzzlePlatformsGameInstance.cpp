

#include "PuzzlePlatformsGameInstance.h"

#include "LevelEditorMenuContext.h"
#include "Blueprint/UserWidget.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	MainMenuBpClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::Host() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hosting Game");

	GetWorld()->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IP) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Joining Game at %s"), *IP));

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->ClientTravel(IP, TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MainMenuBpClass)
	{
		UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, MainMenuBpClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();

			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PlayerController->SetInputMode(InputMode);
				PlayerController->bShowMouseCursor = true;
			}
			
		}
	}
}

