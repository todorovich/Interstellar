// Copyright 2017 Micho Todorovich, all rights reserved.

#include "TestModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FInterstellarTestModule, InterstellarTestModule);

DEFINE_LOG_CATEGORY(InterstellarTestModuleLog);

#define LOCTEXT_NAMESPACE "Test Module"

void FInterstellarTestModule::StartupModule()
{
	WARNING("Interstellar Test Module: Log Started");
}

void FInterstellarTestModule::ShutdownModule()
{
	WARNING("Interstellar Test Module: Log Ended");
}

#undef LOCTEXT_NAMESPACE