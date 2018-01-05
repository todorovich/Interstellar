// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"
#include "InterstellarEngine.generated.h"

/**
 * 
 */
UCLASS()
class INTERSTELLAR_API UInterstellarEngine : public UEngine
{
	GENERATED_BODY()
	
	UInterstellarEngine(const FObjectInitializer& ObjectInitializer)
	{
		LOG("Interstellar Engine Started.");
	}
};
