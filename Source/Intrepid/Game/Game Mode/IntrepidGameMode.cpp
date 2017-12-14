// Copyright 2017 Micho Todorovich, all rights reserved.

#include "IntrepidGameMode.h"
#include "Intrepid.h"
#include "Intrepid/Game/Game Instance/IntrepidGameInstance.h"
#include "Intrepid/Game/Game State/IntrepidGameState.h"
#include "Intrepid/Game/Game Instance/IntrepidGameInstance.h"
#include "Intrepid/Game/Game Session/IntrepidGameSession.h"
#include "Intrepid/Player/Player Controller/IntrepidPlayerController.h"
#include "Intrepid/Player/Player State/IntrepidPlayerState.h"
#include "Intrepid/Pawns/Default Pawn/IntrepidPawn.h"
#include "Intrepid/Pawns/Spectator Pawn/IntrepidSpectatorPawn.h"


AIntrepidGameMode::AIntrepidGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AIntrepidGameState::StaticClass();
	GameSessionClass = AIntrepidGameSession::StaticClass();
	DefaultPawnClass = AIntrepidPawn::StaticClass();
	PlayerControllerClass = AIntrepidPlayerController::StaticClass();
	PlayerStateClass = AIntrepidPlayerState::StaticClass();
	SpectatorClass = AIntrepidSpectatorPawn::StaticClass();
}


void AIntrepidGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance && Cast<UIntrepidGameInstance>(GameInstance))
	{
		bPauseable = false;
	}*/
}

TSubclassOf<AGameSession> AIntrepidGameMode::GetGameSessionClass() const
{
	return AIntrepidGameSession::StaticClass();
}