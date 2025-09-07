
#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"


UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	virtual void Tick(float DeltaSeconds) override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Speed = 20.0f;
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true))
	FVector TargetLocation;

private:
	UPROPERTY()
	FVector GlobalTargetLocation;
	UPROPERTY()
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	
};
