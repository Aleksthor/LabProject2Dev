// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UImage;

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Common			UMETA(DeplayName = "Common"),
	EIR_UnCommon		UMETA(DeplayName = "UnCommon"),
	EIR_Rare			UMETA(DeplayName = "Rare"),
	EIR_Epic			UMETA(DeplayName = "Epic"),
	EIR_Legendary		UMETA(DeplayName = "Legendary"),

	EIR_MAX				UMETA(DeplayName = "DefaultMAX")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LABPROJECT2DEV_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	UStaticMesh* Mesh{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	UTexture2D* Image{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	float Weight;
};
