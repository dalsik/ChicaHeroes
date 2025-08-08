// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BacteriaBase.h"
#include "Gemella.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGemellaState : uint8
{
	Approaching,
	Wander
};

UCLASS()
class VR_PRACTICE_API AGemella : public ABacteriaBase
{
	GENERATED_BODY()
	
public:
	AGemella();

protected:
	virtual void OnDeath() override;

	virtual void performBehavior(float DeltaTime) override;

	void GrantShieldsToNearbyBacteria();

	TArray<ABacteriaBase*> BacteriaList;

	UPROPERTY(VisibleAnywhere)
	EGemellaState SubState = EGemellaState::Approaching;

	void HandleAttackState(float DeltaTime);
	void MoveToward(FVector TargetLocation, float DeltaTime);

	FTimerHandle ShieldGrantTimer;
	UPROPERTY(EditAnywhere, Category = "Shield")
	float ShieldGrantInterval = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Shield")
	float ShieldPoint = 100.0f;

	// Gemella.h
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* NiagaraEffect;

	FVector RandomMoveTarget;

	virtual void ChildBegin() override;
};
