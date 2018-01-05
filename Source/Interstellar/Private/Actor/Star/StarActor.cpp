// Copyright 2017 Micho Todorovich, all rights reserved.

#include "StarActor.h"


// Sets default values
AStarActor::AStarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

