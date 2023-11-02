// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YProjectile.h"
#include "YMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AYMagicProjectile : public AYProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AYMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//UFUNCTION()
	//void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<UParticleSystem> HitEffectTemplate;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UAudioComponent* FlightSoundComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<UCameraShakeBase> HitCameraShake;
};

