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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
	FVector Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
	FRotator Rotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
	int Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
	float Experience;
};
