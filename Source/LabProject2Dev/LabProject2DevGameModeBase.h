// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabProject2DevGameModeBase.generated.h"

class UMySaveGame;

/**
 * 
 */
UCLASS()
class LABPROJECT2DEV_API ALabProject2DevGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALabProject2DevGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGame")
	TSubclassOf<UMySaveGame> SaveGame_BP;

public:
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
};
