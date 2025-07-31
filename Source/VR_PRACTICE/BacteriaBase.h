#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "BacteriaBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerAttacked, ABacteriaBase*, Attacker);

UENUM(BlueprintType)
enum class EBacteriaState : uint8
{
    Bounced,
    CustomBehavior
};

UCLASS()
class VR_PRACTICE_API ABacteriaBase : public AActor
{
    GENERATED_BODY()

public:
    ABacteriaBase();

    virtual void Tick(float DeltaTime) override;
    virtual void OnDeath() {};

    UFUNCTION(BlueprintCallable, Category = "Bacteria")
    virtual void TakeDamageBac(float Damage);

    UFUNCTION(BlueprintCallable, Category = "Bacteria")
    virtual void HitBac(AActor* Actor);

    bool bShieldAnim = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    bool PistolOverlap = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    bool Shield = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    bool bShieldHitRecently = false;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerAttacked OnPlayerAttacked;

    // 공격력
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackPower = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bacteria")
    UStaticMeshComponent* ShieldMesh;

    float getHealth();

    void Init(APawn* InPlayer, float UptoDownRate, float DownToUpRate, float Force, float XRangeMin, float XRangeMax, float YRangeMin, float YRangeMax);

protected:
    EBacteriaState CurrentState = EBacteriaState::Bounced;

    virtual void BeginPlay() override;
    virtual void Destroyed() override;

    virtual void performBehavior(float DeltaTime);

    void LaunchBounce();

    // 체력
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float Health;

    // 이동 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MoveSpeed;

    // 최대 이동 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float MaxSpeed;
    float IncSpeed = 5.f;

    // 회전 속도
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float TrackingSpeed = 1.2f;

    // 공격 범위
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    float AttackRange = 200.f;

    // 메시 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    UStaticMeshComponent* MeshComponent;

    // 플레이어 참조
    UPROPERTY(EditAnywhere, Category = "Bacteria")
    APawn* PlayerPawn;

    UPROPERTY(VisibleAnywhere, Category = "Bacteria")
    float Distance;

    // 플레이어 참조
    UPROPERTY()
    UCameraComponent* CameraComp;

    // 플레이어 위치 캐시
    FVector PlayerLocation;

    UPROPERTY(EditAnywhere, Category = "RotateSpeed")
    float SpinSpeedX = 30.f;

    UPROPERTY(EditAnywhere, Category = "RotateSpeed")
    float SpinSpeedY = 45.f;

    UPROPERTY(EditAnywhere, Category = "RotateSpeed")
    float SpinSpeedZ = 60.f;

    virtual void ChildBegin() {};

    float UptoDownRate = 0.f;
    float DownToUpRate = 0.f;
    float Force = 0.f;
    float XRangeMin = 0.f;
    float XRangeMax = 0.f;
    float YRangeMin = 0.f;
    float YRangeMax = 0.f;
};
