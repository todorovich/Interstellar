// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldSystemComponent.h"

UShieldSystemComponent::UShieldSystemComponent()
{

}


void UShieldSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentShieldPoints += RechargePoints * DeltaTime;

	if (CurrentShieldPoints > MaxShieldPoints)
	{
		CurrentShieldPoints = MaxShieldPoints;
	}
};

float UShieldSystemComponent::TakeDamage(float DamageAmount, int DamageType)
{
	auto RemainingDamage = 0.0f;

	// Sufficient Hardness to Soak it all
	if (DamageAmount >= Hardness)
	{
		// Enough Shields
		if (CurrentShieldPoints >= DamageAmount)
		{
			CurrentShieldPoints -= DamageAmount;
			RemainingDamage = 0.0f;
		}
		// Not enough shields
		else
		{
			RemainingDamage = DamageAmount - CurrentShieldPoints;
			CurrentShieldPoints = 0.0f;
		}

	}
	// Insufficient Hardness to Soak it all;
	else
	{
		// Enough Shields to Soak Hardness Amount
		if (CurrentShieldPoints >= Hardness)
		{
			RemainingDamage = DamageAmount - Hardness;
			CurrentShieldPoints -= Hardness;
		}
		// Not enough to soak hardness
		else
		{
			RemainingDamage = DamageAmount - CurrentShieldPoints;
			CurrentShieldPoints = 0.0f;
		}
	}

	return RemainingDamage;
};