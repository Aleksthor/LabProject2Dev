// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyGameModeBase.h"

// Sets default values
AMover::AMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(StaticMesh);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMover::OnComponentBeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AMover::OnComponentEndOverlap);

	Velocity = FVector::ZeroVector;
	Acceleration = FVector::ZeroVector;

	Mass = 1.f;

	OverlappedActors = TArray<AMover*>();

	GravityActive = false;
	StandStill = false;
	GameMode = nullptr;
}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Did not find the correct gamemode"));
	}

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMover::OnComponentBeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AMover::OnComponentEndOverlap);
	//AddForce(FVector(-3.f, 0, 0));
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GravityActive && GameMode)
	{
		TArray<AMover*> Movers = GameMode->GetMovers();
		for (int i{}; i < Movers.Num(); i++)
		{
			if (Movers[i] != this)
			{
				Movers[i]->Attract(this);
			}
		}
	}

	if (!FMath::IsNearlyZero(Acceleration.X))
	{
		Velocity.X += Acceleration.X;
	}
	if (!FMath::IsNearlyZero(Acceleration.Y))
	{
		Velocity.Y += Acceleration.Y;
	}
	if (!FMath::IsNearlyZero(Acceleration.Z))
	{
		Velocity.Z += Acceleration.Z;
	}
	Acceleration = FVector::ZeroVector;


	// Add Velocity to out position
	if (!UKismetMathLibrary::Vector_IsNearlyZero(Velocity) && !StandStill)
	{
		SetActorLocation(GetActorLocation() + (Velocity * DeltaTime));
	}


}

void AMover::AddForce(FVector force)
{
	if (StandStill)
	{
		return;
	}


	force *= 100.f;
	if (!FMath::IsNearlyZero(Mass))
	{
		Acceleration += force / Mass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to divide by 0"));
		Acceleration += force;
	}
}

void AMover::Attract(AMover* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Attracting"));

	float GravitationalConstant = 100000.f;
	FVector Direction = GetActorLocation() - Other->GetActorLocation();
	
	float DistanceSq = Direction.Length();
	DistanceSq *= DistanceSq;

	DistanceSq = FMath::Clamp(DistanceSq, 10000.f, 1000000000.f);

	FVector Force = Direction;
	Force.Normalize();

	float Strength = (Mass * Other->Mass);
	Strength /= DistanceSq;
	Strength *= GravitationalConstant;

	Force *= Strength;
	Other->AddForce(Force);
}

void AMover::SetUsingGravity(bool input)
{
	if (input && GameMode)
	{
		if (!GameMode->Movers.Contains(this))
			GameMode->Movers.Add(this);		
	}
	GravityActive = input;
}

void AMover::SetUsingGravity(bool input, AMyGameModeBase* gamemode)
{
	GameMode = gamemode;
	SetUsingGravity(input);
}

void AMover::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping"));
	if (OtherActor->IsA<AMover>() && !OverlappedActors.Contains(Cast<AMover>(OtherActor)))
	{
		AMover* OtherMover = Cast<AMover>(OtherActor);		

		FVector v = Velocity;
		FVector w = OtherMover->Velocity;
		float m1 = Mass;
		float m2 = OtherMover->Mass;

		Velocity = (((m1 - m2) / (m1 + m2)) * v) + (((2 * m2) / (m1 + m2)) * w);
		OtherMover->Velocity = (((2 * m1) / (m1 + m2)) * v) + (((m2 - m1) / (m1 + m2)) * w);

		OverlappedActors.Add(OtherMover);
		OtherMover->OverlappedActors.Add(this);		 
	}
}

void AMover::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedActors.Contains(Cast<AMover>(OtherActor)))
	{
		OverlappedActors.Remove(Cast<AMover>(OtherActor));
	}
}

