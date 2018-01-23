// Copyright 2018 Micho Todorovich, all rights reserved.

#include "SceneCapture3D.h"

#include "Misc/ScopeLock.h"
#include "UObject/RenderingObjectVersion.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "RenderingThread.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Components/BillboardComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Texture2D.h"
#include "SceneManagement.h"
#include "Engine/StaticMesh.h"
#include "Engine/SceneCapture.h"
#include "Engine/SceneCaptureCube.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Components/DrawFrustumComponent.h"
#include "Engine/PlanarReflection.h"
#include "Components/PlanarReflectionComponent.h"
#include "PlanarReflectionSceneProxy.h"
#include "Components/BoxComponent.h"
#include "Logging/MessageLog.h"

#define LOCTEXT_NAMESPACE "SceneCapture3D"

ASceneCapture3D::ASceneCapture3D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	const FQuat Rotations[6] = { FQuat()									// Forward
		, FQuat(FVector::RightVector, PI)			// Backward
		, FQuat(FVector::RightVector, PI / 2)		// Top
		, FQuat(FVector::RightVector, -PI / 2)		// Bottom
		, FQuat(FVector::UpVector, -PI / 2)			// Left
		, FQuat(FVector::UpVector, PI / 2)			// Right
	};

	CaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("NewSceneCaptureComponent2D"));
	CaptureComponent2D->SetupAttachment(GetMeshComp());

	CaptureComponent2D->bEnableClipPlane = true;

	for (int i = 0; i < 6; i++)
	{
		const FString message = FString::Printf(TEXT("DrawFrustum %i"), i);

		auto Frustum = CreateDefaultSubobject<UDrawFrustumComponent>(*message);

		Frustum->SetupAttachment(GetMeshComp());

		DrawFrustums.Add(Frustum);

	}
	
	UpdateDrawFrustums();
}

void ASceneCapture3D::OnInterpToggle(bool bEnable)
{
	CaptureComponent2D->SetVisibility(bEnable);
}


void ASceneCapture3D::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UpdateDrawFrustums();
}

void ASceneCapture3D::UpdateDrawFrustums()
{
	static const FQuat Rotations[6] = { FQuat()									// Forward
									  , FQuat(FVector::RightVector, PI)			// Backward
									  , FQuat(FVector::RightVector, PI / 2.0)		// Top
									  , FQuat(FVector::RightVector, -PI / 2.0)	// Bottom
									  , FQuat(FVector::UpVector, -PI / 2.0)		// Left
									  , FQuat(FVector::UpVector, PI / 2.0)		// Right
									  };

	for (int i = 0; i < 6; i++)
	{
		auto Frustum = DrawFrustums[i];

		if (Frustum)
		{
			Frustum->bIsEditorOnly = true;

			Frustum->FrustumAspectRatio = 1.0f;

			Frustum->SetWorldRotation(Rotations[i]);

			Frustum->FrustumStartDist = MinDistance;

			// 1000 is the default frustum distance, ideally this would be infinite but that might cause rendering issues
			//DrawFrustums[i]->FrustumEndDist = (CaptureComponent2D->MaxViewDistanceOverride > DrawFrustums[i]->FrustumStartDist)
			//	? CaptureComponent2D->MaxViewDistanceOverride : 1000.0f;

			Frustum->FrustumEndDist = MaxDistance;

			Frustum->FrustumAngle = 90.f;
			
			Frustum->MarkRenderStateDirty();
		}
	}
}

void ASceneCapture3D::PostActorCreated()
{
	Super::PostActorCreated();

	// no need load the editor mesh when there is no editor
#if WITH_EDITOR
	if(GetMeshComp())
	{
		if (!IsRunningCommandlet())
		{
			if( !GetMeshComp()->GetStaticMesh())
			{
				UStaticMesh* CamMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM"), NULL, LOAD_None, NULL);
				GetMeshComp()->SetStaticMesh(CamMesh);
			}
		}
	}
#endif

	// Sync component with CameraActor frustum settings.
	UpdateDrawFrustums();
}


#if WITH_EDITOR
void ASceneCapture3D::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	auto name = PropertyChangedEvent.Property->GetNameCPP();

	if (name == TEXT("MinDistance"))
	{
		
	}

	if (name == TEXT("MaxDistance"))
	{

	}

	UpdateDrawFrustums();
}
#endif

#undef LOCTEXT_NAMESPACE