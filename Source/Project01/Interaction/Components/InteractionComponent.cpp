// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "Project01/Project01.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::OnInteract_Implementation()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, TEXT("UInteractionComponent::OnInteract >> Hello!"));
}