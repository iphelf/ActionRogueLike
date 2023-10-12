// Fill out your copyright notice in the Description page of Project Settings.


#include "YMagicProjectile.h"
#include "YAttributeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AYMagicProjectile::AYMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AYMagicProjectile::OnActorOverlap);
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

void AYMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	UYAttributeComponent* AttributeComp = Cast<UYAttributeComponent>(OtherActor->GetComponentByClass(UYAttributeComponent::StaticClass()));
	if (!AttributeComp) return;
	AttributeComp->ChangeHealth(-20.0f);
	Destroy();
}

