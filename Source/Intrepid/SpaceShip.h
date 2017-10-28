// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShip.generated.h"

//USTRUCT(BlueprintType, EditAnywhere, BlueprintReadWrite, Category = "SpaceShip")
//enum SpaceShipComponentType
//{
//	Hull,
//	Armor,
//	Shields,
//	Sublight_Engines,
//	Warp_Engines,
//	Power_Generators,
//	Internal_Force_Fields,
//	Brig,
//	Door,
//	Atmosphere,
//	Medical_Bay,
//	Teleporter,
//	Research_Lab,
//	Weapon,
//	Anntenna,
//	Internal_Senors,
//	External_Senors,
//	Other
//};

USTRUCT(BlueprintType, Category = "Space Ship")
struct FShieldSystem
{
	GENERATED_BODY()

private:
	ASpaceShip* parent_ship;

public:
	FShieldSystem(ASpaceShip* parent_ship)
	{
		ship.shield_system = *this;
	}

	UPROPERTY(EditAnywhere)
	int	max_shield_points = 10;

	UPROPERTY(EditAnywhere)
	int	current_shield_points = 10;

	UPROPERTY(EditAnywhere)
	int	recharge_points = 1;

	virtual void Tick(float DeltaTime);
};



UCLASS()
class INTREPID_API ASpaceShip : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	int max_structure_points = 0;

	UPROPERTY(EditAnywhere)
	int current_structure_points = 0;

	UPROPERTY(EditAnywhere)
	FShieldSystem* shield_system;

	// Sets default values for this actor's properties
	ASpaceShip()
	{
		new FShieldSystem(this);
	};

	~ASpaceShip()
	{
		delete shield_system;
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;
	
	//void CreateComponent(UClass* CompClass, const FVector& Location, const FRotator& Rotation, const FName& AttachSocket);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateGrid();

};
