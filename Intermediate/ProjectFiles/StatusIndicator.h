#pragma once

//~~~~~~~~~~~~ UMG ~~~~~~~~~~~~~~~~
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Custom Slate Element
#include "SStatusIndicator.h"

#include "StatusIndicator.generated.h"

UCLASS()
class UStatusIndicator : public UWidget
{
	GENERATED_UCLASS_BODY()

		//Custom Slate Element 
protected:
	TSharedPtr<SStatusIndicator> MyImage;

	//~~~~~~~~~~
	//Thickness
	// 	Rama's custom UMG Widget property!
	//~~~~~~~~~~
public:
	/** Thickness */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Soft Edge Image")
		float Thickness;

	//Delegate verison if you want it!
	//		-Rama
	//UPROPERTY()
	//FGetFloat ThicknessDelegate;

	/** Update thickness of Soft Edge Image! Yay! */
	UFUNCTION(BlueprintCallable, Category = "Joy Soft Edge Image")
		void SetThickness(float InThickness);

	//~~~ Rest is copied from UMG Image.h ~~~
public:

	/** Image to draw */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
		FSlateBrush Brush;

	/** A bindable delegate for the Image. */
	UPROPERTY()
		FGetSlateBrush BrushDelegate;

	/** Color and opacity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
		FLinearColor ColorAndOpacity;

	/** A bindable delegate for the ColorAndOpacity. */
	UPROPERTY()
		FGetLinearColor ColorAndOpacityDelegate;

public:

	UPROPERTY(EditDefaultsOnly, Category = Events)
		FOnPointerEvent OnMouseButtonDownEvent;

public:

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetColorAndOpacity(FLinearColor InColorAndOpacity);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetOpacity(float InOpacity);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromAsset(USlateBrushAsset* Asset);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromTexture(UTexture2D* Texture);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromMaterial(UMaterialInterface* Material);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		UMaterialInstanceDynamic* GetDynamicMaterial();

	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	// UWidget interface
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;

	FReply HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent);
};