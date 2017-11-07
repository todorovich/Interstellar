// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "SStatusIndicatorWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct INTREPID_API FSStatusIndicatorStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSStatusIndicatorStyle();
	virtual ~FSStatusIndicatorStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSStatusIndicatorStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USStatusIndicatorWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSStatusIndicatorStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
