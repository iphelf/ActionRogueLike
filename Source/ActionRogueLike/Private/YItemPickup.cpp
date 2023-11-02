// Fill out your copyright notice in the Description page of Project Settings.


#include "YItemPickup.h"

// Sets default values
AYItemPickup::AYItemPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AYItemPickup::OnOverlap);

	RootComponent = MeshComp;

	bIsRecurring = false;
	RecurringPeriod = 3.0f;
}

// Called when the game starts or when spawned
void AYItemPickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AYItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYItemPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (AYCharacter* Character = Cast<AYCharacter>(InstigatorPawn)) {
		if (!IsPickable(Character)) return;
		Pickup(Character);
	}
}

bool AYItemPickup::IsPickable(AYCharacter* Character)
{
	return MeshComp->IsVisible();
}

void AYItemPickup::Pickup(AYCharacter* Character)
{
	if (bIsRecurring) {
		GetWorldTimerManager().SetTimer(RecurringTimerHandle, this, &AYItemPickup::Recur, RecurringPeriod);
		MeshComp->SetVisibility(false);
	}
	else {
		Destroy();
	}
}

void AYItemPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AYCharacter* Character = Cast<AYCharacter>(OtherActor)) {
		if (!IsPickable(Character)) return;
		Pickup(Character);
	}
}

void AYItemPickup::Recur()
{
	MeshComp->SetVisibility(true);
}

