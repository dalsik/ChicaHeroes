// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "Components/ProgressBar.h"
#include "ProgressHUDActor.generated.h"

UCLASS()
class VR_PRACTICE_API AProgressHUDActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressHUDActor();

	UFUNCTION(BlueprintCallable)
	void UpdateProgressBar(float NewProgress);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar_Progress;

private:

public:	
};
