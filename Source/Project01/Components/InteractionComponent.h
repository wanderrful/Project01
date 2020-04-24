// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project01/Interfaces/Interactable.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT01_API UInteractionComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/// IInteractable
	// This method is called when the player interacts with the parent Actor!
	// TODO | Maybe use an Event Delegate so that the parent Actor can bind to this, if it's a Blueprint?
	void OnInteract_Implementation() override;
};
