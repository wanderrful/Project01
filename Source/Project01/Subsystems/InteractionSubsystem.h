// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InteractionSubsystem.generated.h"

class IInteractable;

UCLASS()
class UInteractionSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UInteractionSubsystem();

	AActor *GetTarget();
	bool SetTarget(AActor *target);
	void UpdateTarget();

public:
	void OnInteract();

private:
	void _StartTimer();
	void _OnInteract();

public:
	FORCEINLINE static float GetInteractionDistance() { return 200.f; }

private:
	/* The Actor we will attempt to interact with */
	AActor *Target;

	FTimerHandle InteractionUpdateTimer;
};
