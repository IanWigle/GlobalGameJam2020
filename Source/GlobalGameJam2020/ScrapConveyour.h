// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScrapConveyour.generated.h"

UCLASS()
class GLOBALGAMEJAM2020_API AScrapConveyour : public AActor
{
	GENERATED_BODY()
	
public:	
	AScrapConveyour();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void AScrapConveyour::OnFurnaceOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	FName m_scrapMeshesFolder;
	TSubclassOf<AActor> m_scrapTemplate;
	TArray<class USkeletalMesh*> m_scrapMeshes;
	TArray<AActor*> m_scrapPool;
	TMap<FName, class UBoxComponent*> m_colliders;
	TMap<FName, class UStaticMeshComponent*> m_staticMeshes;
	TMap<FName, class USkeletalMeshComponent*> m_staticMeshes;
};
