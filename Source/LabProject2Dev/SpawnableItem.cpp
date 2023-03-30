// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableItem.h"
#include "Item.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpawnableItem::ASpawnableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider); 
	Collider->bHiddenInGame = false;
	Collider->InitSphereRadius(200.f);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnableItem::OnOverlapBegin);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	Item = nullptr;
	Amount = 1;

}

// Called when the game starts or when spawned
void ASpawnableItem::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnableItem::OnOverlapBegin);

	// Creating an item from the BP
	UObject* object = NewObject<UObject>(this, BP_Item);
	Item = Cast<UItem>(object);

	if (Item != nullptr)
	{
		if (Item->Mesh != nullptr)
		{
			StaticMesh->SetStaticMesh(Item->Mesh);
		}
	}
	
}

// Called every frame
void ASpawnableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnableItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("StartOverlap"));
	
}

void ASpawnableItem::Kill()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Destroy();
}

