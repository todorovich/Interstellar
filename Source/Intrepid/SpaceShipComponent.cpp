// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShipComponent.h"

//// Sets default values for this component's properties
//USpaceShipComponent::USpaceShipComponent(int MaximumStructurePointsIn, int CurrentStructurePointsIn, int SystemDisabledThreshold)
//	: MaximumStructurePoints(MaximumStructurePointsIn)
//	, CurrentStructurePoints(CurrentStructurePointsIn)
//	, SystemDisabledThreshold(SystemDisabledThreshold)
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}

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

