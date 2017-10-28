// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntrepidGameModeBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INTREPID_API AMasterGameMode : public AIntrepidGameModeBase
{
	GENERATED_BODY()

	UWorld* virtual_world;
	
	virtual void FinishDestroy() override;

	virtual void BeginPlay() override;
	
};
