// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Misc/Attribute.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateWidgetStyleAsset.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SLeafWidget.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "StatusIndicatorWidgetStyle.h"

class FActiveTimerHandle;
class FPaintArgs;
class FSlateWindowElementList;

/**
 * 
 */
class INTREPID_API SStatusIndicator : public SLeafWidget
{

public:
	SLATE_BEGIN_ARGS(SStatusIndicator)
		: _Style(&FCoreStyle::Get().GetWidgetStyle<FStatusIndicatorStyle>("StatusIndicator"))
		, _Percent(TOptional<float>())
	{}

		/** Style used for the progress bar */
		SLATE_STYLE_ARGUMENT(FStatusIndicatorStyle, Style)

		/** Used to determine the fill position of the progress bar ranging 0..1 */
		SLATE_ATTRIBUTE(TOptional<float>, Percent)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual bool ComputeVolatility() const override;

	/** See attribute Percent */
	void SetPercent(TAttribute< TOptional<float> > InPercent);

	/** See attribute Style */
	void SetStyle(const FStatusIndicatorStyle* InStyle);

private:

	/** The style of the indicator */
	const FStatusIndicatorStyle* Style;

	/** How full the indicator is */
	TAttribute< TOptional<float> > Percent;

	FSlateBrush DynamicSwipeMaterial;
};