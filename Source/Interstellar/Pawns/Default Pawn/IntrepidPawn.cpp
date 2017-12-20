// Copyright 2017 Micho Todorovich, all rights reserved.

#include "IntrepidPawn.h"

// Sets default values
AIntrepidPawn::AIntrepidPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIntrepidPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIntrepidPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AIntrepidPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

