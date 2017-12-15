// Copyright 2017 Micho Todorovich, all rights reserved.

#include "SpaceShip.h"
//#include "Engine.h"
#include "Intrepid.h"
#include "ShieldSystemComponent.h"
#include "UnrealType.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values
ASpaceShip::ASpaceShip(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	shields = ObjectInitializer.CreateDefaultSubobject<UShieldSystemComponent>(this, TEXT("Shields"));

	//CompClass can be a BP
	//shields = NewObject<UShieldSystemComponent>(this, TEXT("ShieldSystem"));
	//
	//if (!shields)
	//{
	//	return;
	//}	
	//FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	//
	//shields->AttachToComponent(GetRootComponent(), rule);
	////could use different than Root Comp
}


// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	shields->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above	 
	//shields->SetActive(true);

	PrimaryActorTick.SetTickFunctionEnable(true);
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//shield_system.Tick(DeltaTime);
}

#if WITH_EDITOR
void ASpaceShip::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UE_LOG(IntrepidLog, Log, TEXT("Post Edit Property Change"));

	switch(PropertyChangedEvent.ChangeType)
	{
		case EPropertyChangeType::Unspecified:
			UE_LOG(IntrepidLog, Log, TEXT("Unspecified"));
			break;

		case EPropertyChangeType::ArrayAdd:

			UE_LOG(IntrepidLog, Log, TEXT("ArrayAdd"));
			break;

		case EPropertyChangeType::ValueSet:

			UE_LOG(IntrepidLog, Log, TEXT("ValueSet"));
			break;

		case EPropertyChangeType::Duplicate:

			UE_LOG(IntrepidLog, Log, TEXT("Duplicate"));
			break;

		case EPropertyChangeType::Interactive:

			UE_LOG(IntrepidLog, Log, TEXT("Interactive"));
			break;

		case EPropertyChangeType::Redirected:

			UE_LOG(IntrepidLog, Log, TEXT("Redirected"));
			break;
	}

	//PropertyChangedEvent.Property->GetClass();

	UE_LOG(IntrepidLog, Log, TEXT("String %s"), *PropertyChangedEvent.GetPropertyName().ToString());

	//UE_LOG(DebugLog, Log, TEXT("String %s"), PropertyChangedEvent.Property())

}
#endif
//inline void FShieldSystem::Tick(float DeltaTime)
//{
//	current_shield_points += recharge_points * DeltaTime;
//
//	if (current_shield_points > max_shield_points)
//	{
//		current_shield_points = max_shield_points;
//	}
//}
