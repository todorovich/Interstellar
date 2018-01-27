// Copyright 2017 Micho Todorovich, all rights reserved.

#include "Interstellar.h"
#include "InterstellarClasses.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FInterstellarModule, Interstellar, "Interstellar" );

DEFINE_LOG_CATEGORY(InterstellarLog);

void FInterstellarModule::StartupModule()
{
	WARNING("Interstellar Module Started.");
}

void FInterstellarModule::ShutdownModule()
{
	WARNING("Interstellar Module Shutdown.");
}
