// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueStand.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AStatueStand::AStatueStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_Mesh->SetCollisionProfileName("PhysicsActor");
	SetRootComponent(m_Mesh);
	
	m_BuildArea = CreateDefaultSubobject<UBoxComponent>("Build Area");
	m_BuildArea->SetGenerateOverlapEvents(true);
	m_BuildArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStatueStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatueStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

