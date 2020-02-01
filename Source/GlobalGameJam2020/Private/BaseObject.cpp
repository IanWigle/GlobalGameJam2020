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

	//if (m_BeingHeld == false && m_InStand == false)
	//{
	//	if (IsFading() == false)
	//	{
	//		GetWorld()->GetTimerManager().SetTimer(FadeTimer, this, &ABaseObject::ReturnToPool, m_TimeToFade,false);
	//	}
	//}

	//if (IsFading() && m_PrintFadeTimeRemaining)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Purple, FString::Printf(TEXT("%f"),FadeTimeRemaining()));
	//}

	
}

void ABaseObject::DisableObject()
{
	m_Mesh->SetSimulatePhysics(false);
	m_Mesh->SetGenerateOverlapEvents(false);
	m_Mesh->SetHiddenInGame(true, true);
}

void ABaseObject::EnableObject()
{
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

