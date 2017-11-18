// Fill out your copyright notice in the Description page of Project Settings.

#include "DataSingleton.h"
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "Runtime/AssetRegistry/Public/IAssetRegistry.h"

UDataSingleton* UDataSingleton::_instance = nullptr;

//UDataSingleton::UDataSingleton(const FObjectInitializer& ObjectInitializer)
//{
//};

UDataSingleton* UDataSingleton::Instance() 
{
 	if (_instance == nullptr)
	{
		_instance = NewObject<UDataSingleton>(GetTransientPackage(), FName("DataSingleton"));
		_instance->AddToRoot();
	}

	return _instance;
}

// Call to get asset registry, will force a synchrounous scan if
// one has not been done already.
IAssetRegistry* UDataSingleton::GetAssetRegistry()
{
	auto& asset_registry = Instance()->_assetRegistry;

	if (asset_registry == nullptr)
	{
		asset_registry = &FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
		TArray<FString> PathsToScan;
		PathsToScan.Add(TEXT("/Game"));

		asset_registry->ScanPathsSynchronous(PathsToScan);
	}

	return asset_registry;
}
