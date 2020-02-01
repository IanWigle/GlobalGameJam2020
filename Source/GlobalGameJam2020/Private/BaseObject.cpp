// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseObject::ABaseObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	m_Mesh->SetSimulatePhysics(true);
	m_Mesh->SetGenerateOverlapEvents(true);
	SetRootComponent(m_Mesh);

	Tags.Add("Interactable");
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

