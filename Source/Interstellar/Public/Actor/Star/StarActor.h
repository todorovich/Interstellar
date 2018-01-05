// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarActor.generated.h"

class UStarBillboardComponent;

UCLASS()
class INTERSTELLAR_API AStarActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Star Size (Solar Radii)"))
	float SizeSolarRadii;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", meta = (DisplayName = "Color Temperature °K"))
	int ColorTemperatureKelvin;

	// Sets default values for this actor's properties
	AStarActor(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//virtual void PostEditUndo() override;
#endif

	//virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star", Transient)
	UStarBillboardComponent* StarBillboard;
};
