// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusIndicatorWidgetStyle.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

FStatusIndicatorStyle::FStatusIndicatorStyle()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/M_CircleSwipe.M_CircleSwipe'"));
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture(TEXT("Texture2D'/Game/Textures/shield_status_icon.shield_status_icon'"));

	if (Texture.Object)
	{
		BackgroundImage.SetResourceObject(Texture.Object);
	}

	if (Material.Object)
	{
		FillImage.SetResourceObject(Material.Object);
	}
}

FStatusIndicatorStyle::~FStatusIndicatorStyle()
{
}

const FName FStatusIndicatorStyle::TypeName(TEXT("FStatusIndicatorStyle"));

const FStatusIndicatorStyle& FStatusIndicatorStyle::GetDefault()
{
	static FStatusIndicatorStyle Default;
	return Default;
}

void FStatusIndicatorStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	OutBrushes.Add(&BackgroundImage);
	OutBrushes.Add(&FillImage);
}

