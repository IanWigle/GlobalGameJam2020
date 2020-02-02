// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObject.h"
#include "ToolObject.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMEJAM2020_API AToolObject : public ABaseObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void Activate();
};
