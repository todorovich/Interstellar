// Fill out your copyright notice in the Description page of Project Settings.

#include "SStatusIndicatorWidgetStyle.h"


FSStatusIndicatorStyle::FSStatusIndicatorStyle()
{
}

FSStatusIndicatorStyle::~FSStatusIndicatorStyle()
{
}

const FName FSStatusIndicatorStyle::TypeName(TEXT("FSStatusIndicatorStyle"));

const FSStatusIndicatorStyle& FSStatusIndicatorStyle::GetDefault()
{
	static FSStatusIndicatorStyle Default;
	return Default;
}

void FSStatusIndicatorStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

