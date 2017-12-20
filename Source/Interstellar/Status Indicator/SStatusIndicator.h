// Copyright 2017 Micho Todorovich, all rights reserved.

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
 *  The Status Indicator Slate Widget
 */
class INTERSTELLAR_API SStatusIndicator : public SLeafWidget
{

public:
	SLATE_BEGIN_ARGS(SStatusIndicator)
		: _Style(&FStatusIndicatorStyle::GetDefault())
		, _Percent(0.95f)
		, _Rotation(0.0f)
	{}

		// The Status Indicator's style
		SLATE_STYLE_ARGUMENT(FStatusIndicatorStyle, Style)

		// The fill amount of the Status Indicator respresented as a range of 0..1 
		SLATE_ATTRIBUTE(float, Percent)

		// The the rotation of the Status Indicator normalized to the range of 0..1 
		SLATE_ATTRIBUTE(float, Rotation)

	SLATE_END_ARGS()

	virtual ~SStatusIndicator();

	// Constructs this widget from FArguments
	void Construct(const FArguments& InArgs);

	// Called whenever the widget is supposed to redraw itself
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	// Returns this widgets desired size. 
	virtual FVector2D ComputeDesiredSize(float) const override;

	// Returns whether or not this widget is volatile
	virtual bool ComputeVolatility() const override;

	// Set Percent attribute 
	void SetPercent(TAttribute<float> InPercent);


	void SetRotation(TAttribute<float> InRotation);

	// Set Style attribute 
	void SetStyle(const FStatusIndicatorStyle* InStyle);

private:

	// The Status Indicator's style
	TAttribute<const FStatusIndicatorStyle*> Style;

	// The fill amount of the Status Indicator normalized to the range of 0..1 
	TAttribute<float> Percent;

	// The the rotation of the Status Indicator normalized to the range of 0..1 
	TAttribute<float> Rotation;

	// The Dynamic Material created in order to display this indicator
	FSlateBrush DynamicSwipeMaterial;
};