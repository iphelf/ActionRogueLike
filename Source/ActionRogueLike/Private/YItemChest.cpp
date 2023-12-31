// Fill out your copyright notice in the Description page of Project Settings.


#include "YItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AYItemChest::AYItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("Lid Mesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.0;
}

// Called when the game starts or when spawned
void AYItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AYItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator{ TargetPitch, 0.0, 0.0 });
}

