#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LerpBarProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, float, AmountChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStatsInit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS(config=Game)
class ALerpBarProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALerpBarProjectCharacter();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DamageMe(float DamageToDeal);

	UFUNCTION(BlueprintCallable)
	void HealMe(float AmountToHeal);

	UFUNCTION(BlueprintCallable, Category = Stats)
	float GetCurrentHealth() const;

protected:	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles stafing movement, left and right */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

public:
	UPROPERTY(BlueprintAssignable)
	FOnStatChanged OnPlayerDamaged;

	UPROPERTY(BlueprintAssignable)
	FOnStatChanged OnPlayerHealed;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeath OnPlayerDeath;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatsInit OnPlayerStatsInit;

protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate = 45.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate = 45.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float MaxHealth = 100.0f;

private:
	float CurrentHealth = 0.0f;
};

