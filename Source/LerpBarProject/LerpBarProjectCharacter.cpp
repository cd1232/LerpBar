// This Include
#include "LerpBarProjectCharacter.h"

// Engine Includes
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/InputSettings.h"

// Local Includes

//DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ALerpBarProjectCharacter::ALerpBarProjectCharacter()
	:Super()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void ALerpBarProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set here in case blueprint overrides Max Health
	CurrentHealth = MaxHealth;

	OnPlayerStatsInit.Broadcast();
}

void ALerpBarProjectCharacter::DamageMe(const float DamageToDeal)
{
	CurrentHealth -= DamageToDeal;
	float ActualDamageDealt = DamageToDeal;
	if (CurrentHealth <= 0)
	{
		ActualDamageDealt = DamageToDeal + CurrentHealth;
		CurrentHealth = 0;
		OnPlayerDeath.Broadcast();
	}
	
	OnPlayerDamaged.Broadcast(ActualDamageDealt);
}

void ALerpBarProjectCharacter::HealMe(const float AmountToHeal)
{
	CurrentHealth += AmountToHeal;
	float ActualAmountHealed = AmountToHeal;
	if (CurrentHealth > MaxHealth)
	{
		ActualAmountHealed = AmountToHeal - (CurrentHealth - MaxHealth);
		CurrentHealth = MaxHealth;
	}

	OnPlayerHealed.Broadcast(AmountToHeal);
}

float ALerpBarProjectCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void ALerpBarProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up game-play key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ALerpBarProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALerpBarProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turn-rate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALerpBarProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALerpBarProjectCharacter::LookUpAtRate);
}

void ALerpBarProjectCharacter::MoveForward(const float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALerpBarProjectCharacter::MoveRight(const float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALerpBarProjectCharacter::TurnAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALerpBarProjectCharacter::LookUpAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
