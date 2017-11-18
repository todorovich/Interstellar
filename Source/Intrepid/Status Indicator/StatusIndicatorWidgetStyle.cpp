// Copyright 2017 Micho Todorovich, all rights reserved.

#include "StatusIndicatorWidgetStyle.h"
#include "Status Indicator/StatusIndicator.h"
//#include "Slate/SlateBrushAsset.h"
//#include "Intrepid.h"
//#include "Materials/MaterialInstanceDynamic.h"
//#include "Materials/MaterialInstance.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
//#include "Runtime/Engine/Classes/Engine/Texture2D.h"
//#include "AssetRegistryModule.h"
//#include "ARFilter.h"
//#include "DataSingleton.h"


const FName FStatusIndicatorStyle::TypeName(TEXT("FStatusIndicatorStyle"));

const FStatusIndicatorStyle& FStatusIndicatorStyle::GetDefault()
{
	static FStatusIndicatorStyle Default;

	return Default;
}

void FStatusIndicatorStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	OutBrushes.Add(&SwipeMaterial);
	OutBrushes.Add(&BorderImage);
	OutBrushes.Add(&FillImage);
}

