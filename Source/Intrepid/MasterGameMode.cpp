// Copyright 2017 Micho Todorovich, all rights reserved.

#include "MasterGameMode.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Intrepid.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


void AMasterGameMode::FinishDestroy()
{

	//virtual_world->DestroyWorld(false);
	Super::FinishDestroy();
	//virtual_world->DestroyWorld

}

void AMasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	//const bool InformEngine = false;

	//virtual_world = UWorld::CreateWorld(EWorldType::Game, InformEngine, FName("VirtualWorld"), nullptr, true, ERHIFeatureLevel::ES3_1);

	//UGameViewportClient* viewport = new UGameViewportClient();

	//UGameInstance* instance = new UGameInstance();
	//
	//FWorldContext* context = new FWorldContext();

	//context->SetCurrentWorld(virtual_world);

	//viewport->Init(*context, instance);
	
	//if (virtual_world->GetGameViewport())
	//{
	//	UE_LOG(DebugLog, Log, TEXT("Viewport Exists"));
	//}
	//else
	//{
	//	UE_LOG(DebugLog, Log, TEXT("Viewport Does Not Exist"));

	//}
	
	//UGameplayStatics::OpenLevel(virtual_world, "MainMenu");

	//virtual_world->GetCanvasForRenderingToTarget();

	//auto viewport = virtual_world->GetGameViewport()->set;

}
