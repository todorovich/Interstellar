// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataSingleton.generated.h"

/**
 * 
 */
UCLASS()
class INTREPID_API UDataSingleton : public UObject
{
	GENERATED_BODY()

public:
	UDataSingleton(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	static UDataSingleton* const Instance();

private:
	static UDataSingleton* _instance;
};
