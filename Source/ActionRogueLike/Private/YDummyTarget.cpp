// Fill out your copyright notice in the Description page of Project Settings.


#include "YDummyTarget.h"
#include "YAttributeComponent.h"

// Sets default values
AYDummyTarget::AYDummyTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RootComponent = StaticMeshComp;

	AttributeComp = CreateDefaultSubobject<UYAttributeComponent>("Attribute");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AYDummyTarget::OnHealthChanged);
}

// Called when the game starts or when spawned
void AYDummyTarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AYDummyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYDummyTarget::OnHealthChanged(AActor* Cause, UYAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta >= 0.0f) return;
	StaticMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
}

