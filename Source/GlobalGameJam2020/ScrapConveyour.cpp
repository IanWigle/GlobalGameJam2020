// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapConveyour.h"
#include "Public/BaseObject.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AScrapConveyour::AScrapConveyour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Component initialization
	//Colliders
	//Conveyour
	m_conveyourCollider = CreateDefaultSubobject<UBoxComponent>("Coveyour Collider");
	m_conveyourCollider->SetCollisionProfileName("OverlapAllDynamic");
	m_conveyourCollider->SetSimulatePhysics(false);
	m_conveyourCollider->SetupAttachment(RootComponent);
	m_conveyourCollider->OnComponentBeginOverlap.AddDynamic(this, &AScrapConveyour::OnConveyourOverlapBegin);
	m_conveyourCollider->OnComponentEndOverlap.AddDynamic(this, &AScrapConveyour::OnConveyourOverlapEnd);

	//Furnace
	m_furnaceCollider = CreateDefaultSubobject<UBoxComponent>("Furnace Trigger");
	m_furnaceCollider->SetCollisionProfileName("OverlapAllDynamic");
	m_furnaceCollider->SetGenerateOverlapEvents(true);
	m_furnaceCollider->SetSimulatePhysics(false);
	m_furnaceCollider->SetupAttachment(RootComponent);
	m_furnaceCollider->OnComponentBeginOverlap.AddDynamic(this, &AScrapConveyour::OnFurnaceOverlapBegin);

	//Drop
	m_dropCollider = CreateDefaultSubobject<UBoxComponent>("Drop Trigger");
	m_dropCollider->SetCollisionProfileName("NoCollision");
	m_dropCollider->SetGenerateOverlapEvents(true);
	m_dropCollider->SetSimulatePhysics(false);
	m_dropCollider->SetupAttachment(RootComponent);

	//Meshes
	//Conveyour
	m_conveyourMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Conveyour Mesh");
	m_conveyourMesh->SetCollisionProfileName("PhysicsActor");
	m_conveyourMesh->SetSimulatePhysics(false);
	m_conveyourMesh->SetupAttachment(m_conveyourCollider);

	//Furnace
	m_furnaceMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Furnace Mesh");
	m_furnaceMesh->SetCollisionProfileName("NoCollision");
	m_furnaceMesh->SetSimulatePhysics(false);
	m_furnaceMesh->SetupAttachment(m_furnaceCollider);

	//Drop
	m_dropMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Drop Mesh");
	m_dropMesh->SetCollisionProfileName("NoCollision");
	m_dropMesh->SetSimulatePhysics(false);
	m_dropMesh->SetupAttachment(m_dropCollider);
}

// Called when the game starts or when spawned
void AScrapConveyour::BeginPlay()
{
	Super::BeginPlay();
	//Find all the meshes in the mesh folder

	//populate pool
	if (m_scrapTemplate)
	{
		FActorSpawnParameters spawnParams;
		for (int i = 0; i < m_poolSize; i++)
		{
			ABaseObject* scrap = GetWorld()->SpawnActor<ABaseObject>(m_scrapTemplate, m_dropCollider->GetComponentLocation(), FRotator(), spawnParams);
			AddBaseObjectToPool(scrap);
		}
	}
	//timer to start spawning scraps
	GetWorld()->GetTimerManager().SetTimer(m_scrapSpawnTimer, this, &AScrapConveyour::DropBaseObjectFromPool, m_dropDelay, true, m_dropDelay);
}

// Called every frame
void AScrapConveyour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	while (m_scrapOnConveyourToRemove.Num() > 0)
	{
		m_scrapOnConveyour.Remove(m_scrapOnConveyourToRemove.Pop());
	}
	for (ABaseObject* scrap : m_scrapOnConveyour)
	{
		scrap->SetActorLocation(scrap->GetActorLocation() + m_conveyourCollider->GetForwardVector() * m_conveyourSpeed * DeltaTime);
	}
}

void AScrapConveyour::OnFurnaceOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if the overlapping object is a base object call the return to pool function in it passing yourself
	ABaseObject* scrap = Cast<ABaseObject>(OtherActor);
	if (scrap)
	{
		scrap->ReturnToPool(this);
	}
}

void AScrapConveyour::OnConveyourOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseObject* scrap = Cast<ABaseObject>(OtherActor);
	if (scrap && !scrap->m_BeingHeld)
	{
		scrap->m_Mesh->SetSimulatePhysics(false);
		m_scrapOnConveyour.Add(scrap);
	}
}

void AScrapConveyour::OnConveyourOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseObject* scrap = Cast<ABaseObject>(OtherActor);
	if (scrap)
	{
		if (!scrap->m_BeingHeld)
		{
			scrap->m_Mesh->SetSimulatePhysics(true);
		}

		//Cast<UPrimitiveComponent>(scrap->GetRootComponent())->AddForce(m_conveyourCollider->GetForwardVector() * 1000);
		m_scrapOnConveyourToRemove.Add(scrap);
	}
}

void AScrapConveyour::AddBaseObjectToPool(ABaseObject* a_scrap)
{
	//Add to the TArray
	m_scrapPool.Add(a_scrap);
	//disable mesh, collision and physics
	a_scrap->DisableObject();
	a_scrap->TeleportTo(FVector::ZeroVector, FRotator());
}

void AScrapConveyour::DropBaseObjectFromPool()
{
	if (m_scrapPool.Num() > 0)
	{
		//Remove from the TArray if there are any objects in it
		ABaseObject* scrap = m_scrapPool.Pop();
		//Position the object
		scrap->TeleportTo(m_dropCollider->GetComponentLocation(), FRotator());
		//Switch its mesh
		if (m_scrapMeshes.Num() > 0)
		{
			int index = FMath::RandRange(0, m_scrapMeshes.Num() - 1);
			scrap->m_Mesh->SetSkeletalMesh(m_scrapMeshes[index].m_mesh);
			scrap->m_Mesh->SetPhysicsAsset(m_scrapMeshes[index].m_meshPhysics);
		}
		//Enable mesh, collision and physics
		scrap->EnableObject();
	}
}

