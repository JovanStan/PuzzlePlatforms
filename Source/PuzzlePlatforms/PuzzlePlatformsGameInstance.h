
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"


class UPauseMenu;
class UMainMenu;

UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host() const;
	UFUNCTION(Exec)
	void Join(const FString& IP) const;
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu();

private:
	TSubclassOf<UUserWidget> MainMenuBpClass;
	TSubclassOf<UUserWidget> PauseMenuBPClass;
	
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenu;
	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenu;
};
