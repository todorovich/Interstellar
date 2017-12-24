// Copyright 2017 Micho Todorovich, all rights reserved.

#include "InterstellarPawn.h"

// Sets default values
AInterstellarPawn::AInterstellarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInterstellarPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInterstellarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AInterstellarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

