// Fill out your copyright notice in the Description page of Project Settings.


#include "YMagicProjectile.h"
#include "YAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AYMagicProjectile::AYMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlightSoundComp = CreateDefaultSubobject<UAudioComponent>("Flight Sound");
	FlightSoundComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentHit.AddDynamic(this, &AYMagicProjectile::OnActorHit);
}

// Called when the game starts or when spawned
void AYMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
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

	if (UYAttributeComponent* AttributeComp
		= Cast<UYAttributeComponent>(OtherActor->GetComponentByClass(UYAttributeComponent::StaticClass()))) {
		AttributeComp->ChangeHealth(-50.0f);
	}

	FVector HitLocation{ GetActorLocation() };

	// 为何会被不可见平面遮挡？
	DrawDebugSphere(GetWorld(), HitLocation, 10.0f, 12, FColor{ 0xFFu, 0x8Du, 0x7Eu }, false, 1.0f);

	if (ensure(HitEffectTemplate)) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectTemplate, HitLocation, GetActorRotation());
	}
	if (ensure(ImpactSound)) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitLocation);
	}

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), HitCameraShake, HitLocation, 0.0f, 1000.0f);

	Destroy();
}

