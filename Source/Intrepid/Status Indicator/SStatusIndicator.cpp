// Fill out your copyright notice in the Description page of Project Settings.

#include "SStatusIndicator.h"
#include "SlateOptMacros.h"
#include "Rendering/DrawElements.h"

#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

//BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SStatusIndicator::Construct(const FArguments& InArgs)
{
	SetStyle(InArgs._Style);

	SetPercent(InArgs._Percent);
}

void SStatusIndicator::SetPercent(TAttribute< TOptional<float> > InPercent)
{
	if (!Percent.IdenticalTo(InPercent))
	{
		Percent = InPercent;

		

		Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

void SStatusIndicator::SetStyle(const FStatusIndicatorStyle* InStyle)
{

	Style = InStyle;

	if (Style == nullptr)
	{
		FArguments Defaults;
		Style = Defaults._Style;
	}

	check(Style);

	DynamicSwipeMaterial.SetResourceObject(UMaterialInstanceDynamic::Create(static_cast<UMaterialInterface*>(Style->SwipeMaterial.GetResourceObject()), nullptr, FName("DynamicFillMaterial")));

	Invalidate(EInvalidateWidget::Layout);
}


void PushTransformedClip(FSlateWindowElementList& OutDrawElements, const FGeometry& AllottedGeometry, FVector2D InsetPadding, FVector2D ProgressOrigin, FSlateRect Progress)
{
	const FSlateRenderTransform& Transform = AllottedGeometry.GetAccumulatedRenderTransform();

	const FVector2D MaxSize = AllottedGeometry.GetLocalSize() - (InsetPadding * 2.0f);

	OutDrawElements.PushClip(FSlateClippingZone(
		Transform.TransformPoint(InsetPadding + (ProgressOrigin - FVector2D(Progress.Left, Progress.Top)) * MaxSize),
		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X + Progress.Right, ProgressOrigin.Y - Progress.Top) * MaxSize),
		Transform.TransformPoint(InsetPadding + FVector2D(ProgressOrigin.X - Progress.Left, ProgressOrigin.Y + Progress.Bottom) * MaxSize),
		Transform.TransformPoint(InsetPadding + (ProgressOrigin + FVector2D(Progress.Right, Progress.Bottom)) * MaxSize)
	));
}

// Return Value is the largest LayerId used.
int32 SStatusIndicator::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Used to track the layer ID we will return.
	int32 RetLayerId = LayerId;

	bool bEnabled = ShouldBeEnabled(bParentEnabled);

	if (bEnabled)
	{
		const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		const FLinearColor BorderColor(Style->BorderImage.GetTint(InWidgetStyle));
		const FLinearColor FillColor(Style->FillImage.GetTint(InWidgetStyle));


		if (DynamicSwipeMaterial.GetResourceObject())
		{
			static_cast<UMaterialInstanceDynamic*>(DynamicSwipeMaterial.GetResourceObject())->SetScalarParameterValue(FName("Percent"), Percent.Get().GetValue());
			
			FSlateDrawElement::MakeBox(
				OutDrawElements,
				RetLayerId++,
				AllottedGeometry.ToPaintGeometry(),
				&DynamicSwipeMaterial,
				DrawEffects,
				BorderColor
			);
		}

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			RetLayerId++,
			AllottedGeometry.ToPaintGeometry(
				FVector2D::ZeroVector,
				FVector2D(AllottedGeometry.GetLocalSize().X, AllottedGeometry.GetLocalSize().Y)),
			&Style->BorderImage,
			DrawEffects,
			FillColor
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

//END_SLATE_FUNCTION_BUILD_OPTIMIZATION
