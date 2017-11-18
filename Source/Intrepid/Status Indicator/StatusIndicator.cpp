// Copyright 2017 Micho Todorovich, all rights reserved.

#include "Status Indicator/StatusIndicator.h"
#include "Intrepid.h"
#include "Slate/SlateBrushAsset.h"
#include "Materials/MaterialInstance.h"
//#include "Materials/MaterialInstanceDynamic.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "DataSingleton.h"

#define LOCTEXT_NAMESPACE "StatusIndicator"

UStatusIndicator::UStatusIndicator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SStatusIndicator::FArguments SlateDefaults;
	Style = *SlateDefaults._Style;	
	Percent = SlateDefaults._Percent.Get();

	FARFilter filter;
	TArray<FAssetData> assetArray;
	auto assetRegistry = UDataSingleton::GetAssetRegistry();

	// Set up filter to find materials
	filter.PackagePaths.Add("/Game/Materials");
	filter.ClassNames.Add(UMaterial::StaticClass()->GetFName());
	filter.bRecursiveClasses = true;

	assetRegistry->GetAssets(filter, assetArray);

	//UE_LOG(DebugLog, Log, TEXT("Results found: %d"), assetArray.Num());

	// Iterate over the materials until the one we want is found.
	for (auto& assetData : assetArray)
	{
		//UE_LOG(DebugLog,
		//	Log,
		//	TEXT("AssetName: %s\n\tAssetClass: %s\n\tObjectPath: %s\n\tPackagePath: %s\n\tPackageName: %s\n\tNumber of TagsAndValues: %d"),
		//	*assetData.AssetName.ToString(),
		//	*assetData.AssetClass.ToString(),
		//	*assetData.ObjectPath.ToString(),
		//	*assetData.PackagePath.ToString(),
		//	*assetData.PackageName.ToString(),
		//	assetData.TagsAndValues.Num());
		if (assetData.AssetName == FName("M_ClockwiseRadialFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_ClockwiseRadialFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	filter.Clear();

	// Set up filter to find textures 
	filter.PackagePaths.Add("/Game/Textures");
	filter.ClassNames.Add(UTexture2D::StaticClass()->GetFName());
	filter.bRecursiveClasses = true;

	assetRegistry->GetAssets(filter, assetArray);

	//UE_LOG(DebugLog, Log, TEXT("Results found: %d"), assetArray.Num());

	// Iterate over the texutres and find the ones we are looking for
	for (auto& assetData : assetArray)
	{
		if (assetData.AssetName == FName("T_Shield_Status_Icon"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found shield_status_icon"));
			auto object = assetData.GetAsset();
			auto texture = Cast<UTexture2D>(object);
			Style.BorderImage.SetResourceObject(object);
			Style.BorderImage.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeX());
			Style.BorderImage.TintColor = FLinearColor::White;
		}
		else if (assetData.AssetName == FName("T_Shield_Status_Icon_Fill"))
		{
			auto object = assetData.GetAsset();
			auto texture = Cast<UTexture2D>(object);
			Style.FillImage.SetResourceObject(object);
			Style.FillImage.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeX());
			Style.FillImage.TintColor = FLinearColor::White;
		}
	}

	Style.BorderPadding = FVector2D(0, 0);

	//SynchronizeProperties();
}

//UStatusIndicator::~UStatusIndicator(){}

void UStatusIndicator::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyStatusIndicator.Reset();
}

TSharedRef<SWidget> UStatusIndicator::RebuildWidget()
{
	MyStatusIndicator = SNew(SStatusIndicator);
	
	SynchronizeProperties();

	return MyStatusIndicator.ToSharedRef();
}

void UStatusIndicator::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	if (MyStatusIndicator.IsValid())
	{
		MyStatusIndicator->SetStyle(&Style);
		MyStatusIndicator->SetPercent(Percent);
	}
}

void UStatusIndicator::SetPercent(float InPercent)
{
	Percent = InPercent;
	if (MyStatusIndicator.IsValid())
	{
		MyStatusIndicator->SetPercent(InPercent);
	}
}

void UStatusIndicator::PostLoad()
{
	Super::PostLoad();
}

#if WITH_EDITOR

const FText UStatusIndicator::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

void UStatusIndicator::OnCreationFromPalette() {}

#endif

#undef LOCTEXT_NAMESPACE
