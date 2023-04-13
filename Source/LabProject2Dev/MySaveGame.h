// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LABPROJECT2DEV_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMySaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
	FVector Position;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
	int Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
	float Experience;
};
