
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	void Teardown();

	UFUNCTION()
	void CancelButtonPressed();
	UFUNCTION()
	void QuitGameButtonPressed();

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CancelButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitGameButton;

protected:
	virtual bool Initialize() override;
};
