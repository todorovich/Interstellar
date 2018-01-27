// Copyright 2017 Micho Todorovich, all rights reserved.

#include "InterstellarEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FInterstellarEditorModule, InterstellarEditor);

DEFINE_LOG_CATEGORY(InterstellarEditorLog);

#define LOCTEXT_NAMESPACE "MyGameEditor"

void FInterstellarEditorModule::StartupModule()
{
	WARNING("IntrepidEditor: Log Started");
}

void FInterstellarEditorModule::ShutdownModule()
{
	WARNING("IntrepidEditor: Log Ended");
}

#undef LOCTEXT_NAMESPACE