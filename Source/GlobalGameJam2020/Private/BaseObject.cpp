// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"
#include <EngineGlobals.h>
#include "Components/SkeletalMeshComponent.h"
#include "../ScrapConveyour.h"
#include "Engine/Engine.h"

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
	Tags.Add("Scrap");
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseObject::ReturnToPool(AScrapConveyour* a_Conveyour)
{
	if (m_Conveyour)
	{
		m_Conveyour->AddBaseObjectToPool(this);
	}
	else
	{
		m_Conveyour = a_Conveyour;
		m_Conveyour->AddBaseObjectToPool(this);
	}

	DisableObject();
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseObject::DisableObject()
{
	//m_Mesh->SetCollisionProfileName("NoCollision");
	m_Mesh->SetSimulatePhysics(false);
	m_Mesh->SetGenerateOverlapEvents(false);
	m_Mesh->SetHiddenInGame(true, true);
}

void ABaseObject::EnableObject()
{
	//m_Mesh->SetCollisionProfileName("PhysicsActor");
	m_Mesh->SetSimulatePhysics(true);
	m_Mesh->SetGenerateOverlapEvents(true);
	RootComponent->SetHiddenInGame(false, true);
}

bool ABaseObject::IsFading()
{
	return GetWorld()->GetTimerManager().IsTimerActive(FadeTimer);
}

float ABaseObject::FadeTimeRemaining()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FadeTimer))
		return GetWorld()->GetTimerManager().GetTimerRemaining(FadeTimer);

	return 0.0f;
}

void ABaseObject::StopFade()
{
	if (IsFading())
	{
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
	}
}

void ABaseObject::Weld()
{
	// = > function that when called causes the object to check who is being overlapped and then attach itself to the closest base object that is "Rooted" then sets itself to be rooted
	TArray<AActor*> overlappingActors;
	m_Mesh->GetOverlappingActors(overlappingActors, ABaseObject::StaticClass());
	ABaseObject* closestRootedScrap = nullptr;
	for (AActor* actor : overlappingActors)
	{
		if (actor->ActorHasTag("Scrap"))
		{
			ABaseObject* scrap = Cast<ABaseObject>(actor);
			if (scrap && scrap->ObjectIsRooted())
			{
				if (!closestRootedScrap)
				{
					closestRootedScrap = scrap;
				}
				else
				{
					float oldDistance = FVector::Dist(GetActorLocation(), closestRootedScrap->GetActorLocation());
					float newDistance = FVector::Dist(GetActorLocation(), scrap->GetActorLocation());
					if (newDistance < oldDistance)
					{
						closestRootedScrap = scrap;
					}
				}
			}
		}
	}
	AttachToActor(closestRootedScrap, FAttachmentTransformRules::KeepWorldTransform);
	m_isAttached = true;
}

void ABaseObject::Cut()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	m_isAttached = false;
}

void ABaseObject::Clean()
{
	// = > Fucntion that switches materials from a dirty to a clean material from the scrapStruct(streach goal at this point)
}

bool ABaseObject::ObjectIsRooted()
{
	return false;
}

