// Fill out your copyright notice in the Description page of Project Settings.

#include "StatusIndicatorWidgetStyle.h"


FStatusIndicatorStyle::FStatusIndicatorStyle()
{
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
}

