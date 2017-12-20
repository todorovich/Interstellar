// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "StatusIndicatorWidgetStyle.generated.h"

class UMaterialInstanceDynamic;



/**
 *	The Slate Widget Style for the Status Indicator
 */
USTRUCT(BlueprintType)
struct INTERSTELLAR_API FStatusIndicatorStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FStatusIndicatorStyle() = default;
	virtual ~FStatusIndicatorStyle() = default;

	static const FStatusIndicatorStyle& GetDefault();
	
	static const FName TypeName;
	
	virtual const FName GetTypeName() const override { return TypeName; };
	
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	
	// The Material used to selectively modify the opacity Fill Image.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush SwipeMaterial;
	FStatusIndicatorStyle& SetSwipeMaterial(const FSlateBrush& InSwipeMaterial) { SwipeMaterial = InSwipeMaterial; return *this; }

	// The texture used as a container for the fill image.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush BorderImage;
	FStatusIndicatorStyle& SetBorderImage(const FSlateBrush& InBorderImage) { BorderImage = InBorderImage; return *this; }

	// The texture used to fill the border.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush FillImage;
	FStatusIndicatorStyle& SetFillImage(const FSlateBrush& InFillImage) { FillImage = InFillImage; return *this; }

	// The amount of padding that should be used.
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
