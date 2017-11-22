// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWidget.h"
#include "Components/Widget.h"
#include "Status Indicator/SStatusIndicator.h"
#include "Status Indicator/StatusIndicatorWidgetStyle.h"
#include "StatusIndicator.generated.h"

class USlateBrushAsset;

UENUM(BlueprintType)
enum class FillStyle : uint8
{
	LeftToRight UMETA(DisplayName = "Left to Right"),
	RightToLeft UMETA(DisplayName = "Right to Left"),
	BottomToTop UMETA(DisplayName = "Bottom to Top"),
	TopToBottom UMETA(DisplayName = "Top to Bottom"),
	RadialCW	UMETA(DisplayName = "Radial Clockwise"),
	RadialCCW	UMETA(DisplayName = "Radial Counter-Clockwise"),
	Custom		UMETA(DisplayName = "Custom"),
};


/**
*  The Status Indicator UMG Widget
*/
UCLASS(BlueprintType)
class INTREPID_API UStatusIndicator : public UWidget
{
	GENERATED_UCLASS_BODY()

	FillStyle currentFillStyle = FillStyle::RadialCCW;

	inline void UseRadialCCWFillType();

	inline void UseRadialCWFillType();

	inline void UseRightToLeftFillType();

	inline void UseLeftToRightFillType();
	
	inline void UseBottomToTopFillType();
	
	inline void UseTopToBottomFillType();
	
	inline void FindAndSetDefaultAssets();

	inline void FindAndSetDefaultTextures();

protected:
	// Native Slate Widget
	TSharedPtr<SStatusIndicator> MyStatusIndicator;

	// Overridden from UWidget
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:

	// Says it's already defined or declared somwhere else? Thinking it's included in the generated uclass body.
	//UStatusIndicator(const FObjectInitializer& ObjectInitializer);

	virtual ~UStatusIndicator() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Fill Style"))
	FillStyle fillStyleSelected = FillStyle::RadialCCW;

	// The style of the Status Indicator
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style"))
	FStatusIndicatorStyle Style;
	 
	// The fill amount of the progress bar as a float with a range of 0..1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Progress, meta = (UIMin = "0", UIMax = "1"))
	float Percent;

	// Sets the current value of the Status Indicator.
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void SetPercent(float InPercent);

	// Overridden from UWidget
	virtual void SynchronizeProperties() override;

	// Overridden from UVisual
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	// Overridden form UObject
	virtual void PostLoad() override;

#if WITH_EDITOR
	// Overridden from UWidget
	virtual const FText GetPaletteCategory() override;
	
	// Overridden from UWidget
	virtual void OnCreationFromPalette() override;
#endif
};
