
//Project Name
//#include "Abatron.h"
#include "StatusIndicator.h"

//LOCTEXT
#define LOCTEXT_NAMESPACE "UMG"

UStatusIndicator::UStatusIndicator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ColorAndOpacity(FLinearColor(0, 0, 1, 0.0333))
	, Thickness(24)
{
	//Default Values Set Here, see above
}

//Rebuild using custom Slate Widget 
//		-Rama
TSharedRef<SWidget> UStatusIndicator::RebuildWidget()
{
	MyImage = SNew(SSoftEdgeImage);
	return MyImage.ToSharedRef();
}

//Set Thickness
void UStatusIndicator::SetThickness(float InThickness)
{
	Thickness = InThickness;
	if (MyImage.IsValid())
	{
		MyImage->SetThickness(InThickness);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//This is where the SSoftEdgeImage slate widget gets updated 
//		when the UPROPERTY() is changed in the Editor
//		-Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UStatusIndicator::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	//Thickness Delegate Version
	//TAttribute<float> ThickBind = OPTIONAL_BINDING(float, Thickness);
	//MyImage->SetThickness(ThickBind.Get());   

	//Thickness non-delegate version
	MyImage->SetThickness(Thickness);

	//Color and Opacity
	TAttribute<FSlateColor> ColorAndOpacityBinding = OPTIONAL_BINDING(FSlateColor, ColorAndOpacity);
	MyImage->SetColorAndOpacity(ColorAndOpacityBinding);

	//Image
	TAttribute<const FSlateBrush*> ImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, Brush, const FSlateBrush*, ConvertImage);
	MyImage->SetImage(ImageBinding);

	//Mouse
	MyImage->SetOnMouseButtonDown(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonDown));
}


//~~~ Rest is copied from UMG Image.h ~~~

void UStatusIndicator::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyImage.Reset();
}

void UStatusIndicator::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacity = InColorAndOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

void UStatusIndicator::SetOpacity(float InOpacity)
{
	ColorAndOpacity.A = InOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

const FSlateBrush* UStatusIndicator::ConvertImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UJoySoftEdgeImage* MutableThis = const_cast<UJoySoftEdgeImage*>(this);
	MutableThis->Brush = InImageAsset.Get();

	return &Brush;
}

void UStatusIndicator::SetBrushFromAsset(USlateBrushAsset* Asset)
{
	Brush = Asset ? Asset->Brush : FSlateBrush();

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UStatusIndicator::SetBrushFromTexture(UTexture2D* Texture)
{
	Brush.SetResourceObject(Texture);

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UStatusIndicator::SetBrushFromMaterial(UMaterialInterface* Material)
{
	Brush.SetResourceObject(Material);

	//TODO UMG Check if the material can be used with the UI

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

UMaterialInstanceDynamic* UStatusIndicator::GetDynamicMaterial()
{
	UMaterialInterface* Material = NULL;

	UObject* Resource = Brush.GetResourceObject();
	Material = Cast<UMaterialInterface>(Resource);

	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

		if (!DynamicMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
			Brush.SetResourceObject(DynamicMaterial);

			if (MyImage.IsValid())
			{
				MyImage->SetImage(&Brush);
			}
		}

		return DynamicMaterial;
	}

	//TODO UMG can we do something for textures?  General purpose dynamic material for them?

	return NULL;
}

FReply UStatusIndicator::HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (OnMouseButtonDownEvent.IsBound())
	{
		return OnMouseButtonDownEvent.Execute(Geometry, MouseEvent).NativeReply;
	}

	return FReply::Unhandled();
}

#if WITH_EDITOR

const FSlateBrush* UStatusIndicator::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Image");
}

const FText UStatusIndicator::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

#endif


/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE