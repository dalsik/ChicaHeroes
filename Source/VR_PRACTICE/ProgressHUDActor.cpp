// Fill out your copyright notice in the Description page of Project Settings.

#include "ProgressHUDActor.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AProgressHUDActor::AProgressHUDActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AProgressHUDActor::BeginPlay()
{
	Super::BeginPlay();
	
}



void AProgressHUDActor::UpdateProgressBar(float NewProgress)
{
	if (ProgressBar_Progress)
	{
		// 진행도를 0~100 → 0~1로 정규화
		ProgressBar_Progress->SetPercent(FMath::Clamp(NewProgress / 100.f, 0.f, 1.f));
	}
}