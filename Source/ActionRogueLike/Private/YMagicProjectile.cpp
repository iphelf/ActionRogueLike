// Fill out your copyright notice in the Description page of Project Settings.


#include "YMagicProjectile.h"
#include "YAttributeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AYMagicProjectile::AYMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->OnComponentHit.AddDynamic(this, &AYMagicProjectile::OnActorHit);
}

// Called when the game starts or when spawned
void AYMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AYMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) return;
	if (OtherActor == GetInstigator()) return;
	UYAttributeComponent* AttributeComp = Cast<UYAttributeComponent>(OtherActor->GetComponentByClass(UYAttributeComponent::StaticClass()));
	if (!AttributeComp) return;
	AttributeComp->ChangeHealth(-20.0f);
	Destroy();
}

