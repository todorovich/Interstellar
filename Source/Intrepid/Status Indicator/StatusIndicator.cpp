// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Status Indicator/StatusIndicator.h"
#include "Slate/SlateBrushAsset.h"

#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"


#define LOCTEXT_NAMESPACE "StatusIndicator"

UStatusIndicator::UStatusIndicator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SStatusIndicator::FArguments SlateDefaults;
	
	WidgetStyle = *SlateDefaults._Style;	
	WidgetStyle.FillImage.TintColor = FLinearColor::White;

	Percent = 0;
	FillColorAndOpacity = FLinearColor::White;
	BorderPadding = FVector2D(0, 0);
}

UMaterialInstanceDynamic* UStatusIndicator::GetDynamicMaterial()
{
	UMaterialInterface* Material = NULL;

	UObject* Resource = WidgetStyle.FillImage.GetResourceObject();
	Material = Cast<UMaterialInterface>(Resource);

	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

		if (!DynamicMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
			WidgetStyle.FillImage.SetResourceObject(DynamicMaterial);

			if (MyStatusIndicator.IsValid())
			{
				MyStatusIndicator->SetFillImage(&WidgetStyle.FillImage);
			}
		}

		return DynamicMaterial;
	}

	return NULL;
}

void UStatusIndicator::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyStatusIndicator.Reset();
}

TSharedRef<SWidget> UStatusIndicator::RebuildWidget()
{
	MyStatusIndicator = SNew(SStatusIndicator);

	return MyStatusIndicator.ToSharedRef();
}

void UStatusIndicator::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute< TOptional<float> > PercentBinding = OPTIONAL_BINDING_CONVERT(float, Percent, TOptional<float>, ConvertFloatToOptionalFloat);
	TAttribute<FSlateColor> FillColorAndOpacityBinding = PROPERTY_BINDING(FSlateColor, FillColorAndOpacity);

	MyStatusIndicator->SetStyle(&WidgetStyle);
	GetDynamicMaterial();

	MyStatusIndicator->SetFillColorAndOpacity(FillColorAndOpacityBinding);
	MyStatusIndicator->SetBorderPadding(BorderPadding);

	MyStatusIndicator->SetPercent(Percent);
}


void UStatusIndicator::SetFillColorAndOpacity(FLinearColor Color)
{
	FillColorAndOpacity = Color;
	if (MyStatusIndicator.IsValid())
	{
		MyStatusIndicator->SetFillColorAndOpacity(FillColorAndOpacity);
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

void UStatusIndicator::OnCreationFromPalette()
{
	FillColorAndOpacity = FLinearColor(0, 0.5f, 1.0f);
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
