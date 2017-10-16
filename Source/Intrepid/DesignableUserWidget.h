// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DesignableUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class INTREPID_API UDesignableUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "User Interface")
	void OnSynchronizeProperties();	

	virtual void SynchronizeProperties() override;
};
