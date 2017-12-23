// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"
#include "UObject/ObjectMacros.h"
#include "Components/PrimitiveComponent.h"
#include "StarBillboardComponent.generated.h"

class FPrimitiveSceneProxy;
class UMaterialInterface;
class UMaterialInstanceDynamic;

USTRUCT(BlueprintType)
struct FStarSpriteParameters
{
	GENERATED_BODY()

	FStarSpriteParameters()
		: Material(nullptr)
		, StarColor(1.0,1.0,1.0)
		, DontUseColorTemperature(false)
		, ColorTemperature(5780)
		, BaseRadius(1.0f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement")
	class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement", meta = (EditCondition = DontUseColorTemperature))
	FLinearColor StarColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement")
	float BaseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement|ColorTemperature")
	bool DontUseColorTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement|ColorTemperature", meta = (ClampMin = "1000", ClampMax = "10000", UIMin = "1000", UIMax = "10000"))
	int ColorTemperature;


	friend FArchive& operator<<(FArchive& Ar, FStarSpriteParameters& LODElement);
};


/**
 * 
 */
UCLASS(ClassGroup = Rendering, collapsecategories, hidecategories = (Object, Activation, "Components|Activation", Physics, Collision, Lighting, Mesh, PhysicsVolume), editinlinenew, meta = (BlueprintSpawnableComponent))
class INTERSTELLAR_API UStarBillboardComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	UStarBillboardComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star")
	FStarSpriteParameters StarSpriteParameters;

	/** Get this actor's image plates */
	UFUNCTION(BlueprintCallable,  Category = "Game|Image Plate")
	FStarSpriteParameters GetStarSpriteParameters() const
	{
		return StarSpriteParameters;
	}

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual UMaterialInterface* GetMaterial(int32 Index) const override;
	virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override;
	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;
	
	virtual int32 GetNumMaterials() const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//virtual void PostEditUndo() override;
#endif
};
