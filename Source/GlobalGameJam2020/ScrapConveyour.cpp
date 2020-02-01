// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapConveyour.h"

// Sets default values
AScrapConveyour::AScrapConveyour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Component initialization

}

// Called when the game starts or when spawned
void AScrapConveyour::BeginPlay()
{
	Super::BeginPlay();
	//Timer? to populate pool
	//timer to start spawning scraps
}

// Called every frame
void AScrapConveyour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

