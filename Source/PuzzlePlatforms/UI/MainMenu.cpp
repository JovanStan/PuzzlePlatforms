
#include "MainMenu.h"

#include "Components/Button.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hosting Game");
}

void UMainMenu::JoinButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Joining Game");
}
