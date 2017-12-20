// Copyright 2017 Micho Todorovich, all rights reserved.

#include "InterstellarGameMode.h"
#include "Interstellar.h"
#include "Interstellar/Game/Game Instance/InterstellarGameInstance.h"
#include "Interstellar/Game/Game State/InterstellarGameState.h"
#include "Interstellar/Game/Game Instance/InterstellarGameInstance.h"
#include "Interstellar/Game/Game Session/InterstellarGameSession.h"
#include "Interstellar/Player/Player Controller/InterstellarPlayerController.h"
#include "Interstellar/Player/Player State/InterstellarPlayerState.h"
#include "Interstellar/Pawns/Default Pawn/InterstellarPawn.h"
#include "Interstellar/Pawns/Spectator Pawn/InterstellarSpectatorPawn.h"


AInterstellarGameMode::AInterstellarGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AInterstellarGameState::StaticClass();
	GameSessionClass = AInterstellarGameSession::StaticClass();
	DefaultPawnClass = AInterstellarPawn::StaticClass();
	PlayerControllerClass = AInterstellarPlayerController::StaticClass();
	PlayerStateClass = AInterstellarPlayerState::StaticClass();
	SpectatorClass = AInterstellarSpectatorPawn::StaticClass();
}


void AInterstellarGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance && Cast<UInterstellarGameInstance>(GameInstance))
	{
		bPauseable = false;
	}*/
}

TSubclassOf<AGameSession> AInterstellarGameMode::GetGameSessionClass() const
{
	return AInterstellarGameSession::StaticClass();
}