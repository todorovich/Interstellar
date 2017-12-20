// Copyright 2017 Micho Todorovich, all rights reserved.

#include "SStatusIndicator.h"
#include "SlateOptMacros.h"
#include "Rendering/DrawElements.h"
#include "Interstellar.h"

#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SStatusIndicator::~SStatusIndicator()
{
	if (auto dsm = DynamicSwipeMaterial.GetResourceObject())
	{
		dsm->RemoveFromRoot();
	}
}

void SStatusIndicator::Construct(const FArguments& InArgs)
{
	SetStyle(InArgs._Style);

	SetPercent(InArgs._Percent);
}

void SStatusIndicator::SetPercent(TAttribute<float> InPercent)
{
	if (!Percent.IdenticalTo(InPercent))
	{
		Percent = InPercent;

		Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

void SStatusIndicator::SetRotation(TAttribute<float> InRotation)
{
	if (!Rotation.IdenticalTo(InRotation))
	{
		Rotation = InRotation;

		Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

void SStatusIndicator::SetStyle(const FStatusIndicatorStyle* InStyle)
{
	Style.Set(InStyle);

	if (Style.Get() == nullptr)
	{
		FArguments Defaults;
		Style = Defaults._Style;
	}

	check(Style.Get());

	UE_LOG(IntrepidLog, Log, TEXT("Creating Dynamic Material"));

	DynamicSwipeMaterial.SetResourceObject(UMaterialInstanceDynamic::Create(static_cast<UMaterialInterface*>(Style.Get()->SwipeMaterial.GetResourceObject()), nullptr));

	DynamicSwipeMaterial.GetResourceObject()->AddToRoot();

	Invalidate(EInvalidateWidget::Layout);
}

//void PushTransformedClip(FSlateWindowElementList& OutDrawElements, const FGeometry& AllottedGeometry, FVector2D InsetPadding, FVector2D ProgressOrigin, FSlateRect Progress)
//{
//	const FSlateRenderTransform& Transform = AllottedGeometry.GetAccumulatedRenderTransform();
//
//	const FVector2D MaxSize = AllottedGeometry.GetLocalSize() - (InsetPadding * 2.0f);
//
//	OutDrawElements.PushClip(FSlateClippingZone(
//		Transform.TransformPoint(InsetPadding + (ProgressOrigin - FVector2D(Progress.Left, Progress.Top)) * MaxSize),
//		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X + Progress.Right, ProgressOrigin.Y - Progress.Top) * MaxSize),
//		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X - Progress.Left, ProgressOrigin.Y + Progress.Bottom) * MaxSize),
//		Transform.TransformPoint(InsetPadding + (ProgressOrigin + FVector2D(Progress.Right, Progress.Bottom)) * MaxSize)
//	));
//}

// Return Value is the largest LayerId used.
int32 SStatusIndicator::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Used to track the layer ID we will return.
	int32 RetLayerId = LayerId;

	bool bEnabled = ShouldBeEnabled(bParentEnabled);

	if (bEnabled)
	{
		const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		const FLinearColor BorderColor(Style.Get()->BorderImage.GetTint(InWidgetStyle));
		const FLinearColor FillColor(Style.Get()->FillImage.GetTint(InWidgetStyle));

		//UE_LOG(DebugLog, Log, TEXT("%s"), *FillColor.ToString());

		if (DynamicSwipeMaterial.GetResourceObject())
		{
			auto mat = static_cast<UMaterialInstanceDynamic*>(DynamicSwipeMaterial.GetResourceObject());
			
			mat->SetTextureParameterValue(FName("Texture"), Cast<UTexture>(Style.Get()->FillImage.GetResourceObject()));
			mat->SetScalarParameterValue(FName("Percent"), Percent.Get());
			mat->SetScalarParameterValue(FName("Rotation"), Rotation.Get());
			
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				RetLayerId++,
				AllottedGeometry.ToPaintGeometry(
					FVector2D::ZeroVector,
					AllottedGeometry.GetLocalSize()),
				&DynamicSwipeMaterial,				   
				DrawEffects,						   
				FillColor
			);

			FSlateDrawElement::MakeBox(
				OutDrawElements,
				RetLayerId++,
				AllottedGeometry.ToPaintGeometry(
					FVector2D::ZeroVector,
					AllottedGeometry.GetLocalSize()),
				&DynamicSwipeMaterial,
				DrawEffects,
				FillColor
			);
		}// Maybe add an else to try to create the dynamic material

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			RetLayerId++,
			AllottedGeometry.ToPaintGeometry(
				FVector2D::ZeroVector,
				AllottedGeometry.GetLocalSize()),
			&Style.Get()->BorderImage,
			DrawEffects,
			BorderColor
		);
	}

	return RetLayerId - 1;
}

FVector2D SStatusIndicator::ComputeDesiredSize(float) const
{
	return FVector2D(64.0, 64.0);
}

bool SStatusIndicator::ComputeVolatility() const
{
	return SLeafWidget::ComputeVolatility() || Percent.IsBound();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
