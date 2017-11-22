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

	FindAndSetDefaultAssets();

	Style.BorderPadding = FVector2D(0, 0);

	//SynchronizeProperties();
}

void UStatusIndicator::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyStatusIndicator.Reset();
}

inline void UStatusIndicator::UseRadialCCWFillType()
{
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
		if (assetData.AssetName == FName("M_CounterClockwiseRadialFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_CounterClockwiseRadialFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::RadialCCW;
}

inline void UStatusIndicator::UseRadialCWFillType()
{
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
		if (assetData.AssetName == FName("M_ClockwiseRadialFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_CounterClockwiseRadialFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::RadialCW;
}

inline void UStatusIndicator::UseLeftToRightFillType()
{
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
		if (assetData.AssetName == FName("M_LeftToRightFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_LeftToRightFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::LeftToRight;
}

inline void UStatusIndicator::UseRightToLeftFillType()
{
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
		if (assetData.AssetName == FName("M_RightToLeftFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_RightToLeftFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::RightToLeft;
}

inline void UStatusIndicator::UseBottomToTopFillType()
{
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
		if (assetData.AssetName == FName("M_BottomToTopFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_BottomToTopFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::BottomToTop;
}

inline void UStatusIndicator::UseTopToBottomFillType()
{
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
		if (assetData.AssetName == FName("M_TopToBottomFill"))
		{
			UE_LOG(DebugLog, Log, TEXT("Found M_TopToBottomFill"));
			auto  asset = assetData.GetAsset();
			Style.SwipeMaterial.SetResourceObject(asset);
			Style.SwipeMaterial.TintColor = FLinearColor::White;
		}
	}

	currentFillStyle = FillStyle::TopToBottom;
}

inline void UStatusIndicator::FindAndSetDefaultTextures()
{
	FARFilter filter;
	TArray<FAssetData> assetArray;
	auto assetRegistry = UDataSingleton::GetAssetRegistry();

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
			UE_LOG(DebugLog, Log, TEXT("Found shield_status_icon_fill"));
			auto object = assetData.GetAsset();
			auto texture = Cast<UTexture2D>(object);
			Style.FillImage.SetResourceObject(object);
			Style.FillImage.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeX());
			Style.FillImage.TintColor = FLinearColor::White;
		}
	}
}

inline void UStatusIndicator::FindAndSetDefaultAssets()
{
	FindAndSetDefaultTextures();	

	UseRadialCCWFillType();
	//UseLeftToRightFillType();
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
	
	switch (fillStyleSelected)
	{
		case FillStyle::Custom:
			currentFillStyle = FillStyle::Custom;
			break;

		case FillStyle::RadialCW:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::RadialCW)
			{
				//UE_LOG(DebugLog, Log, TEXT("%s"), *Style.SwipeMaterial.GetResourceName().ToString());
				if (Style.SwipeMaterial.GetResourceName() != FName("M_ClockwiseRadialFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseRadialCWFillType();
			}
			break;

		case FillStyle::RadialCCW:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::RadialCCW)
			{
				//UE_LOG(DebugLog, Log, TEXT("%s"), *Style.SwipeMaterial.GetResourceName().ToString());
				if (Style.SwipeMaterial.GetResourceName() != FName("M_CounterClockwiseRadialFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseRadialCCWFillType();
			}
			break;

		case FillStyle::LeftToRight:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::LeftToRight)
			{
				if (Style.SwipeMaterial.GetResourceName() != FName("M_LeftToRightFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseLeftToRightFillType();
			}
			break;

		case FillStyle::RightToLeft:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::RightToLeft)
			{
				if (Style.SwipeMaterial.GetResourceName() != FName("M_RightToLeftFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseRightToLeftFillType();
			}
			break;

		case FillStyle::BottomToTop:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::BottomToTop)
			{
				if (Style.SwipeMaterial.GetResourceName() != FName("M_BottomToTopFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseBottomToTopFillType();
			}
			break;

		case FillStyle::TopToBottom:
			// Confirm we havent been switched from
			if (currentFillStyle == FillStyle::TopToBottom)
			{
				if (Style.SwipeMaterial.GetResourceName() != FName("M_TopToBottomFill"))
				{
					fillStyleSelected = FillStyle::Custom;
					currentFillStyle = FillStyle::Custom;
				}
			}
			// Switch to 
			else
			{
				UseTopToBottomFillType();
			}
			break;
	}
	

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
