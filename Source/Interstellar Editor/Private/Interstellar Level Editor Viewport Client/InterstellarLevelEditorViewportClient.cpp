// Copyright 2017 Micho Todorovich, all rights reserved.

#include "InterstellarLevelEditorViewportClient.h"
#include "CameraController.h"
#include "Editor/Matinee/Public/IMatinee.h"
#include "Editor/Matinee/Public/MatineeConstants.h"
#include "Matinee/MatineeActor.h"
#include "LevelEditorViewport.h"
#include "MouseDeltaTracker.h"
#include "SEditorViewport.h"
#include "SharedPointer.h"
#include "SlateApplication.h"
#include "Settings/LevelEditorViewportSettings.h"

#define LOCTEXT_NAMESPACE "InterstellarLevelEditorViewportClient"

class INTERSTELLAREDITOR_API FInterstellarLevelEditorViewportClient : public FLevelEditorViewportClient
{
	using FEditorViewportClient::MaxCameraSpeeds;

	FVector CurrentLocation = FVector::ZeroVector;

	FIntVector CurrentSectorCoordinates = FIntVector::ZeroValue;
	FIntVector PreviousSectorCoordinates = FIntVector::ZeroValue;

	bool differentLocation = false;

public:
	FInterstellarLevelEditorViewportClient(const TSharedPtr<class SLevelViewport>& InLevelViewport)
		: FLevelEditorViewportClient(InLevelViewport)
	{
		MaxCameraSpeeds = 32.0f;
		CameraController->GetConfig().bUsePhysicsBasedFOV = false;
		CameraController->GetConfig().bUsePhysicsBasedMovement = false;
		CameraController->GetConfig().MaximumMovementSpeed = FLT_MAX;
		
		DrawHelper.bDrawGrid = false;

		bIsRealtime = true;
	}

	virtual void Tick(float deltaTime) override
	{
		FLevelEditorViewportClient::Tick(deltaTime);

		if (CurrentLocation != GetViewLocation())
		{
			differentLocation = true;
		}
		else
		{
			differentLocation = false;
		}
		//FLongIntVector Offset = FLongIntVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z);

		//if (CurrentLocation.SizeSquared() >= FMath::Pow(800000, 2))
		//{
		//	GetWorld()->RequestNewWorldOrigin(Offset);
		//	
		//	ViewTransformPerspective.SetLocation(FVector::ZeroVector);		
		//}
	}

	virtual void UpdateCameraMovement(float DeltaTime) override
	{
		//FEditorViewportClient::UpdateCameraMovement(DeltaTime);

		PreviousSectorCoordinates = CurrentSectorCoordinates;
		
		CurrentLocation = ViewTransformPerspective.GetLocation();

		// We only want to move perspective cameras around like this
		if (Viewport != NULL && IsPerspective() && !ShouldOrbitCamera())
		{
			//bShouldInvalidateViewportWidget = true;

			const bool bEnable = false;
			ToggleOrbitCamera(bEnable);

			const bool bIsUsingTrackpad = FSlateApplication::Get().IsUsingTrackpad();

			// Certain keys are only available while the flight camera input mode is active
			const bool bUsingFlightInput = IsFlightCameraInputModeActive() || bIsUsingTrackpad;

			// Is the current press unmodified?
			const bool bUnmodifiedPress = !IsAltPressed() && !IsShiftPressed() && !IsCtrlPressed() && !IsCmdPressed();

			// Do we want to use the regular arrow keys for flight input?
			// Because the arrow keys are used for things like nudging actors, we'll only do this while the press is unmodified
			const bool bRemapArrowKeys = bUnmodifiedPress;

			// Do we want to remap the various WASD keys for flight input?
			const bool bRemapWASDKeys =
				(bUnmodifiedPress) &&
				(GetDefault<ULevelEditorViewportSettings>()->FlightCameraControlType == WASD_Always ||
				(bUsingFlightInput &&
					(GetDefault<ULevelEditorViewportSettings>()->FlightCameraControlType == WASD_RMBOnly && (Viewport->KeyState(EKeys::RightMouseButton) || Viewport->KeyState(EKeys::MiddleMouseButton) || Viewport->KeyState(EKeys::LeftMouseButton) || bIsUsingTrackpad)))) &&
				!MouseDeltaTracker->UsingDragTool();

			// Apply impulse from magnify gesture and reset impulses if we're using WASD keys
			CameraUserImpulseData->MoveForwardBackwardImpulse = GestureMoveForwardBackwardImpulse;
			CameraUserImpulseData->MoveRightLeftImpulse = 0.0f;
			CameraUserImpulseData->MoveUpDownImpulse = 0.0f;
			CameraUserImpulseData->ZoomOutInImpulse = 0.0f;
			CameraUserImpulseData->RotateYawImpulse = 0.0f;
			CameraUserImpulseData->RotatePitchImpulse = 0.0f;
			CameraUserImpulseData->RotateRollImpulse = 0.0f;

			GestureMoveForwardBackwardImpulse = 0.0f;

			bool bForwardKeyState = false;
			bool bBackwardKeyState = false;
			bool bRightKeyState = false;
			bool bLeftKeyState = false;

			bool bUpKeyState = false;
			bool bDownKeyState = false;
			bool bZoomOutKeyState = false;
			bool bZoomInKeyState = false;
			// Iterate through all key mappings to generate key state flags
			for (uint32 i = 0; i < static_cast<uint8>(EMultipleKeyBindingIndex::NumChords); ++i)
			{
				EMultipleKeyBindingIndex ChordIndex = static_cast<EMultipleKeyBindingIndex> (i);
				bForwardKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Forward->GetActiveChord(ChordIndex)->Key);
				bBackwardKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Backward->GetActiveChord(ChordIndex)->Key);
				bRightKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Right->GetActiveChord(ChordIndex)->Key);
				bLeftKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Left->GetActiveChord(ChordIndex)->Key);

				bUpKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Up->GetActiveChord(ChordIndex)->Key);
				bDownKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().Down->GetActiveChord(ChordIndex)->Key);
				bZoomOutKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().FovZoomOut->GetActiveChord(ChordIndex)->Key);
				bZoomInKeyState |= Viewport->KeyState(FViewportNavigationCommands::Get().FovZoomIn->GetActiveChord(ChordIndex)->Key);
			}

			// Forward/back
			if ((bRemapWASDKeys && bForwardKeyState) ||
				(bRemapArrowKeys && Viewport->KeyState(EKeys::Up)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadEight)))
			{
				CameraUserImpulseData->MoveForwardBackwardImpulse += 1.0f;
			}
			if ((bRemapWASDKeys && bBackwardKeyState) ||
				(bRemapArrowKeys && Viewport->KeyState(EKeys::Down)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadTwo)))
			{
				CameraUserImpulseData->MoveForwardBackwardImpulse -= 1.0f;
			}

			// Right/left
			if ((bRemapWASDKeys && bRightKeyState) ||
				(bRemapArrowKeys && Viewport->KeyState(EKeys::Right)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadSix)))
			{
				CameraUserImpulseData->MoveRightLeftImpulse += 1.0f;
			}
			if ((bRemapWASDKeys && bLeftKeyState) ||
				(bRemapArrowKeys && Viewport->KeyState(EKeys::Left)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadFour)))
			{
				CameraUserImpulseData->MoveRightLeftImpulse -= 1.0f;
			}

			// Up/down
			if ((bRemapWASDKeys && bUpKeyState) ||
				(bUnmodifiedPress && Viewport->KeyState(EKeys::PageUp)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && (Viewport->KeyState(EKeys::NumPadNine) || Viewport->KeyState(EKeys::Add))))
			{
				CameraUserImpulseData->MoveUpDownImpulse += 1.0f;
			}
			if ((bRemapWASDKeys && bDownKeyState) ||
				(bUnmodifiedPress && Viewport->KeyState(EKeys::PageDown)) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && (Viewport->KeyState(EKeys::NumPadSeven) || Viewport->KeyState(EKeys::Subtract))))
			{
				CameraUserImpulseData->MoveUpDownImpulse -= 1.0f;
			}

			// Zoom FOV out/in
			if ((bRemapWASDKeys && bZoomOutKeyState) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadOne)))
			{
				CameraUserImpulseData->ZoomOutInImpulse += 1.0f;
			}
			if ((bRemapWASDKeys && bZoomInKeyState) ||
				(bUnmodifiedPress && bUseNumpadCameraControl && Viewport->KeyState(EKeys::NumPadThree)))
			{
				CameraUserImpulseData->ZoomOutInImpulse -= 1.0f;
			}

			// Record Stats
			if (CameraUserImpulseData->MoveForwardBackwardImpulse != 0 || CameraUserImpulseData->MoveRightLeftImpulse != 0)
			{
				FEditorViewportStats::Using(FEditorViewportStats::CAT_PERSPECTIVE_KEYBOARD_WASD);
			}
			else if (CameraUserImpulseData->MoveUpDownImpulse != 0)
			{
				FEditorViewportStats::Using(FEditorViewportStats::CAT_PERSPECTIVE_KEYBOARD_UP_DOWN);
			}
			else if (CameraUserImpulseData->ZoomOutInImpulse != 0)
			{
				FEditorViewportStats::Using(FEditorViewportStats::CAT_PERSPECTIVE_KEYBOARD_FOV_ZOOM);
			}

			if (!CameraController->IsRotating())
			{
				CameraController->GetConfig().bForceRotationalPhysics = false;
			}

			bool bIgnoreJoystickControls = false;
			//if we're playing back (without recording), differentLocation input from being processed
			if (RecordingInterpEd && RecordingInterpEd->GetMatineeActor())
			{
				if (RecordingInterpEd->GetMatineeActor()->bIsPlaying && !RecordingInterpEd->IsRecordingInterpValues())
				{
					bIgnoreJoystickControls = true;
				}

				CameraController->GetConfig().bPlanarCamera = (RecordingInterpEd->GetCameraMovementScheme() == MatineeConstants::ECameraScheme::CAMERA_SCHEME_PLANAR_CAM);
			}

			if (GetDefault<ULevelEditorViewportSettings>()->bLevelEditorJoystickControls)
			{
				//Now update for cached joystick info (relative movement first)
				UpdateCameraMovementFromJoystick(true, CameraController->GetConfig());

				//if we're not playing any cinematics right now
				if (!bIgnoreJoystickControls)
				{
					//Now update for cached joystick info (absolute movement second)
					UpdateCameraMovementFromJoystick(false, CameraController->GetConfig());
				}
			}

			FVector NewViewLocation = GetViewLocation();//GetViewLocation();
			FRotator NewViewRotation = GetViewRotation();
			FVector NewViewEuler = GetViewRotation().Euler();
			float NewViewFOV = ViewFOV;

			// We'll combine the regular camera speed scale (controlled by viewport toolbar setting) with
			// the flight camera speed scale (controlled by mouse wheel).
			const float CameraSpeed = FEditorViewportClient::GetCameraSpeed();
			const float FinalCameraSpeedScale = FlightCameraSpeedScale * CameraSpeed;

			// Only allow FOV recoil if flight camera mode is currently inactive.
			//const bool bAllowRecoilIfNoImpulse = (!bUsingFlightInput) && (!IsMatineeRecordingWindow());
			const bool bAllowRecoilIfNoImpulse = false;

			// Update the camera's position, rotation and FOV
			float EditorMovementDeltaUpperBound = 1.0f;	// Never "teleport" the camera further than a reasonable amount after a large quantum

#if UE_BUILD_DEBUG
														// Editor movement is very difficult in debug without this, due to hitching
														// It is better to freeze movement during a hitch than to fly off past where you wanted to go 
														// (considering there will be further hitching trying to get back to where you were)
			EditorMovementDeltaUpperBound = .15f;
#endif
			// Check whether the camera is being moved by the mouse or keyboard
			bool bHasMovement = bIsTracking;

			if ((*CameraUserImpulseData).RotateYawVelocityModifier != 0.0f ||
				(*CameraUserImpulseData).RotatePitchVelocityModifier != 0.0f ||
				(*CameraUserImpulseData).RotateRollVelocityModifier != 0.0f ||
				(*CameraUserImpulseData).MoveForwardBackwardImpulse != 0.0f ||
				(*CameraUserImpulseData).MoveRightLeftImpulse != 0.0f ||
				(*CameraUserImpulseData).MoveUpDownImpulse != 0.0f ||
				(*CameraUserImpulseData).ZoomOutInImpulse != 0.0f ||
				(*CameraUserImpulseData).RotateYawImpulse != 0.0f ||
				(*CameraUserImpulseData).RotatePitchImpulse != 0.0f ||
				(*CameraUserImpulseData).RotateRollImpulse != 0.0f
				)
			{
				bHasMovement = true;
			}

			BeginCameraMovement(bHasMovement);

			CameraController->UpdateSimulation(
				*CameraUserImpulseData,
				FMath::Min(DeltaTime, EditorMovementDeltaUpperBound),
				bAllowRecoilIfNoImpulse,
				FinalCameraSpeedScale,
				NewViewLocation,
				NewViewEuler,
				NewViewFOV);

			// We'll zero out rotation velocity modifier after updating the simulation since these actions
			// are always momentary -- that is, when the user mouse looks some number of pixels,
			// we increment the impulse value right there
			{
				CameraUserImpulseData->RotateYawVelocityModifier = 0.0f;
				CameraUserImpulseData->RotatePitchVelocityModifier = 0.0f;
				CameraUserImpulseData->RotateRollVelocityModifier = 0.0f;
			}


			// Check for rotation difference within a small tolerance, ignoring winding
			if (!GetViewRotation().GetDenormalized().Equals(FRotator::MakeFromEuler(NewViewEuler).GetDenormalized(), SMALL_NUMBER))
			{
				NewViewRotation = FRotator::MakeFromEuler(NewViewEuler);
			}


			// See if translation/rotation have changed
			const bool bTransformDifferent = !NewViewLocation.Equals(GetViewLocation(), SMALL_NUMBER) || NewViewRotation != GetViewRotation();
			// See if FOV has changed
			const bool bFOVDifferent = !FMath::IsNearlyEqual(NewViewFOV, ViewFOV, float(SMALL_NUMBER));

			// If something has changed, tell the actor
			if (bTransformDifferent || bFOVDifferent)
			{
				// Something has changed!
				const bool bInvalidateChildViews = true;

				// When flying the camera around the hit proxies dont need to be invalidated since we are flying around and not clicking on anything
				const bool bInvalidateHitProxies = !IsFlightCameraActive();
				Invalidate(bInvalidateChildViews, bInvalidateHitProxies);
				//Invalidate(bInvalidateChildViews, true);

				// Update the FOV
				ViewFOV = NewViewFOV;

				// Actually move/rotate the camera
				if (bTransformDifferent)
				{
					FLongIntVector Offset = FLongIntVector(NewViewLocation.X, NewViewLocation.Y, NewViewLocation.Z);

					GetWorld()->RequestNewWorldOrigin(GetWorld()->OriginLocation + Offset);
						
					ViewTransformPerspective.SetLocation(FVector::ZeroVector);		

					SetViewRotation(NewViewRotation);
				}

				// Invalidate the viewport widget
				if (EditorViewportWidget.IsValid())
				{
					EditorViewportWidget.Pin()->Invalidate();
				}
			}
		}
	}

	virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override
	{
		FLevelEditorViewportClient::Draw(View, PDI);
	}

	virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override
	{
		FEditorViewportClient::Draw(Viewport, Canvas);	
	}

	virtual float GetCameraSpeed(int32 SpeedSetting) const override
	{
		return FMath::Pow(2.0, SpeedSetting - 4);
	}
};

UInterstellarLevelEditorViewportClient::UInterstellarLevelEditorViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

TSharedPtr<class FLevelEditorViewportClient> UInterstellarLevelEditorViewportClient::Construct(TSharedPtr<class SLevelViewport> LevelViewport)
{
	return MakeShareable(new FInterstellarLevelEditorViewportClient(LevelViewport));
}

#undef LOCTEXT_NAMESPACE

