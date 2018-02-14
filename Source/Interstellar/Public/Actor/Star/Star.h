// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"


UCLASS()
class INTERSTELLAR_API AStar : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Star Size (Solar Radii)"))
	float SizeSolarRadii;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Color Temperature °K"), meta = (ClampMin = "1000", ClampMax = "10000", UIMin = "1000", UIMax = "10000"))
	int ColorTemperatureKelvin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Sector Space Coordinate"))
	FLongIntVector SectorCoordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Sector Space Coordinate"))
	FVector SectorOffset;

	// Sets default values for this actor's properties
	AStar(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform & Transform) override;

	virtual void PostInitializeComponents() override;

	virtual void PostInitProperties() override;

	//virtual void ApplyWorldOffset(const FLongIntVector& InOffset, bool bWorldShift) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void UpdateWorldLocation() ;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", Transient)
	class UStarBillboardComponent* StarBillboard;
};
