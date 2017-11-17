// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

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
* The progress bar widget is a simple bar that fills up that can be restyled to fit any number of uses.
*
* * No Children
*/
UCLASS()
class INTREPID_API UStatusIndicator : public UWidget
{
	GENERATED_UCLASS_BODY()

protected:
	/** Native Slate Widget */
	TSharedPtr<SStatusIndicator> MyStatusIndicator;

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface

public:

	/** The progress bar style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style"))
	FStatusIndicatorStyle Style;

	/** Used to determine the fill position of the progress bar ranging 0..1 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Progress, meta = (UIMin = "0", UIMax = "1"))
	float Percent;

	/** A bindable delegate to allow logic to drive the text of the widget */
	UPROPERTY()
	FGetFloat PercentDelegate;

	/** Sets the current value of the ProgressBar. */
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void SetPercent(float InPercent);

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

#if WITH_EDITOR
	//~ Begin UWidget Interface
	virtual const FText GetPaletteCategory() override;
	virtual void OnCreationFromPalette() override;
	//~ End UWidget Interface
#endif




};
