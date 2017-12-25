// Copyright 2017 Micho Todorovich, all rights reserved.

#include "Interstellar.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FInterstellarModule, Interstellar, "Interstellar" );

DEFINE_LOG_CATEGORY(InterstellarLog);

void FInterstellarModule::StartupModule()
{
	LOG("Interstellar Module Started.");
}

void FInterstellarModule::ShutdownModule()
{
	LOG("Interstellar Module Shutdown.");
}