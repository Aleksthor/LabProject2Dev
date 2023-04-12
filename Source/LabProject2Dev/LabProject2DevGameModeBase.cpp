// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabProject2DevGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "PlayerCharacter.h"

ALabProject2DevGameModeBase::ALabProject2DevGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALabProject2DevGameModeBase::BeginPlay()
{
	Super::BeginPlay();
		
}

void ALabProject2DevGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabProject2DevGameModeBase::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(FString("Save1"), 0)) // Save Name, UserIndex
	{
		USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save1"), 0);
		UMySaveGame* mySave = Cast<UMySaveGame>(save);

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character == nullptr) return;

		APlayerCharacter* player = Cast<APlayerCharacter>(character);
		if (player == nullptr) return;

		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		mySave->Level = player->Level;
		mySave->Experience = player->ExperiencePoints;

		UGameplayStatics::SaveGameToSlot(mySave, FString("Save1"), 0);
	}
	else
	{
		USaveGame* save = UGameplayStatics::CreateSaveGameObject(SaveGame_BP);
		UMySaveGame* mySave = Cast<UMySaveGame>(save);

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character == nullptr) return;

		APlayerCharacter* player = Cast<APlayerCharacter>(character);
		if (player == nullptr) return;

		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		mySave->Level = player->Level;
		mySave->Experience = player->ExperiencePoints;

		UGameplayStatics::SaveGameToSlot(mySave, FString("Save1"), 0);
	}
}

void ALabProject2DevGameModeBase::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(FString("Save1"), 0)) return;
	
	USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save1"), 0);
	UMySaveGame* mySave = Cast<UMySaveGame>(save);

	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (character == nullptr) return;

	APlayerCharacter* player = Cast<APlayerCharacter>(character);
	if (player == nullptr) return;

	player->SetActorLocation(mySave->Position);
	player->SetActorRotation(mySave->Rotation);
	player->Level = mySave->Level;
	player->ExperiencePoints = mySave->Experience;
}
