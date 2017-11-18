// Copyright 2017 Micho Todorovich, all rights reserved.

#include "SpaceShipComponent.h"

USpaceShipComponent::USpaceShipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpaceShipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USpaceShipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentStructurePoints <= SystemDisabledThreshold)
	{
		bIsDisabled = true;
	}
	else
	{
		bIsDisabled = false;
	}
}

