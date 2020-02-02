// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolObject.h"
#include "WeldTool.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMEJAM2020_API AWeldTool : public AToolObject
{
	GENERATED_BODY()
	
public:
	void Activate() override;
};
