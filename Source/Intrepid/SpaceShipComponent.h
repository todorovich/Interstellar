// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceShipComponent.generated.h"


UCLASS(BlueprintType, ClassGroup=(SpaceShipComponents), meta=(BlueprintSpawnableComponent) )
class INTREPID_API USpaceShipComponent : public USceneComponent
{
	GENERATED_BODY()

	bool bIsDisabled = false;

public:	
	// Sets default values for this component's properties
	//USpaceShipComponent(int MaximumStructurePointsIn = 2, int CurrentStructurePointsIn = 2, int SystemDisabledThreshold = 1);

	USpaceShipComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumStructurePoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentStructurePoints = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SystemDisabledThreshold = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
