// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceShipComponent.generated.h"


UCLASS( ClassGroup=(SpaceShipComponents), meta=(BlueprintSpawnableComponent) )
class INTREPID_API USpaceShipComponent : public USceneComponent
{
	GENERATED_BODY()

	bool bIsDisabled = false;

public:	
	// Sets default values for this component's properties
	//USpaceShipComponent(int MaximumStructurePointsIn = 2, int CurrentStructurePointsIn = 2, int SystemDisabledThreshold = 1);

	USpaceShipComponent();

	UPROPERTY(EditAnywhere)
	int MaximumStructurePoints = 0;

	UPROPERTY(EditAnywhere)
	int CurrentStructurePoints = 0;
	
	UPROPERTY(EditAnywhere)
	int SystemDisabledThreshold = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
