// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameMode.h"
#include "IntrepidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INTREPID_API AIntrepidGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIntrepidGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual TSubclassOf<AGameSession> GetGameSessionClass() const;
};
