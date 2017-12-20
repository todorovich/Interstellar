// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"
#include "Blueprint/UserWidget.h"
#include "DesignableUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class INTERSTELLAR_API UDesignableUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "User Interface")
	void OnSynchronizeProperties();	

	virtual void SynchronizeProperties() override;
};
