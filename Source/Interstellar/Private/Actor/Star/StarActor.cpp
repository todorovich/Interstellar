// Copyright 2017 Micho Todorovich, all rights reserved.

#include "StarActor.h"
#include "StarBillboardComponent.h"
#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "DataSingleton.h"

// Sets default values
AStarActor::AStarActor(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StarBillboard = ObjectInitializer.CreateDefaultSubobject<UStarBillboardComponent>(this, FName("Star Billboard Component"));

	FARFilter filter;
	TArray<FAssetData> assetArray;
	auto assetRegistry = UDataSingleton::GetAssetRegistry();

	// Set up filter to find materials
	filter.PackagePaths.Add("/Game/Materials");
	filter.ClassNames.Add(UMaterial::StaticClass()->GetFName());
	filter.bRecursiveClasses = true;

	assetRegistry->GetAssets(filter, assetArray);

	// Iterate over the materials until the one we want is found.
	for (auto& assetData : assetArray)
	{
		if (assetData.AssetName == FName("M_Star"))
		{
			UE_LOG(InterstellarLog, Log, TEXT("Found M_Star"));
			auto  asset = assetData.GetAsset();
			StarBillboard->SetMaterial(0, Cast<UMaterialInterface>(asset));
		}
	}
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

void AStarActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	StarBillboard->SetSize(SizeSolarRadii);
	StarBillboard->SetColorTemperature(ColorTemperatureKelvin);
	StarBillboard->SetSectorCoordinates(SectorX, SectorY, SectorZ);

	GetRootComponent()->SetWorldLocation(FVector(SectorX * SectorSize, SectorY * SectorSize, SectorZ * SectorSize));
}

#if WITH_EDITOR
void AStarActor::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	StarBillboard->SetSize(SizeSolarRadii);
	StarBillboard->SetColorTemperature(ColorTemperatureKelvin);
	StarBillboard->SetSectorCoordinates(SectorX, SectorY, SectorZ);

	GetRootComponent()->SetWorldLocation(FVector(SectorX * SectorSize, SectorY * SectorSize, SectorZ * SectorSize));
}
#endif