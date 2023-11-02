// Fill out your copyright notice in the Description page of Project Settings.


#include "YCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YInteractionComponent.h"
#include "YAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AYCharacter::AYCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UYInteractionComponent>("Interaction");

	AttributeComp = CreateDefaultSubobject<UYAttributeComponent>("Attribute");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	AimRange = 5e4f;
}

void AYCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AYCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void AYCharacter::BeginPlay()
{
	Super::BeginPlay();
	ensure(MagicProjectileClass);
	ensure(BlackholeProjectileClass);
	ensure(TeleportProjectileClass);
}

// Called every frame
void AYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AYCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AYCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction<SkillDelegate>("PrimaryAttack", EInputEvent::IE_Pressed, this, &AYCharacter::BeginAttack, 0);
	PlayerInputComponent->BindAction<SkillDelegate>("Skill1", EInputEvent::IE_Pressed, this, &AYCharacter::BeginAttack, 1);
	PlayerInputComponent->BindAction<SkillDelegate>("Skill2", EInputEvent::IE_Pressed, this, &AYCharacter::BeginAttack, 2);

	PlayerInputComponent->BindAction("PrimaryInteract", EInputEvent::IE_Pressed, this, &AYCharacter::DoPrimaryInteract);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AYCharacter::MoveForward(float Value)
{
	FRotator ControlRot{ GetControlRotation() };
	ControlRot.Roll = 0.0;
	ControlRot.Pitch = 0.0;
	AddMovementInput(ControlRot.Vector(), Value);
}

void AYCharacter::MoveRight(float Value)
{
	const FVector RightVector{ FRotationMatrix{GetControlRotation()}.GetScaledAxis(EAxis::Y) };
	AddMovementInput(RightVector, Value);
}

void AYCharacter::BeginAttack(int SkillId) {
	if (ensure(AttackAnim)) {
		PlayAnimMontage(AttackAnim);
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this, SkillId] { DeliverAttack(SkillId); });
		GetWorldTimerManager().SetTimer(AttackAnimTimerHandle, TimerDelegate, 0.2f, false);
	}
}

void AYCharacter::DeliverAttack(int SkillId)
{
	if (!ensure(0 <= SkillId && SkillId <= 2)) return;
	FVector SpawnLocation{ GetMesh()->GetSocketLocation("AttackSource") };
	FRotator Aim;
	{
		FVector AimStart{ CameraComp->GetComponentLocation() };
		FVector AimEnd{ AimStart + GetControlRotation().Vector() * AimRange };
		FHitResult HitResult;
		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, AimStart, AimEnd, QueryParams)) {
			AimEnd = HitResult.ImpactPoint;
			DrawDebugString(GetWorld(), AimEnd, FString::Printf(TEXT("Aiming at %s"), *AimEnd.ToString()), nullptr, FColor::Red, 2.0f);
		}
		Aim = FRotationMatrix::MakeFromX(AimEnd - SpawnLocation).Rotator();
	}
	FTransform SpawnTransform{ Aim, SpawnLocation };
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	switch (SkillId) {
	case 0:
		GetWorld()->SpawnActor<AActor>(MagicProjectileClass, SpawnTransform, SpawnParameters);
		break;
	case 1:
		GetWorld()->SpawnActor<AActor>(BlackholeProjectileClass, SpawnTransform, SpawnParameters);
		break;
	case 2:
		GetWorld()->SpawnActor<AActor>(TeleportProjectileClass, SpawnTransform, SpawnParameters);
		break;
	default:
		return;
	}
	if (ensure(SpellCastingEffect))
		UGameplayStatics::SpawnEmitterAttached(SpellCastingEffect, GetMesh(), "AttackSource");
}

void AYCharacter::DoPrimaryInteract()
{
	InteractionComp->DoPrimaryInteract();
}

void AYCharacter::OnHealthChanged(AActor* Cause, UYAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f) {
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
	if (NewHealth <= 0.0f && 0.0f < NewHealth - Delta) {
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}

