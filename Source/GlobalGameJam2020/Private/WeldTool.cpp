// Fill out your copyright notice in the Description page of Project Settings.


#include "WeldTool.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

void AWeldTool::Activate()
{
	//raycast forward
	FHitResult OutHitForward;
	FVector Start = GetActorLocation();
	FVector direction = GetActorForwardVector();
	FVector End = direction * 50.0f;
	FCollisionQueryParams CollsionParams;
	CollsionParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(OutHitForward, Start, End, ECC_PhysicsBody, CollsionParams))
	{
		if (OutHitForward.Actor->ActorHasTag("Scrap"))
		{
			//cast hit object as BaseObject
			ABaseObject*  scrap = Cast<ABaseObject>(OutHitForward.Actor);
			if (scrap)
			{
				//Call Weld() on it
				scrap->Weld();
			}
		}
	}
}