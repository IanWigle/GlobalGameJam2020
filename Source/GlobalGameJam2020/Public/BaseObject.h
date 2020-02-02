// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

UCLASS()
class GLOBALGAMEJAM2020_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObject();
	void ReturnToPool(class AScrapConveyour* a_Conveyour);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	FTimerHandle FadeTimer;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* m_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_InStand = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_BeingHeld = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool m_PrintFadeTimeRemaining = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_TimeToFade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AScrapConveyour* m_Conveyour;

	//FScrapMeshData* m_currentScrapMeshData;

	UFUNCTION(BlueprintCallable)
		void DisableObject();

	UFUNCTION(BlueprintCallable)
		void EnableObject();

	UFUNCTION(BlueprintCallable)
		bool IsFading();

	UFUNCTION(BlueprintCallable)
		float FadeTimeRemaining();

	UFUNCTION(BlueprintCallable)
		void StopFade();

	void Weld();
	void Cut();
	void Clean();
};
