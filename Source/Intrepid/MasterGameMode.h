// Copyright 2017 Micho Todorovich, all rights reserved.

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
