// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShipComponent.h"
#include "ShieldSystemComponent.generated.h"

/**
 *	Component Representing a Shield System
 */
UCLASS()
class INTREPID_API UShieldSystemComponent : public USpaceShipComponent
{
	GENERATED_BODY()
	
public:

	//UShieldSystemComponent(int	MaxShieldPointsIn = 10, int CurrentShieldPointsIn = 10, int RechargePointsIn = 1, int HardnessIn = 1,
	//	int MaximumStructurePointsIn = 4, int CurrentStructurePointsIn = 4, int SystemDisabledThresholdIn = 1)
	//	: USpaceShipComponent(MaximumStructurePointsIn, CurrentStructurePointsIn, SystemDisabledThresholdIn)
	//	, MaxShieldPoints(MaxShieldPointsIn)
	//	, CurrentShieldPoints(CurrentShieldPointsIn)
	//	, RechargePoints(RechargePointsIn)
	//	, Hardness(HardnessIn)
	//{
	//};

	UShieldSystemComponent();

	UPROPERTY(EditAnywhere)
	float	MaxShieldPoints;
	
	UPROPERTY(EditAnywhere)
	float	CurrentShieldPoints;
	
	UPROPERTY(EditAnywhere)
	float	RechargePoints;

	UPROPERTY(EditAnywhere)
	float	Hardness;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Returns Amount of Damage not Taken
	virtual float TakeDamage(float DamageAmount, int DamageType = 0);

protected:

};
