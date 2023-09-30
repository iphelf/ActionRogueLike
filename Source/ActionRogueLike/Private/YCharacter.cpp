// Fill out your copyright notice in the Description page of Project Settings.


#include "YCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YInteractionComponent.h"

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

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AYCharacter::BeginPlay()
{
	Super::BeginPlay();
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

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &AYCharacter::BeginPrimaryAttack);
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

void AYCharacter::BeginPrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(AttackAnimTimerHandle, this, &AYCharacter::DeliverPrimaryAttack, 0.2f);
}

void AYCharacter::DeliverPrimaryAttack()
{
	FVector SpawnLocation{ GetMesh()->GetSocketLocation("PrimaryAttackSource") };
	FRotator ControlRotation{ GetControlRotation() };
	ControlRotation.Pitch = 0.0;
	ControlRotation.Roll = 0.0;
	FTransform SpawnTransform{ ControlRotation, SpawnLocation };
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParameters);
}

void AYCharacter::DoPrimaryInteract()
{
	InteractionComp->DoPrimaryInteract();
}

