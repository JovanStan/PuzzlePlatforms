
#include "MainMenu.h"

#include "Components/Button.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameInstance.h"

void UMainMenu::Setup()
{
	this->AddToViewport();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}

void UMainMenu::Teardown()
{
	this->RemoveFromParent();
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}

bool UMainMenu::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);

	return true;
}

void UMainMenu::HostButtonClicked()
{
	if (const UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()))
	{
		GameInstance->Host();
	}
}

void UMainMenu::JoinButtonClicked()
{
	if (const UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()))
	{
		//GameInstance->Join();
	}
}
