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

//For UE4 Profiler ~ Stat
DECLARE_CYCLE_STAT(TEXT("StarBillboard - GetDynamicMeshElements"), STAT_StarBillboard_GetDynamicMeshElements, STATGROUP_StarBillboard);

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
			, DynamicMaterial(nullptr)
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

			const auto Parameters = InComponent->GetStarSpriteParameters();

			Material			= Parameters.Material;
			DynamicMaterial     = Parameters.DynamicMaterial;
			StarColor			= Parameters.StarColor;
			StarColorIndex		= Parameters.StarColorIndex;
			Radius				= Parameters.Radius;
			SectorCoordinates	= Parameters.SectorCoordinates;
			SectorOffset		= Parameters.SectorOffset;
			WorldOriginOffset	= InComponent->GetWorld()->OriginLocation;
			
			Location_WS	=  FVector( (SectorCoordinates.X  - WorldOriginOffset.X) + SectorOffset.X
								  , (SectorCoordinates.Y  - WorldOriginOffset.Y) + SectorOffset.Y
							  	  , (SectorCoordinates.Z  - WorldOriginOffset.Z) + SectorOffset.Z);
		
			
			if (Material->IsValidLowLevel())
			{
				if (DynamicMaterial && DynamicMaterial->IsValidLowLevel())
				{
					
					MaterialRelevance |= DynamicMaterial->GetRelevance(GetScene().GetFeatureLevel());
				}
				else
				{
					MaterialRelevance |= Material->GetRelevance(GetScene().GetFeatureLevel());
				}
			}

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


		virtual const TArray<FBoxSphereBounds>* GetOcclusionQueries(const FSceneView* View) const override
		{
			static const float SupposedHFOV = 1.5708; // 90 degrees in Radians

			const auto tanPixel = FMath::Tan((SupposedHFOV / ((View->UnconstrainedViewRect.Max.X < 1080.0f) ? View->UnconstrainedViewRect.Max.X : 1080.0f)));

			const auto Distance = (Location_WS - View->ViewLocation).Size();

			const auto Size = tanPixel * Distance * 2.0f;

			return new TArray<FBoxSphereBounds>{ FBoxSphereBounds(Location_WS, FVector(Size, Size, Size), Size) };
		}

		virtual bool HasSubprimitiveOcclusionQueries() const
		{
			return true;
		}

		virtual void CreateRenderThreadResources() override
		{
			VertexFactory.Init(&VertexBuffer);

			VertexBuffer.InitResource();
			IndexBuffer.InitResource();
			VertexFactory.InitResource();
		}

		virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
		{
			SCOPE_CYCLE_COUNTER(STAT_StarBillboard_GetDynamicMeshElements);

			UMaterialInterface* PreferredMaterial = Material;

			if (DynamicMaterial)
			{
				PreferredMaterial = DynamicMaterial;
			}

			if (PreferredMaterial == nullptr)
			{
				return;
			}

			const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

			FMaterialRenderProxy* MaterialProxy = nullptr;
			if (bWireframe)
			{
				auto WireframeMaterialInstance = new FColoredMaterialRenderProxy(
					GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy(IsSelected()) : NULL,
					FLinearColor(0, 0.5f, 1.f)
				);

				Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);

				MaterialProxy = WireframeMaterialInstance;
			}
			else
			{
				MaterialProxy = PreferredMaterial->GetRenderProxy(IsSelected());
			}

			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{
				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];

					const bool bIsWireframe = View->Family->EngineShowFlags.Wireframe;
					
					// Try to work in viewspace!

					const FVector& ViewLocation_WorldSpace = View->ViewLocation;

					const FVector CameraUp		= -View->ViewMatrices.GetInvViewMatrix().GetUnitAxis(EAxis::Type::X);
					const FVector CameraRight	= -View->ViewMatrices.GetInvViewMatrix().GetUnitAxis(EAxis::Type::Y);
					const FVector CameraForward = -View->ViewMatrices.GetInvViewMatrix().GetUnitAxis(EAxis::Type::Z);					

					// Vector representing View to Local in sector coordinates
					const FLongIntVector	Delta_SectorCoordinates	{ SectorCoordinates - WorldOriginOffset };
					const FVector			Delta_SectorOffset		{ SectorOffset - ViewLocation_WorldSpace };

					// Coordinates below are already expressed relative to the camera, this rotation puts the coordinates into Viewspace
					const FQuat&	ViewSpaceQuaternion	= View->ViewMatrices.GetTranslatedViewMatrix().ToQuat();
					const FVector	ViewToPrimitive		= FVector( Delta_SectorCoordinates.X + Delta_SectorOffset.X
																 , Delta_SectorCoordinates.Y + Delta_SectorOffset.Y
																 , Delta_SectorCoordinates.Z + Delta_SectorOffset.Z );
					
					const FVector PrimitiveCoordinates_ViewSpace{ ViewSpaceQuaternion * ViewToPrimitive };
							
					const float DistanceToCamera = PrimitiveCoordinates_ViewSpace.Size();

					static const float SupposedHFOV = 1.5708; // 90 degrees in Radians

					// Convert the size into world-space.
					float WorldSizeX = Radius;
					float WorldSizeY = Radius;

					const auto tan = Radius / DistanceToCamera;
					
					// Used to ensure our billboard is bigger than a pixel so it will not twinkle.
					static const float Multiplier = .9f;
					
					const auto tanPixel = FMath::Tan((SupposedHFOV / ((View->UnconstrainedViewRect.Max.X < 1080.0f) ? View->UnconstrainedViewRect.Max.X : 1080.0f)));
					
					FLinearColor Color = FLinearColor(StarColor.R, StarColor.G, StarColor.B, 0.1f);

					if (tan < tanPixel)
					{
						WorldSizeX = tanPixel * DistanceToCamera;// *1.1;
						WorldSizeY = tanPixel * DistanceToCamera; //*1.1;
						//Color.A = log(1 + 9 * (tan / tanPixel)) / log(10);						
					}

					if (CurrentStarColor != Color && DynamicMaterial)
					{
						DynamicMaterial->SetVectorParameterByIndex(StarColorIndex, Color);
					}

					// Set up the sprite vertex attributes that are constant across the sprite.
					FMaterialSpriteVertexArray& VertexArray = Collector.AllocateOneFrameResource<FMaterialSpriteVertexArray>();
					VertexArray.Vertices.Empty(4);
					VertexArray.Vertices.AddUninitialized(4);

					for (uint32 VertexIndex = 0; VertexIndex < 4; ++VertexIndex)
					{
						VertexArray.Vertices[VertexIndex].Color		= Color.ToFColor(true);
						VertexArray.Vertices[VertexIndex].TangentX	= FPackedNormal(CameraRight);
						VertexArray.Vertices[VertexIndex].TangentZ	= FPackedNormal(-CameraForward);
					}

					// Set up the sprite vertex positions and texture coordinates.
					VertexArray.Vertices[3].Position = -WorldSizeX * CameraRight + +WorldSizeY * CameraUp;
					VertexArray.Vertices[3].TextureCoordinates = FVector2D(0, 0);					  
					VertexArray.Vertices[2].Position = +WorldSizeX * CameraRight + +WorldSizeY * CameraUp;
					VertexArray.Vertices[2].TextureCoordinates = FVector2D(0, 1);					  
					VertexArray.Vertices[1].Position = -WorldSizeX * CameraRight + -WorldSizeY * CameraUp;
					VertexArray.Vertices[1].TextureCoordinates = FVector2D(1, 0);					  
					VertexArray.Vertices[0].Position = +WorldSizeX * CameraRight + -WorldSizeY * CameraUp;
					VertexArray.Vertices[0].TextureCoordinates = FVector2D(1, 1);

					// Set up the FMeshElement.
					FMeshBatch& Mesh					= Collector.AllocateMesh();
					Mesh.UseDynamicData					= true;
					Mesh.DynamicVertexData				= VertexArray.Vertices.GetData();
					Mesh.DynamicVertexStride			= sizeof(FStarSpriteVertex);
					Mesh.VertexFactory					= &VertexFactory;
					Mesh.MaterialRenderProxy			= PreferredMaterial->GetRenderProxy((View->Family->EngineShowFlags.Selection) && IsSelected(), IsHovered());
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
				}
			}
		}
		
		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
		{

			//const FVector& ViewLocation_WorldSpace = View->ViewMatrices.GetViewMatrix().GetOrigin();

			//const FVector ViewLocation_SectorCoordinates{ FMath::FloorToFloat((ViewLocation_WorldSpace.X + WorldOriginOffset.X) / SectorSize),
			//											  FMath::FloorToFloat((ViewLocation_WorldSpace.Y + WorldOriginOffset.Y) / SectorSize),
			//											  FMath::FloorToFloat((ViewLocation_WorldSpace.Z + WorldOriginOffset.Z) / SectorSize) };

			FPrimitiveViewRelevance Result;

			//auto a = View->ViewMatrices.GetViewProjectionMatrix().TransformFVector4(FVector4(Location_WS, 1.f));

			//FVector NDC = FVector(a.X / a.W, a.Y / a.W, a.Z / a.W);
			//
			//if (FMath::Abs(NDC.X) < 1.0f)
			//{
			//	// the result of this will be x and y coords in -1..1 projection space

			//	// Move from projection space to normalized 0..1 UI space
			//	//const float NormalizedX = (PosInScreenSpace.X / 2.f) + 0.5f;
			//	//const float NormalizedY = 1.f - (PosInScreenSpace.Y / 2.f) - 0.5f;

			
				Result.bDrawRelevance = true;
				Result.bDynamicRelevance = true;

				MaterialRelevance.SetPrimitiveViewRelevance(Result);
			//}
			//else
			//{
			//	Result.bDrawRelevance = false;
			//	Result.bDynamicRelevance = false;
			//}
			//
			return Result;
		}
		
		virtual bool CanBeOccluded() const override { return !MaterialRelevance.bDisableDepthTest; }

		virtual uint32 GetMemoryFootprint() const override { return sizeof(*this) + GetAllocatedSize(); }

		virtual void ApplyWorldOffset(const FLongIntVector& InOffset) override
		{
			FPrimitiveSceneProxy::ApplyWorldOffset(InOffset);
		}

		uint32 GetAllocatedSize() const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

	private:
		UMaterialInterface*			Material;
		UMaterialInstanceDynamic*   DynamicMaterial;
		FMaterialRelevance			MaterialRelevance;
		FStarSpriteVertexBuffer		VertexBuffer;
		FStarSpriteIndexBuffer		IndexBuffer;
		FStarSpriteVertexFactory	VertexFactory;
		FLinearColor				CurrentStarColor;
		FLinearColor				StarColor;
		FLongIntVector				WorldOriginOffset;
		FLongIntVector				SectorCoordinates;
		FVector						Location_WS;
		FVector						WorldPosition;
		FVector						SectorOffset;
		float						Radius;
		int							StarColorIndex;
	};
}


UStarBillboardComponent::UStarBillboardComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	this->bAllowCullDistanceVolume	= false;
	this->CachedMaxDrawDistance		= 0.0f;
	this->LDMaxDrawDistance			= 0.0f;

}

UStarBillboardComponent::~UStarBillboardComponent()
{
}

void UStarBillboardComponent::SetMaterial(int32 ElementIndex, class UMaterialInterface* Material)
{
	if (ElementIndex == 0 && Material)
	{
		StarSpriteParameters.Material = Material; 

		CreateDynamicMaterial();
		
		MarkRenderStateDirty();
	}
}

void UStarBillboardComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.AddUnique(StarSpriteParameters.Material);
	OutMaterials.AddUnique(StarSpriteParameters.DynamicMaterial);
}

int32 UStarBillboardComponent::GetNumMaterials() const
{
	return 2;
}

void UStarBillboardComponent::SetSize(float NewSize)
{
	StarSpriteParameters.Radius = NewSize;

	//this->LDMaxDrawDistance = StarSpriteParameters.Radius * 10000;

	MarkRenderStateDirty();
}

void UStarBillboardComponent::SetColorTemperature(int NewColorTemperature)
{
	StarSpriteParameters.ColorTemperature = NewColorTemperature;
	StarSpriteParameters.StarColor = FLinearColor::MakeFromColorTemperature(StarSpriteParameters.ColorTemperature);
	StarSpriteParameters.DynamicMaterial->SetVectorParameterByIndex(StarSpriteParameters.StarColorIndex, StarSpriteParameters.StarColor);

	MarkRenderStateDirty();
}

void UStarBillboardComponent::SetSectorCoordinates(const FLongIntVector& NewCoordinates)
{
	StarSpriteParameters.SectorCoordinates = NewCoordinates;
	
	MarkRenderStateDirty();
}

void UStarBillboardComponent::SetLocalCoordinates(const FVector& NewCoordinates)
{
	StarSpriteParameters.SectorOffset = NewCoordinates;

	MarkRenderStateDirty();
}

FPrimitiveSceneProxy* UStarBillboardComponent::CreateSceneProxy()
{
	return new FStarSpriteSceneProxy(this);
}

FBoxSphereBounds UStarBillboardComponent::CalcBounds(const FTransform & LocalToWorld) const
{

	if (StarSpriteParameters.Radius)
	{
		return FBoxSphereBounds(LocalToWorld.GetLocation(), FVector(StarSpriteParameters.Radius, StarSpriteParameters.Radius, StarSpriteParameters.Radius), StarSpriteParameters.Radius);
	}
	else
	{
		return FBoxSphereBounds(LocalToWorld.GetLocation(), FVector(FLT_MAX, FLT_MAX, FLT_MAX), FLT_MAX);
	}
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
	if (PropertyChangedEvent.GetPropertyName() == FName("DontUseColorTemperature") ||
		PropertyChangedEvent.GetPropertyName() == FName("ColorTemperature"))
	{
		if (!StarSpriteParameters.DontUseColorTemperature)
		{
			StarSpriteParameters.StarColor = FLinearColor::MakeFromColorTemperature(StarSpriteParameters.ColorTemperature);
			StarSpriteParameters.DynamicMaterial->SetVectorParameterByIndex(StarSpriteParameters.StarColorIndex, StarSpriteParameters.StarColor);
		}
	}

	if (PropertyChangedEvent.GetPropertyName() == FName("Material"))
	{

		if (StarSpriteParameters.Material && !StarSpriteParameters.DynamicMaterial)
		{
			CreateDynamicMaterial();
		}
	}

	MarkRenderStateDirty();
}
#endif

bool UStarBillboardComponent::CreateDynamicMaterial()
{
	if (StarSpriteParameters.Material)
	{
		StarSpriteParameters.DynamicMaterial = UMaterialInstanceDynamic::Create(StarSpriteParameters.Material, this);

		if (StarSpriteParameters.DynamicMaterial)
		{
			StarSpriteParameters.DynamicMaterial->InitializeVectorParameterAndGetIndex(FName("StarColor"), StarSpriteParameters.StarColor, StarSpriteParameters.StarColorIndex);

			return true;
		}
	}

	return false;
}

inline UMaterialInstanceDynamic * const FStarSpriteParameters::GetDynamicMaterialInstance() const
{

	return DynamicMaterial;
}
