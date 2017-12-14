// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IntrepidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INTREPID_API UIntrepidGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void StartGameInstance() override;

	/* Called to actually start the game when doing Play/Simulate In Editor */
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params);

	
};
