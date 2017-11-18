// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "StatusIndicatorWidgetStyle.generated.h"

class UMaterialInstanceDynamic;

/**
 * 
 */
USTRUCT(BlueprintType)
struct INTREPID_API FStatusIndicatorStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FStatusIndicatorStyle();
	virtual ~FStatusIndicatorStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FStatusIndicatorStyle& GetDefault();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush SwipeMaterial;
	FStatusIndicatorStyle& SetSwipeMaterial(const FSlateBrush& InSwipeMaterial) { SwipeMaterial = InSwipeMaterial; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush BorderImage;
	FStatusIndicatorStyle& SetBorderImage(const FSlateBrush& InBorderImage) { BorderImage = InBorderImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush FillImage;
	FStatusIndicatorStyle& SetFillImage(const FSlateBrush& InFillImage) { FillImage = InFillImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Progress)
	FVector2D BorderPadding;
	FStatusIndicatorStyle& SetBorderPadding(const FVector2D& InBorderPadding) { BorderPadding = InBorderPadding; return *this; }
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UStatusIndicatorWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FStatusIndicatorStyle Style;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &Style );
	}
};
