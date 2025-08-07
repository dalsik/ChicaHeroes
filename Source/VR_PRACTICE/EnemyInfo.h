// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BacteriaBase.h"
#include "EnemyInfo.generated.h"

USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase {
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<ABacteriaBase> Enemy1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    int32 Enemy1Count;

    // Enemy2, Enemy3 등도 여기에 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<ABacteriaBase> Enemy2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    int32 Enemy2Count;
};