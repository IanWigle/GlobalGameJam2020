// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolObject.h"

void AToolObject::Activate()
{
	Tags.Remove("Scrap");
	Tags.Add("Tool");
}