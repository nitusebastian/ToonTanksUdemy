// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
    RootComponent = CapsuleComponent;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);


}

void ABasePawn::HandleDestruction()
{
	if (DeathExplosionFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathExplosionFX, GetActorLocation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySound2D(this, DeathSound);
	}

	if (DestroyCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DestroyCameraShakeClass);
	}
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::PlayDeathExplosion(FVector Location)
{
	if (DeathExplosionFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathExplosionFX, Location);
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookAtTarget) const
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator RotationToTarget = ToTarget.ToOrientationRotator();
	RotationToTarget.Pitch = 0.0f;
		
	FRotator CurrentRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), RotationToTarget, GetWorld()->DeltaTimeSeconds, TurretRotationSpeed);
	CurrentRotation.Pitch = 0.0f;
	CurrentRotation.Roll = 0.0f;
	TurretMesh->SetWorldRotation(CurrentRotation);
}

void ABasePawn::Fire()
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 30.0f, 16, FColor::Red, false, 3.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), SpawnParams);
	Projectile->SetOwner(this);
}

