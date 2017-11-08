// Fill out your copyright notice in the Description page of Project Settings.

#include "SStatusIndicator.h"
#include "SlateOptMacros.h"
#include "Rendering/DrawElements.h"

#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

//BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SStatusIndicator::Construct(const FArguments& InArgs)
{
	check(InArgs._Style);

	Style = InArgs._Style;

	SetPercent(InArgs._Percent);

	BackgroundImage = InArgs._BackgroundImage;
	FillImage = InArgs._FillImage;

	//FillColorAndOpacity = InArgs._FillColorAndOpacity;
	BorderPadding = InArgs._BorderPadding;

	CurrentTickRate = 0.0f;
	MinimumTickRate = InArgs._RefreshRate;

	ActiveTimerHandle = RegisterActiveTimer(CurrentTickRate, FWidgetActiveTimerDelegate::CreateSP(this, &SStatusIndicator::ActiveTick));
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

	Invalidate(EInvalidateWidget::Layout);
}

//void SStatusIndicator::SetFillColorAndOpacity(TAttribute< FSlateColor > InFillColorAndOpacity)
//{
//	//FillColorAndOpacity = InFillColorAndOpacity;
//	Invalidate(EInvalidateWidget::Layout);
//}

void SStatusIndicator::SetBorderPadding(TAttribute< FVector2D > InBorderPadding)
{
	BorderPadding = InBorderPadding;
	Invalidate(EInvalidateWidget::Layout);
}

void SStatusIndicator::SetBackgroundImage(const FSlateBrush* InBackgroundImage)
{
	BackgroundImage = InBackgroundImage;
	Invalidate(EInvalidateWidget::Layout);
}

void SStatusIndicator::SetFillImage(const FSlateBrush* InFillImage)
{
	FillImage = InFillImage;
	Invalidate(EInvalidateWidget::Layout);
}

const FSlateBrush* SStatusIndicator::GetBackgroundImage() const
{
	return BackgroundImage ? BackgroundImage : &Style->BackgroundImage;
}

const FSlateBrush* SStatusIndicator::GetFillImage() const
{
	return FillImage ? FillImage : &Style->FillImage;
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

int32 SStatusIndicator::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	// Used to track the layer ID we will return.
	int32 RetLayerId = LayerId;

	bool bEnabled = ShouldBeEnabled(bParentEnabled);
	const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	//const FLinearColor FillColor(InWidgetStyle.GetColorAndOpacityTint() * FillColorAndOpacity.Get().GetColor(InWidgetStyle) * CurrentFillImage->GetTint(InWidgetStyle));
	//const FLinearColor FillColor(FillColorAndOpacity.Get().GetColor(InWidgetStyle));
	
	const FLinearColor BorderColor(GetBackgroundImage()->GetTint(InWidgetStyle));
	const FLinearColor FillColor(GetFillImage()->GetTint(InWidgetStyle));
	
	TOptional<float> ProgressFraction = Percent.Get();
	FVector2D BorderPaddingRef = BorderPadding.Get();

	FSlateDrawElement::MakeBox(
		OutDrawElements,
		RetLayerId++,
		AllottedGeometry.ToPaintGeometry(),
		GetBackgroundImage(),
		DrawEffects,
		BorderColor
	);

	if (ProgressFraction.IsSet())
	{
		auto FillMaterial = static_cast<UMaterialInstanceDynamic*>(GetFillImage()->GetResourceObject());

		if (FillMaterial)
		{
			FillMaterial->SetScalarParameterValue(FName("Percent"), ProgressFraction.GetValue());
		}
	}

	FSlateDrawElement::MakeBox(
		OutDrawElements,
		RetLayerId++,
		AllottedGeometry.ToPaintGeometry(
			FVector2D::ZeroVector,
			FVector2D(AllottedGeometry.GetLocalSize().X, AllottedGeometry.GetLocalSize().Y)),
		GetFillImage(),
		DrawEffects,
		FillColor
	);

	return RetLayerId - 1;
}

FVector2D SStatusIndicator::ComputeDesiredSize(float) const
{
	return GetBackgroundImage()->ImageSize;
}

bool SStatusIndicator::ComputeVolatility() const
{
	return SLeafWidget::ComputeVolatility() || Percent.IsBound();
}

void SStatusIndicator::SetActiveTimerTickRate(float TickRate)
{
	if (CurrentTickRate != TickRate || !ActiveTimerHandle.IsValid())
	{
		CurrentTickRate = TickRate;

		TSharedPtr<FActiveTimerHandle> SharedActiveTimerHandle = ActiveTimerHandle.Pin();
		if (SharedActiveTimerHandle.IsValid())
		{
			UnRegisterActiveTimer(SharedActiveTimerHandle.ToSharedRef());
		}

		ActiveTimerHandle = RegisterActiveTimer(TickRate, FWidgetActiveTimerDelegate::CreateSP(this, &SStatusIndicator::ActiveTick));
	}
}

EActiveTimerReturnType SStatusIndicator::ActiveTick(double InCurrentTime, float InDeltaTime)
{
	MarqueeOffset = InCurrentTime - FMath::FloorToDouble(InCurrentTime);

	TOptional<float> PrecentFracton = Percent.Get();
	if (PrecentFracton.IsSet())
	{
		SetActiveTimerTickRate(MinimumTickRate);
	}
	else
	{
		SetActiveTimerTickRate(0.0f);
	}

	return EActiveTimerReturnType::Continue;
}


//END_SLATE_FUNCTION_BUILD_OPTIMIZATION
