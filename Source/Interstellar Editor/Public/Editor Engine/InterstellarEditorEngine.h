// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "InterstellarEditor.h"
#include "UnrealEd.h"
#include "InterstellarEditorEngine.generated.h"

/**
 * 
 */
UCLASS()
class INTERSTELLAREDITOR_API UInterstellarEditorEngine : public UUnrealEdEngine
{
	GENERATED_BODY()
	
	UInterstellarEditorEngine(const FObjectInitializer& ObjectInitializer)
	{
		WARNING("Interstellar Editor Engine Started.");
	}
};
