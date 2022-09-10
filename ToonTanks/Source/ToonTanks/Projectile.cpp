// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AProjectile::OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, UE::Math::TVector<double> NormalImpulse, const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Actor hit = %s"), *OtherActor->GetName())

	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr) return;

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, MyOwnerInstigator, this, DamageTypeClass);
		

		if (ExplosionFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionFX, HitResult.Location, GetActorRotation());
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySound2D(this, HitSound);
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

		Destroy();
	}
	
}

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	

    ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
    ProjectileComponent->InitialSpeed = InitialSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;

	SmokeTrailEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Emitter"));
	SmokeTrailEmitter->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

