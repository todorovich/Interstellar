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
	LeftToRight				UMETA(DisplayName = "Left to Right"),
	RightToLeft				UMETA(DisplayName = "Right to Left"),
	BottomToTop				UMETA(DisplayName = "Bottom to Top"),
	TopToBottom				UMETA(DisplayName = "Top to Bottom"),
	BottomLeftToTopRight	UMETA(DisplayName = "Bottom-Left to Top-Right"),
	BottomRightToTopLeft	UMETA(DisplayName = "Bottom-Right to Top-Left"),
	TopLeftToBottomRight	UMETA(DisplayName = "Top-Left to Bottom-Right"),
	TopRightToBottomLeft	UMETA(DisplayName = "Top-Right to Bottom-Left"),
	RadialCW				UMETA(DisplayName = "Radial Clockwise"),
	RadialCCW				UMETA(DisplayName = "Radial Counter-Clockwise"),
	Custom					UMETA(DisplayName = "Custom"),
};


/**
*  The Status Indicator UMG Widget
*/
UCLASS(BlueprintType)
class INTREPID_API UStatusIndicator : public UWidget
{
	GENERATED_BODY()

	FillStyle currentFillStyle = FillStyle::Custom;

	TMap<FillStyle, TFunction<void()>> FillStyleMap;

public:

	UStatusIndicator(const FObjectInitializer& ObjectInitializer);

	void RadialCCWSyncFunction();
	
	void RadialCWSyncFunction();
	
	void RightToLeftSyncFunction();
	
	void LeftToRightSyncFunction();
	
	void BottomToTopSyncFunction();
	
	void TopToBottomSyncFunction();

	void BottomLeftToTopRightSyncFunction();

	void BottomRightToTopLeftSyncFunction();

	void TopLeftToBottomRightSyncFunction();

	void TopRightToBottomLeftSyncFunction();

	void CustomFillSyncFunction();
	
	void FindAndSetDefaultAssets();
	
	void FindAndSetDefaultTextures();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Progress, meta = (UIMin = "0", UIMax = "1"))
	float Rotation;

	// The style of the Status Indicator
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style"))
	FStatusIndicatorStyle Style;
	 
	// The fill amount of the Status Indicator as a float with a range of 0..1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Progress, meta = (UIMin = "0", UIMax = "1"))
	float Percent;

	// Sets the current value of the Status Indicator.
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void SetPercent(float InPercent);

	// Sets the current value of the Status Indicator.
	UFUNCTION(BlueprintCallable, Category = "Style", meta= (DisplayName = "Rotation"))
	void SetRotation(float InRotation);

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
