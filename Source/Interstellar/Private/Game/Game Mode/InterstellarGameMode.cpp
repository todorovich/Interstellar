// Copyright 2017 Micho Todorovich, all rights reserved.

#include "InterstellarGameMode.h"
#include "Interstellar.h"
#include "Game/Game Instance/InterstellarGameInstance.h"
#include "Game/Game State/InterstellarGameState.h"
#include "Game/Game Instance/InterstellarGameInstance.h"
#include "Game/Game Session/InterstellarGameSession.h"
#include "Player/Player Controller/InterstellarPlayerController.h"
#include "Player/Player State/InterstellarPlayerState.h"
#include "Pawns/Default Pawn/InterstellarPawn.h"
#include "Pawns/Spectator Pawn/InterstellarSpectatorPawn.h"


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
