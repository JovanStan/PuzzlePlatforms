
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"


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

private:
	TSubclassOf<UUserWidget> MainMenuBpClass;
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenu;
};
