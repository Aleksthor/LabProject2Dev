// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Mover.h"

AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	int Amount = 5;

	UWorld* World = GetWorld();

	for (int i{}; i < Amount; i++)
	{
		float Angle = FMath::RandRange(0, 360);
		float Radian = Angle * (PI / 180.f);

		FVector Position = FVector(cos(Radian), sin(Radian), 0);
		Position *= 2500.f;

		FVector Velocity = FVector::CrossProduct(Position, FVector(0, 0, -1));
		Velocity.Normalize();
		Velocity *= 1000.f;

		AMover* Mover = Cast<AMover>(World->SpawnActor<AActor>(MoverBP, Position, FRotator::ZeroRotator));
		Mover->Velocity = Velocity;
		Mover->SetUsingGravity(true, this);
	}

	AMover* Sun = Cast<AMover>(World->SpawnActor<AActor>(MoverBP, FVector(0,0,0), FRotator::ZeroRotator));
	Sun->SetUsingGravity(true, this);
	Sun->StandStill = true;
	Sun->Mass = 10.f;
	Sun->SetActorScale3D(FVector(3, 3, 3));
}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AMover*> AMyGameModeBase::GetMovers()
{
	return Movers;
}
