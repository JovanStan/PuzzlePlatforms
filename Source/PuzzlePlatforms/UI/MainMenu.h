
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UEditableTextBox;
class UWidgetSwitcher;
class IMenuInterface;
class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	void Teardown();
	
protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> HostButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> OpenJoinMenuButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> CancelButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> JoinGameButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UEditableTextBox> EditableTextBox;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UWidget> MainMenuWidget;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UWidget> JoinMenuWidget;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void OpenJoinMenuButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();
	UFUNCTION()
	void JoinGameButtonClicked();
	
};
