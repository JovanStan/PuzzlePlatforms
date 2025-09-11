
#include "PauseMenu.h"

#include "Components/Button.h"

void UPauseMenu::Setup()
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

void UPauseMenu::Teardown()
{
	this->RemoveFromParent();
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}

bool UPauseMenu::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::CancelButtonPressed);
	QuitGameButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitGameButtonPressed);

	return true;
}

void UPauseMenu::CancelButtonPressed()
{
	Teardown();
}

void UPauseMenu::QuitGameButtonPressed()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		Teardown();
		PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", TRAVEL_Absolute);
	}
}
