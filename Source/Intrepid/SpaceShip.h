// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ShieldSystemComponent.h"
#include "GameFramework/Actor.h"
#include "SpaceShip.generated.h"

UCLASS()
class INTREPID_API ASpaceShip : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	int max_structure_points = 0;

	UPROPERTY(EditAnywhere)
	int current_structure_points = 0;

	class UShieldSystemComponent* shields;

	// Sets default values for this actor's properties
	ASpaceShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void CreateGrid();

};
