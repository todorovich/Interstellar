// Copyright 2017 Micho Todorovich, all rights reserved.

#include "Star.h"
#include "Star Material Billboard/StarBillboardComponent.h"
#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "DataSingleton.h"

// Sets default values
AStarActor::AStarActor(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StarBillboard = ObjectInitializer.CreateDefaultSubobject<UStarBillboardComponent>(this, FName("Star Billboard Component"));
	RootComponent = StarBillboard;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> staticAsset(TEXT("Material'/Game/Materials/M_Star.M_Star'"));

	StarBillboard->StarSpriteParameters.Material = staticAsset.Object;
}

// Called when the game starts or when spawned
void AStarActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStarActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (StarBillboard->StarSpriteParameters.Material)
	{
		if (StarBillboard->CreateDynamicMaterial())
		{
			StarBillboard->SetColorTemperature(ColorTemperatureKelvin);
		}
	}

	StarBillboard->SetSectorCoordinates(SectorCoordinates);
	StarBillboard->SetLocalCoordinates(SectorOffset);
	StarBillboard->SetSize(SizeSolarRadii);

	if (auto root = GetRootComponent())
	{
		root->SetWorldLocation(FVector(SectorCoordinates.X * SectorSize, SectorCoordinates.Y * SectorSize, SectorCoordinates.Z * SectorSize) + SectorOffset);
	}
}

void AStarActor::PostInitProperties()
{
	Super::PostInitProperties();


}

void AStarActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	if (StarBillboard->StarSpriteParameters.Material)
	{
		if (StarBillboard->CreateDynamicMaterial())
		{
			StarBillboard->SetColorTemperature(ColorTemperatureKelvin);
		}
	}
	
	StarBillboard->SetSectorCoordinates(SectorCoordinates);
	StarBillboard->SetLocalCoordinates(SectorOffset);
	StarBillboard->SetSize(SizeSolarRadii);

	if (auto root = GetRootComponent())
	{
		root->SetWorldLocation(FVector(SectorCoordinates.X * SectorSize, SectorCoordinates.Y * SectorSize, SectorCoordinates.Z * SectorSize) + SectorOffset);
	}
}

#if WITH_EDITOR
void AStarActor::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (StarBillboard->StarSpriteParameters.Material)
	{
		if (StarBillboard->StarSpriteParameters.DynamicMaterial == nullptr)
		{
			StarBillboard->CreateDynamicMaterial();
		}

		if (StarBillboard->StarSpriteParameters.DynamicMaterial)
		{
			StarBillboard->SetColorTemperature(ColorTemperatureKelvin);
		}	
	}

	StarBillboard->SetSectorCoordinates(SectorCoordinates);
	StarBillboard->SetLocalCoordinates(SectorOffset);	
	StarBillboard->SetSize(SizeSolarRadii);

	if (auto root = GetRootComponent())
	{
		root->SetWorldLocation(FVector(SectorCoordinates.X * SectorSize, SectorCoordinates.Y * SectorSize, SectorCoordinates.Z * SectorSize) + SectorOffset);
	}
}
#endif