// Copyright 2018 Micho Todorovich, all rights reserved.

#pragma once

#include "Interstellar.h"

#include "UObject/ObjectMacros.h"
#include "Engine/SceneCapture.h"

#include "SceneCapture3D.generated.h"

UCLASS(hidecategories=(Collision, Material, Attachment, Actor), MinimalAPI)
class ASceneCapture3D : public ASceneCapture
{
	GENERATED_BODY()

private:

	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* CaptureComponent2D;
	/** To allow drawing the camera frustum in the editor. */
	UPROPERTY()
	TArray<class UDrawFrustumComponent*> DrawFrustums;

public:

	UPROPERTY(Category = DrawDistance, EditAnywhere)
	float MinDistance;

	UPROPERTY(Category = DrawDistance, EditAnywhere)
	float MaxDistance;

	ASceneCapture3D(const FObjectInitializer& ObjectInitializer);

	//~ Begin AActor Interface
	INTERSTELLAR_API virtual void PostActorCreated() override;
	//~ End AActor Interface.

	/** Used to synchronize the DrawFrustumComponent with the SceneCaptureComponent2D settings. */
	void UpdateDrawFrustums();

	UFUNCTION(BlueprintCallable, Category="Rendering")
	void OnInterpToggle(bool bEnable);

	/** Returns CaptureComponent2D subobject **/
	INTERSTELLAR_API class USceneCaptureComponent2D* GetCaptureComponent2D() const { return CaptureComponent2D; }
	/** Returns DrawFrustum subobject **/
	//INTERSTELLAR_API class UDrawFrustumComponent* GetDrawFrustum() const { return *DrawFrustums; }

	virtual void PostInitializeComponents() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 
};



