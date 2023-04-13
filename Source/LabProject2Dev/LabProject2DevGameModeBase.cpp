// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabProject2DevGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "PlayerCharacter.h"

ALabProject2DevGameModeBase::ALabProject2DevGameModeBase()
{

}

void ALabProject2DevGameModeBase::SaveGame()
{

	if (UGameplayStatics::DoesSaveGameExist(FString("Save"), 0))
	{
		// Load Game
		USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save"), 0);
		if (!save) return;

		// Cast to mySaveGame
		UMySaveGame* mySave = Cast<UMySaveGame>(save);

		// Get the player
		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!character) return;
		APlayerCharacter* player = Cast<APlayerCharacter>(character);
		if (!player) return;

		// Save values
		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		mySave->Level = player->Level;
		mySave->Experience = player->Experience;

		// Save game
		UGameplayStatics::SaveGameToSlot(mySave, FString("Save"), 0);
	}
	else
	{
		USaveGame* save = UGameplayStatics::CreateSaveGameObject(MySaveGame_BP);
		if (!save) return;
		UMySaveGame* mySave = Cast<UMySaveGame>(save);

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!character) return;

		APlayerCharacter* player = Cast<APlayerCharacter>(character);
		if (!player) return;

		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		mySave->Level = player->Level;
		mySave->Experience = player->Experience;

		UGameplayStatics::SaveGameToSlot(mySave, FString("Save"), 0);
	}

}

void ALabProject2DevGameModeBase::LoadGame()
{
	USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save"), 0);
	if (!save) return;
	UMySaveGame* mySave = Cast<UMySaveGame>(save);

	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!character) return;

	APlayerCharacter* player = Cast<APlayerCharacter>(character);
	if (!player) return;

	player->SetActorLocation(mySave->Position);
	player->SetActorRotation(mySave->Rotation);
	player->Level = mySave->Level;
	player->Experience = mySave->Experience;
}
