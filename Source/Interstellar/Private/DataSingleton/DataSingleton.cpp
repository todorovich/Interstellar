// Copyright 2017 Micho Todorovich, all rights reserved.

#include "DataSingleton.h"
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "Runtime/AssetRegistry/Public/IAssetRegistry.h"

UDataSingleton* UDataSingleton::_instance = nullptr;

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
		if (!asset_registry->IsLoadingAssets())
		{
			asset_registry->ScanPathsSynchronous(PathsToScan);
		}
	}

	return asset_registry;
}

//FARFilter filter;
//TArray<FAssetData> assetArray;
//auto assetRegistry = UDataSingleton::GetAssetRegistry();

//// Set up filter to find materials
//filter.PackagePaths.Add("/Game/Materials");
//filter.ClassNames.Add(UMaterial::StaticClass()->GetFName());
//filter.bRecursiveClasses = true;

//assetRegistry->GetAssets(filter, assetArray);

//// Iterate over the materials until the one we want is found.
//for (auto& assetData : assetArray)
//{
//	if (assetData.AssetName == FName("M_Star"))
//	{
//		//UE_LOG(InterstellarLog, Log, TEXT("Found M_Star"));
//		auto  asset = assetData.GetAsset();
//		StarBillboard->StarSpriteParameters.Material = Cast<UMaterialInterface>(asset);
//	}
//}