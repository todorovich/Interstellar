// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"
#include "UObject/ObjectMacros.h"
#include "Components/PrimitiveComponent.h"
#include "StarBillboardComponent.generated.h"


//For UE4 Profiler ~ Stat Group
DECLARE_STATS_GROUP(TEXT("StarBillboard"), STATGROUP_StarBillboard, STATCAT_Advanced);

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
	UMaterialInterface* Material;
	
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadonly, Category = "StarSpriteElement")
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement|Color", meta = (EditCondition = DontUseColorTemperature))
	FLinearColor StarColor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StarSpriteElement|Color")
	int StarColorIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement")
	float BaseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement|ColorTemperature")
	bool DontUseColorTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSpriteElement|ColorTemperature", meta = (ClampMin = "1000", ClampMax = "10000", UIMin = "1000", UIMax = "10000"))
	int ColorTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Sector Space Coordinates"))
	FIntVector SectorCoordinates;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Sector Space Coordinates"))
	FVector SectorOffset;

	friend FArchive& operator<<(FArchive& Ar, FStarSpriteParameters& LODElement);

	UMaterialInstanceDynamic* const GetDynamicMaterialInstance() const;
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

	~UStarBillboardComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star")
	FStarSpriteParameters StarSpriteParameters;

	/** Get this actor's image plates */
	UFUNCTION(BlueprintCallable,  Category = "Star")
	const FStarSpriteParameters& GetStarSpriteParameters() const
	{
		return StarSpriteParameters;
	}

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual UMaterialInterface* GetMaterial(int32 Index) const override;
	virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override;	
	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;
	virtual int32 GetNumMaterials() const override;

	bool CreateDynamicMaterial();
	
	void SetSize(float NewSize);

	void SetColorTemperature(int NewColorTemperature);

	void SetSectorCoordinates(const FIntVector& NewCoordinates);

	void SetLocalCoordinates(const FVector& NewCoordinates);
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//virtual void PostEditUndo() override;
#endif
};
