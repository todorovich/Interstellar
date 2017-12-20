// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShipComponent.h"
#include "ShieldSystemComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShieldsChanged)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShieldsChanged);

/**
 *	Component Representing a Shield System
 */
UCLASS(BlueprintType, ClassGroup = (SpaceShipComponents), meta = (BlueprintSpawnableComponent))
class INTREPID_API UShieldSystemComponent : public USpaceShipComponent
{
	GENERATED_BODY()
	
public:

	/** Broadcasts whenever the layer changes */
	//DECLARE_EVENT(UShieldSystemComponent, FShieldsChanged)
	//FShieldsChanged& OnShieldsChanged() { return _OnShieldsChanged; }

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

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FShieldsChanged OnShieldsChanged;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:


	//UPROPERTY()
	//FShieldsChanged  OnShieldsChanged;
};
