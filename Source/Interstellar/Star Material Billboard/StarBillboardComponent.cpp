// Copyright 2017 Micho Todorovich, all rights reserved.

#include "StarBillboardComponent.h"
#include "Interstellar.h"
#include "EngineGlobals.h"
#include "RHI.h"
#include "RenderResource.h"
#include "VertexFactory.h"
#include "PackedNormal.h"
#include "LocalVertexFactory.h"
#include "PrimitiveViewRelevance.h"
#include "Materials/MaterialInterface.h"
#include "PrimitiveSceneProxy.h"
#include "Engine/CollisionProfile.h"
#include "SceneManagement.h"
#include "Engine/Engine.h"
#include "Engine/LevelStreaming.h"
#include "LevelUtils.h"
#include "PrimitiveSceneProxy.h"
namespace
{
	struct FStarSpriteVertex
	{
		FVector			Position;
		FPackedNormal	TangentX;
		FPackedNormal	TangentZ;
		FColor			Color;
		FVector2D		TextureCoordinates;
	};

	// Vertex Buffer
	class FStarSpriteVertexBuffer : public FVertexBuffer
	{
	public:

		using FVertexBuffer::VertexBufferRHI;

		TArray<FStarSpriteVertex> Vertices;

		virtual void InitRHI() override
		{
			const int SizeInBytes = sizeof(FDynamicMeshVertex);// *Vertices.Num();
			FRHIResourceCreateInfo CreateInfo;
			VertexBufferRHI = RHICreateVertexBuffer(SizeInBytes, BUF_Static, CreateInfo);
			
			// Copy the vertex data into the vertex buffer.
			//void* VertexBufferData = RHILockVertexBuffer(VertexBufferRHI, 0, SizeInBytes, RLM_WriteOnly);
			//FMemory::Memcpy(VertexBufferData, Vertices.GetData(), SizeInBytes);
			//RHIUnlockVertexBuffer(VertexBufferRHI);
		}
	};

	// Index Buffer
	class FStarSpriteIndexBuffer : public FIndexBuffer
	{
	public:
		TArray<int32> Indices;

		virtual void InitRHI() override
		{
			FRHIResourceCreateInfo CreateInfo;
			IndexBufferRHI = RHICreateIndexBuffer(sizeof(int32), /*Indices.Num() * */sizeof(int32), BUF_Static, CreateInfo);
			
			// Write the indices to the index buffer.
			//void* Buffer = RHILockIndexBuffer(IndexBufferRHI, 0, Indices.Num() * sizeof(int32), RLM_WriteOnly);
			//FMemory::Memcpy(Buffer, Indices.GetData(), Indices.Num() * sizeof(int32));
			//RHIUnlockIndexBuffer(IndexBufferRHI);
		}
	};
	
	// Vertex Factory
	class FStarSpriteVertexFactory : public FLocalVertexFactory
	{
	public:

		/** Initialization */
		void Init(const FStarSpriteVertexBuffer* VertexBuffer)
		{
			check(IsInRenderingThread())

				FDataType NewData;
				NewData.PositionComponent			= STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FStarSpriteVertex, Position, VET_Float3);
				NewData.TangentBasisComponents[0]	= STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FStarSpriteVertex, TangentX, VET_PackedNormal);
				NewData.TangentBasisComponents[1]	= STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FStarSpriteVertex, TangentZ, VET_PackedNormal);
				NewData.ColorComponent				= STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FStarSpriteVertex, Color, VET_Color);
				NewData.TextureCoordinates.Add(FVertexStreamComponent(VertexBuffer, STRUCT_OFFSET(FStarSpriteVertex, TextureCoordinates), sizeof(FStarSpriteVertex), VET_Float2));
			
				SetData(NewData);
		}
	};

	class FMaterialSpriteVertexArray : public FOneFrameResource
	{
	public:
		TArray<FStarSpriteVertex, TInlineAllocator<4> > Vertices;
	};
	
	class FStarSpriteSceneProxy : public FPrimitiveSceneProxy
	{
	public:
		/** Initialization constructor. */
		FStarSpriteSceneProxy(const UStarBillboardComponent* InComponent)
			: FPrimitiveSceneProxy(InComponent)
		{
			AActor* Owner = InComponent->GetOwner();
			if (Owner)
			{
				// Level colorization
				ULevel* Level = Owner->GetLevel();
				ULevelStreaming* LevelStreaming = FLevelUtils::FindStreamingLevel(Level);
				if (LevelStreaming)
				{
					// Selection takes priority over level coloration.
					LevelColor = LevelStreaming->LevelColor;
				}
			}

			Material = InComponent->GetStarSpriteParameters().Material;
			
			if (Material)
			{
				MaterialRelevance |= Material->GetRelevance(GetScene().GetFeatureLevel());
			}

			Radius = InComponent->GetStarSpriteParameters().BaseRadius;

			FColor NewPropertyColor;
			GEngine->GetPropertyColorationColor((UObject*)InComponent, NewPropertyColor);
			PropertyColor = NewPropertyColor;
		}

		~FStarSpriteSceneProxy()
		{
			VertexBuffer.ReleaseResource();
			IndexBuffer.ReleaseResource();
			VertexFactory.ReleaseResource();
		}

		virtual void CreateRenderThreadResources() override
		{
			//BuildMesh();

			VertexFactory.Init(&VertexBuffer);

			VertexBuffer.InitResource();
			IndexBuffer.InitResource();
			VertexFactory.InitResource();


		}

		virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
		{
			//Super::GetDynamicMeshElements(Views, ViewFamily, VisibilityMap, Collector);

			//QUICK_SCOPE_CYCLE_COUNTER(STAT_MaterialSpriteSceneProxy_GetDynamicMeshElements);

			if (!Material)
			{
				return;
			}

			const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

			auto WireframeMaterialInstance = new FColoredMaterialRenderProxy(
				GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy(IsSelected()) : NULL,
				FLinearColor(0, 0.5f, 1.f)
			);

			Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);

			FMaterialRenderProxy* MaterialProxy = NULL;
			if (bWireframe)
			{
				MaterialProxy = WireframeMaterialInstance;
			}
			else
			{
				MaterialProxy = Material->GetRenderProxy(IsSelected());
			}

			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{
				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];

					const bool bIsWireframe = View->Family->EngineShowFlags.Wireframe;
					// Determine the position of the source
					const FVector SourcePosition = GetLocalToWorld().GetOrigin();
					const FVector CameraToSource = View->ViewMatrices.GetViewOrigin() - SourcePosition;
					const float DistanceToSource = CameraToSource.Size();

					const FVector CameraUp = -View->ViewMatrices.GetInvViewProjectionMatrix().TransformVector(FVector(1.0f, 0.0f, 0.0f));
					const FVector CameraRight = -View->ViewMatrices.GetInvViewProjectionMatrix().TransformVector(FVector(0.0f, 1.0f, 0.0f));
					const FVector CameraForward = -View->ViewMatrices.GetInvViewProjectionMatrix().TransformVector(FVector(0.0f, 0.0f, 1.0f));
					const FMatrix WorldToLocal = GetLocalToWorld().InverseFast();
					const FVector LocalCameraUp = WorldToLocal.TransformVector(CameraUp);
					const FVector LocalCameraRight = WorldToLocal.TransformVector(CameraRight);
					const FVector LocalCameraForward = WorldToLocal.TransformVector(CameraForward);

					// Convert the size into world-space.
					const float W = View->ViewMatrices.GetViewProjectionMatrix().TransformPosition(SourcePosition).W;
					const float AspectRatio = CameraRight.Size() / CameraUp.Size();
					const float WorldSizeX = Radius * W;
					const float WorldSizeY = Radius * AspectRatio * W;

					// Evaluate the color/opacity of the sprite.
					FLinearColor Color = FLinearColor::White;

					// Set up the sprite vertex attributes that are constant across the sprite.
					FMaterialSpriteVertexArray& VertexArray = Collector.AllocateOneFrameResource<FMaterialSpriteVertexArray>();
					VertexArray.Vertices.Empty(4);
					VertexArray.Vertices.AddUninitialized(4);

					for (uint32 VertexIndex = 0; VertexIndex < 4; ++VertexIndex)
					{
						VertexArray.Vertices[VertexIndex].Color = Color.ToFColor(true);
						VertexArray.Vertices[VertexIndex].TangentX = FPackedNormal(LocalCameraRight.GetSafeNormal());
						VertexArray.Vertices[VertexIndex].TangentZ = FPackedNormal(-LocalCameraForward.GetSafeNormal());
					}

					// Set up the sprite vertex positions and texture coordinates.
					VertexArray.Vertices[3].Position = -WorldSizeX * LocalCameraRight + +WorldSizeY * LocalCameraUp;
					VertexArray.Vertices[3].TextureCoordinates = FVector2D(0, 0);
					VertexArray.Vertices[2].Position = +WorldSizeX * LocalCameraRight + +WorldSizeY * LocalCameraUp;
					VertexArray.Vertices[2].TextureCoordinates = FVector2D(0, 1);
					VertexArray.Vertices[1].Position = -WorldSizeX * LocalCameraRight + -WorldSizeY * LocalCameraUp;
					VertexArray.Vertices[1].TextureCoordinates = FVector2D(1, 0);
					VertexArray.Vertices[0].Position = +WorldSizeX * LocalCameraRight + -WorldSizeY * LocalCameraUp;
					VertexArray.Vertices[0].TextureCoordinates = FVector2D(1, 1);

					// Set up the FMeshElement.
					FMeshBatch& Mesh					= Collector.AllocateMesh();
					Mesh.UseDynamicData					= true;
					Mesh.DynamicVertexData				= VertexArray.Vertices.GetData();
					Mesh.DynamicVertexStride			= sizeof(FStarSpriteVertex);
					Mesh.VertexFactory					= &VertexFactory;
					Mesh.MaterialRenderProxy			= Material->GetRenderProxy((View->Family->EngineShowFlags.Selection) && IsSelected(), IsHovered());
					Mesh.LCI							= NULL;
					Mesh.ReverseCulling					= IsLocalToWorldDeterminantNegative() ? true : false;
					Mesh.CastShadow						= false;
					Mesh.DepthPriorityGroup				= (ESceneDepthPriorityGroup)GetDepthPriorityGroup(View);
					Mesh.Type							= PT_TriangleStrip;
					Mesh.bDisableBackfaceCulling		= true;
					Mesh.bCanApplyViewModeOverrides		= true;
					Mesh.bUseWireframeSelectionColoring = IsSelected();

					// Set up the FMeshBatchElement.
					FMeshBatchElement& BatchElement		= Mesh.Elements[0];
					BatchElement.IndexBuffer			= NULL;
					BatchElement.DynamicIndexData		= NULL;
					BatchElement.DynamicIndexStride		= 0;
					BatchElement.FirstIndex				= 0;
					BatchElement.MinVertexIndex			= 0;
					BatchElement.MaxVertexIndex			= 3;
					BatchElement.PrimitiveUniformBuffer = GetUniformBuffer();
					BatchElement.NumPrimitives			= 2;


					Collector.AddMesh(ViewIndex, Mesh);


#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
					//RenderBounds(Collector.GetPDI(ViewIndex), View->Family->EngineShowFlags, GetBounds(), IsSelected());
#endif
				}
			}
		}
		
		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
		{
			bool bVisible = true; // View->Family->EngineShowFlags.BillboardSprites;
			FPrimitiveViewRelevance Result;
			Result.bDrawRelevance = true; // IsShown(View);
			Result.bDynamicRelevance = true;

			MaterialRelevance.SetPrimitiveViewRelevance(Result);
			return Result;
		}
		
		virtual bool CanBeOccluded() const override { return !MaterialRelevance.bDisableDepthTest; }
		virtual uint32 GetMemoryFootprint() const override { return sizeof(*this) + GetAllocatedSize(); }
		uint32 GetAllocatedSize() const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

	private:
		UMaterialInterface*			Material;
		FMaterialRelevance			MaterialRelevance;
		FStarSpriteVertexBuffer		VertexBuffer;
		FStarSpriteIndexBuffer		IndexBuffer;
		FStarSpriteVertexFactory	VertexFactory;
		float Radius;
	};
}

UStarBillboardComponent::UStarBillboardComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void UStarBillboardComponent::SetMaterial(int32 ElementIndex, class UMaterialInterface* Material)
{
	if (ElementIndex == 0)
	{
		StarSpriteParameters.Material = Material;
		MarkRenderStateDirty();
	}
}

void UStarBillboardComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.AddUnique(StarSpriteParameters.Material);
}

int32 UStarBillboardComponent::GetNumMaterials() const
{
	return 1;
}

FPrimitiveSceneProxy* UStarBillboardComponent::CreateSceneProxy()
{
	return new FStarSpriteSceneProxy(this);
}

FBoxSphereBounds UStarBillboardComponent::CalcBounds(const FTransform & LocalToWorld) const
{
	float BoundsSize = float(HALF_WORLD_MAX);
	
	BoundsSize *= LocalToWorld.GetMaximumAxisScale();

	return FBoxSphereBounds(LocalToWorld.GetLocation(), FVector(BoundsSize, BoundsSize, BoundsSize), FMath::Sqrt(3.0f * FMath::Square(BoundsSize)));

}

UMaterialInterface* UStarBillboardComponent::GetMaterial(int32 Index) const
{
	UMaterialInterface* ResultMI = nullptr;
	if (Index == 0)
	{
		ResultMI = StarSpriteParameters.Material;
	}
	return ResultMI;
}

#if WITH_EDITOR
void UStarBillboardComponent::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{	
	//if (StarSpriteParameters.Material)
	//{		
	//	StarSpriteParameters.BaseRadius = 1.0f / 1080.0f;
	//}
	
	MarkRenderStateDirty();
}
#endif