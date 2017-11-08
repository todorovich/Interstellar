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
		/*, _FillColorAndOpacity(FLinearColor::White)*/
		, _BorderPadding(FVector2D(1, 0))
		, _BackgroundImage(nullptr)
		, _FillImage(nullptr)
		, _RefreshRate(2.0f)
	{}

		/** Style used for the progress bar */
		SLATE_STYLE_ARGUMENT(FStatusIndicatorStyle, Style)

		/** Used to determine the fill position of the progress bar ranging 0..1 */
		SLATE_ATTRIBUTE(TOptional<float>, Percent)
	
		///** Fill Color and Opacity */
		//SLATE_ATTRIBUTE(FSlateColor, FillColorAndOpacity)

		/** Border Padding around fill bar */
		SLATE_ATTRIBUTE(FVector2D, BorderPadding)

		/** The brush to use as the background of the progress bar */
		SLATE_ARGUMENT(const FSlateBrush*, BackgroundImage)
	
		/** The brush to use as the fill image */
		SLATE_ARGUMENT(const FSlateBrush*, FillImage)
		
		/** Rate at which this widget is ticked when sleeping in seconds */			
		SLATE_ARGUMENT(float, RefreshRate)

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

	///** See attribute SetFillColorAndOpacity */
	//void SetFillColorAndOpacity(TAttribute< FSlateColor > InFillColorAndOpacity);

	/** See attribute BorderPadding */
	void SetBorderPadding(TAttribute< FVector2D > InBorderPadding);

	/** See attribute BackgroundImage */
	void SetBackgroundImage(const FSlateBrush* InBackgroundImage);

	/** See attribute FillImage */
	void SetFillImage(const FSlateBrush* InFillImage);

private:

	/** Controls the speed at which the widget is ticked when in slate sleep mode */
	void SetActiveTimerTickRate(float TickRate);

	/** Widgets active tick */
	EActiveTimerReturnType ActiveTick(double InCurrentTime, float InDeltaTime);

	/** Gets the current background image. */
	const FSlateBrush* GetBackgroundImage() const;
	/** Gets the current fill image */
	const FSlateBrush* GetFillImage() const;

private:

	/** The style of the progress bar */
	const FStatusIndicatorStyle* Style;

	/** The text displayed over the progress bar */
	TAttribute< TOptional<float> > Percent;

	/** Background image to use for the progress bar */
	const FSlateBrush* BackgroundImage;

	/** Foreground image to use for the progress bar */
	const FSlateBrush* FillImage;

	///** Fill Color and Opacity */
	//TAttribute<FSlateColor> FillColorAndOpacity;

	/** Border Padding */
	TAttribute<FVector2D> BorderPadding;

	/** Value to drive progress bar animation */
	float MarqueeOffset;

	/** Reference to the widgets current active timer */
	TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;

	/** Rate at which the widget is currently ticked when slate sleep mode is active */
	float CurrentTickRate;

	/** The slowest that this widget can tick when in slate sleep mode */
	float MinimumTickRate;

};
