// Fill out your copyright notice in the Description page of Project Settings.

#include "DataSingleton.h"

UDataSingleton* const UDataSingleton::Instance()
{
	if (!_instance)
	{
		_instance = NewObject<UDataSingleton>(nullptr, FName("UDataSingleton"));
		_instance->AddToRoot();
	}

	return _instance;
}
