// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/**	Interactable Interface
 * 
 * When an ActorComponent or SceneComponent implements this interface, the InteractionSubsystem 
 * will call the OnInteract() method so that each Component can provide its own implementation of
 * being interacted with!
 */
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT01_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInteract();
};
