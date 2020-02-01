// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScrapConveyour.generated.h"
//

USTRUCT()
struct FScrapMeshData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class USkeletalMesh* m_mesh;
	UPROPERTY(EditAnywhere)
		class UPhysicsAsset* m_meshPhysics;
};

UCLASS()
class GLOBALGAMEJAM2020_API AScrapConveyour : public AActor
{
	GENERATED_BODY()
	
public:	
	AScrapConveyour();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnFurnaceOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnConveyourOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnConveyourOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void AddBaseObjectToPool(class ABaseObject* a_scrap);
	void DropBaseObjectFromPool();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int m_poolSize;
	UPROPERTY(EditAnywhere)
	float m_dropDelay;
	UPROPERTY(EditAnywhere)
	float m_conveyourSpeed;
	UPROPERTY(EditAnywhere)
	FName m_scrapMeshesFolder;
	UPROPERTY(EditAnywhere)
	TArray<FScrapMeshData> m_scrapMeshes;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseObject> m_scrapTemplate;
	UPROPERTY(EditAnywhere)
	TArray<class ABaseObject*> m_scrapPool;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* m_furnaceCollider;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* m_dropCollider;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* m_conveyourCollider;

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* m_furnaceMesh;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* m_dropMesh;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* m_conveyourMesh;

	FTimerHandle m_scrapSpawnTimer;

	TArray<class ABaseObject*> m_scrapOnConveyour;
	TArray<class ABaseObject*> m_scrapOnConveyourToRemove;
};
