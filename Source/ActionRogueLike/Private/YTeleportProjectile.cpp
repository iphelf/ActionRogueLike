// Fill out your copyright notice in the Description page of Project Settings.


#include "YTeleportProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AYTeleportProjectile::AYTeleportProjectile()
{
	ExplodeEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("Explode Effect");
	ExplodeEffectComp->bAutoActivate = false;
	ExplodeEffectComp->SetupAttachment(SphereComp);

	TravelTime = 0.3f;
	ExplodeTime = 0.2f;
}

void AYTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TravelTimerHandle, this, &AYTeleportProjectile::Explode, TravelTime);
	SphereComp->OnComponentHit.AddDynamic(this, &AYTeleportProjectile::OnHit);
}

void AYTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AYTeleportProjectile::Explode()
{
	GetWorldTimerManager().ClearTimer(TravelTimerHandle);
	MovementComp->StopMovementImmediately();
	EffectComp->Deactivate();

	ExplodeEffectComp->Activate();
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &AYTeleportProjectile::Teleport, ExplodeTime);
}

void AYTeleportProjectile::Teleport()
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	ExplodeEffectComp->Deactivate();

	APawn* Character{ GetInstigator() };
	if (Character) {
		Character->SetActorLocation(GetActorLocation(), true);
	}

	Destroy();
}

