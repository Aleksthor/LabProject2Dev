// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabProject2DevGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LABPROJECT2DEV_API ALabProject2DevGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALabProject2DevGameModeBase();

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGame")
	TSubclassOf<class UMySaveGame> MySaveGame_BP;
};
