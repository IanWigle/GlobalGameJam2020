// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapConveyour.h"
#include "Public/BaseObject.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"


// Sets default values
AScrapConveyour::AScrapConveyour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Component initialization
	UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>("Furnace Trigger");
	m_colliders.Add("Furnace Trigger", box);
	UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>("Drop Trigger");
	m_colliders.Add("Drop Trigger", box);
	UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>("Coveyour Trigger");
	m_colliders.Add("Coveyour Trigger", box);

	USkeletalMeshComponent* mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Furnace Mesh");
	m_Meshes.Add("Furnace Mesh", mesh);
	USkeletalMeshComponent* mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Drop Mesh");
	m_Meshes.Add("Drop Mesh", mesh);
	USkeletalMeshComponent* mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Conveyour Mesh");
	m_Meshes.Add("Conveyour Mesh", mesh);
}

// Called when the game starts or when spawned
void AScrapConveyour::BeginPlay()
{
	Super::BeginPlay();
	//Find all the meshes in the mesh folder
	//populate pool
	FActorSpawnParameters spawnParams;
	for (int i =0; i<m_poolSize; i++)
	{
		GetWorld()->SpawnActor<ABaseObject>(m_scrapTemplate, m_colliders["Drop Trigger"]->GetComponentLocation(), FRotator(), spawnParams);
	}
	//timer to start spawning scraps
	GetWorld()->GetTimerManager().SetTimer(m_scrapSpawnTimer, this, AScrapConveyour::DropBaseObjectFromPool, m_dropDelay, false, m_dropDelay);
}

// Called every frame
void AScrapConveyour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScrapConveyour::OnFurnaceOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if the overlapping object is a base object call the return to pool function in it passing yourself
}

void AScrapConveyour::AddBaseObjectToPool()
{
	//Add to the TArray
	//disable mesh, collision and physics
}

void AScrapConveyour::DropBaseObjectFromPool()
{
	//Remove from the TArray if there are any objects in it
	ABaseObject* scrap = m_scrapPool.Pop();
	//Position the object
	scrap->TeleportTo(m_colliders["Drop Trigger"]->GetComponentLocation(), );
	//Switch its mesh
	//Enable mesh, collision and physics
}

