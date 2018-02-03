// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SharedPointer.h"
#include "LevelEditorViewport.h"
#include "LevelEditorViewportClient.h"
#include "InterstellarLevelEditorViewportClient.generated.h"

class USlateBrushAsset;

UCLASS(BlueprintType)
class INTERSTELLAREDITOR_API UInterstellarLevelEditorViewportClient : public ULevelEditorViewportClient
{
	GENERATED_BODY()

public:

	UInterstellarLevelEditorViewportClient(const FObjectInitializer& ObjectInitializer);
	
	virtual TSharedPtr<class FLevelEditorViewportClient> Construct(TSharedPtr<class SLevelViewport> LevelViewport) override;
	
	virtual ~UInterstellarLevelEditorViewportClient() = default;

};


