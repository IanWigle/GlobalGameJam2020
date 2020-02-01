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
		void OnFurnaceOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void AddBaseObjectToPool();
	void DropBaseObjectFromPool();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditEnywhere);
	int m_poolSize;
	UPROPERTY(EditEnywhere);
	float m_dropDelay;
	UPROPERTY(EditEnywhere);
	FName m_scrapMeshesFolder;
	TArray<class USkeletalMesh*> m_scrapMeshes;
	TSubclassOf<class ABaseObject> m_scrapTemplate;
	UPROPERTY(EditEnywhere);
	TArray<class ABaseObject*> m_scrapPool;
	UPROPERTY(EditEnywhere);
	TMap<FName, class UBoxComponent*> m_colliders;
	UPROPERTY(EditEnywhere);
	TMap<FName, class USkeletalMeshComponent*> m_Meshes;
	FTimerHandle m_scrapSpawnTimer;
};
