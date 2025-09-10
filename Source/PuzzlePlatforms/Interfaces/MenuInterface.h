
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

UINTERFACE()
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};


class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Host() = 0;
};
