// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InterstellarGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INTERSTELLAR_API UInterstellarGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void StartGameInstance() override;

#if WITH_EDITOR
	/* Called to actually start the game when doing Play/Simulate In Editor */
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params);
#endif
};
