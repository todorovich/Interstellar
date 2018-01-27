// Copyright 2017 Micho Todorovich, all rights reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "CoreOnline.h"
#include "CoreMinimal.h"
#include "InterstellarClasses.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(InterstellarLog, Log, All);

// This is not what the ternary operator is for, wtf.
// Unfuck this.
#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
		: (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
		: (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
		: (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
		: TEXT("[Standalone] "))

#if _MSC_VER
#define FUNC_NAME		TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define FILE		TEXT(__FILE__)

#define LOG(Format, ...) \
{\
	const FString message = FString::Printf(TEXT(Format), __VA_ARGS__); \
	UE_LOG(InterstellarLog, Log, TEXT("%s():\t%s: Line: %d:\n\t%s"), FUNC_NAME, FILE, __LINE__,  *message);\
};

#define WARNING(Format, ...) \
{\
	const FString message = FString::Printf(TEXT(Format), __VA_ARGS__); \
	UE_LOG(InterstellarLog, Warning, TEXT("%s():\t%s: Line: %d:\n\t%s"), FUNC_NAME, FILE, __LINE__,  *message);\
};

#define ERROR(Format, ...) \
{\
	const FString message = FString::Printf(TEXT(Format), __VA_ARGS__); \
	UE_LOG(InterstellarLog, Error, TEXT("%s():\t%s: Line: %d:\n\t%s"), FUNC_NAME, FILE, __LINE__,  *message);\
};


const static float SectorSize = 1600000.0f;

class FInterstellarModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
