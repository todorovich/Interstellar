// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataSingleton.generated.h"

class IAssetRegistry;

/**
 * 
 */
UCLASS()
class INTREPID_API UDataSingleton : public UObject
{
	GENERATED_BODY()

public:
	//UDataSingleton(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	static UDataSingleton* Instance();

	static IAssetRegistry* GetAssetRegistry();

private:
	static UDataSingleton* _instance;
	IAssetRegistry* _assetRegistry;
};
