
#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
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
	OpenJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenuButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelButtonClicked);
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGameButtonClicked);

	return true;}

void UMainMenu::HostButtonClicked()
{
	if (const UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()))
	{
		GameInstance->Host();
	}
}

void UMainMenu::OpenJoinMenuButtonClicked()
{
	if (WidgetSwitcher && JoinMenuWidget)
	{
		WidgetSwitcher->SetActiveWidget(JoinMenuWidget);
	}
}

void UMainMenu::CancelButtonClicked()
{
	if (WidgetSwitcher && MainMenuWidget)
	{
		WidgetSwitcher->SetActiveWidget(MainMenuWidget);
	}
}

void UMainMenu::JoinGameButtonClicked()
{
	if (const UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()))
	{
		const FString& Address = EditableTextBox->GetText().ToString();
		GameInstance->Join(Address);
	}
}
