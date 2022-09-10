// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float InitialSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FX", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* SmokeTrailEmitter;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
public:
	
	
	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
