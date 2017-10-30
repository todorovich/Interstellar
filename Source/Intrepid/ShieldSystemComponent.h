// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShipComponent.h"
#include "ShieldSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShieldsChanged, int32, Number, FString, String);

/**
 *	Component Representing a Shield System
 */
UCLASS(BlueprintType, ClassGroup = (SpaceShipComponents), meta = (BlueprintSpawnableComponent))
class INTREPID_API UShieldSystemComponent : public USpaceShipComponent
{
	GENERATED_BODY()
	
public:

	UShieldSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	MaxShieldPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	CurrentShieldPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	RechargePoints;

	UPROPERTY(EditAnywhere)
	float	Hardness;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Returns Amount of Damage not Taken
	virtual float TakeDamage(float DamageAmount, int DamageType = 0);

	UPROPERTY(BlueprintAssignable, Category = "Shields")
	FShieldsChanged  OnShieldsChanged;

protected:

};
