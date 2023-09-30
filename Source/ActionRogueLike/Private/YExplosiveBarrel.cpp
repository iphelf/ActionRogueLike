// Fill out your copyright notice in the Description page of Project Settings.


#include "YExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "YMagicProjectile.h"

// Sets default values
AYExplosiveBarrel::AYExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->Radius = 700.0f;
	RadialForceComp->ImpulseStrength = 2'000.0f;
	RadialForceComp->bImpulseVelChange = true;

	StaticMeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AYExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &AYExplosiveBarrel::OnComponentHit);
}

// Called every frame
void AYExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AYMagicProjectile>(OtherActor)) {
		RadialForceComp->FireImpulse();
		UE_LOG(LogTemp, Display, TEXT("The explosive barrel got hit by projectile. BOOM!"));
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("The explosive barrel got hit by projectile. BOOM!"));
		}
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("The explosive barrel got hit but not by projectile."));
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Silver, TEXT("The explosive barrel got hit but not by projectile."));
		}
	}
}

