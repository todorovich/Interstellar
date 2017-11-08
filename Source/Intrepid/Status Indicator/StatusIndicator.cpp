// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Status Indicator/StatusIndicator.h"
#include "Slate/SlateBrushAsset.h"

#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

#define LOCTEXT_NAMESPACE "StatusIndicator"


UStatusIndicator::UStatusIndicator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/M_CircleSwipe.M_CircleSwipe'"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture(TEXT("Texture2D'/Game/Textures/shield_status_icon.shield_status_icon'"));

	SStatusIndicator::FArguments SlateDefaults;
	
	Style = *SlateDefaults._Style;	

	Style.BackgroundImage.TintColor = FLinearColor::White;
	Style.FillImage.TintColor = FLinearColor::Green;

	if (Texture.Object)
	{
		Style.BackgroundImage.SetResourceObject(Texture.Object);
	}

	if (Material.Object)
	{
		Style.FillImage.SetResourceObject(Material.Object);
	}

	Percent = .99;
	/*FillColorAndOpacity = FLinearColor::White;*/
	BorderPadding = FVector2D(0, 0);
}

UMaterialInstanceDynamic* UStatusIndicator::GetDynamicMaterial()
{
	UMaterialInterface* Material = NULL;

	UObject* Resource = Style.FillImage.GetResourceObject();
	Material = Cast<UMaterialInterface>(Resource);

	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

		if (!DynamicMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
			Style.FillImage.SetResourceObject(DynamicMaterial);

			if (MyStatusIndicator.IsValid())
			{
				MyStatusIndicator->SetFillImage(&Style.FillImage);
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
	//TAttribute<FSlateColor> FillColorAndOpacityBinding = PROPERTY_BINDING(FSlateColor, FillColorAndOpacity);

	MyStatusIndicator->SetStyle(&Style);
	GetDynamicMaterial();

	//MyStatusIndicator->SetFillColorAndOpacity(FillColorAndOpacityBinding);
	MyStatusIndicator->SetBorderPadding(BorderPadding);

	MyStatusIndicator->SetPercent(Percent);
}


//void ustatusindicator::setfillcolorandopacity(flinearcolor color)
//{
//	fillcolorandopacity = color;
//	if (mystatusindicator.isvalid())
//	{
//		mystatusindicator->setfillcolorandopacity(fillcolorandopacity);
//	}
//}

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
	/*FillColorAndOpacity = FLinearColor(0, 0.5f, 1.0f);*/
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
