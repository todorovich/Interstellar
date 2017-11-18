// Copyright 2017 Micho Todorovich, all rights reserved.

#include "Status Indicator/StatusIndicator.h"
#include "Slate/SlateBrushAsset.h"
#include "Intrepid.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstance.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "DataSingleton.h"

#define LOCTEXT_NAMESPACE "StatusIndicator"

UStatusIndicator::UStatusIndicator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// TODO: Switch this to use asset registry
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/M_CircleSwipe.M_CircleSwipe'"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> BorderTexture(TEXT("Texture2D'/Game/Textures/shield_status_icon.shield_status_icon'"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> FillTexture(TEXT("Texture2D'/Game/Textures/shield_status_icon_fill.shield_status_icon_fill'"));

	SStatusIndicator::FArguments SlateDefaults;
	
	SlateDefaults._Percent;
	Style = *SlateDefaults._Style;	
	Percent = SlateDefaults._Percent.Get();

	if (BorderTexture.Object)
	{
		Style.BorderImage.SetResourceObject(BorderTexture.Object);
		Style.BorderImage.ImageSize = FVector2D(BorderTexture.Object->GetSizeX(), BorderTexture.Object->GetSizeX());
		Style.BorderImage.TintColor = FLinearColor::White;
	}

	if (FillTexture.Object)
	{
		Style.FillImage.SetResourceObject(FillTexture.Object);
		Style.FillImage.ImageSize = FVector2D(FillTexture.Object->GetSizeX(), FillTexture.Object->GetSizeX());
		Style.FillImage.TintColor = FLinearColor::White;
	}
	
	if (Material.Object)
	{
		Style.SwipeMaterial.SetResourceObject(Material.Object);

		// Setting this on a material makes it think you are not defaulted in the editor, wtf?
		//Style.SwipeMaterial.ImageSize.Set(64.0, 64.0);
		Style.SwipeMaterial.TintColor = FLinearColor::White;
	}

	Style.BorderPadding = FVector2D(0, 0);

	SynchronizeProperties();
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
