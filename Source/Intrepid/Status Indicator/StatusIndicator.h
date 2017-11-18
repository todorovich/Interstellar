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

/**
*  The Status Indicator UMG Widget
*/
UCLASS()
class INTREPID_API UStatusIndicator : public UWidget
{
	GENERATED_UCLASS_BODY()

protected:
	// Native Slate Widget
	TSharedPtr<SStatusIndicator> MyStatusIndicator;

	// Overridden from UWidget
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:

	// Says it's already defined or declared somwhere else? Thinking it's included in the generated uclass body.
	// UStatusIndicator(const FObjectInitializer& ObjectInitializer);

	virtual ~UStatusIndicator() = default;

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
