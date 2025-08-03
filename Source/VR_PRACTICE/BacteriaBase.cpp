// Fill out your copyright notice in the Description page of Project Settings.


#include "BacteriaBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "StageManager.h"

ABacteriaBase::ABacteriaBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1); // "Bacteria" 채널

    MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

    MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // 서로 무시

    MeshComponent->SetEnableGravity(false);
    MeshComponent->SetSimulatePhysics(true);

    ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
    ShieldMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShieldAsset(TEXT("/Game/Niagara/Shield/IcoSphere.IcoSphere")); // 실제 경로로!
    if (ShieldAsset.Succeeded())
    {
        ShieldMesh->SetStaticMesh(ShieldAsset.Object);
    }

    DeathEffect = LoadObject<UNiagaraSystem>(
        nullptr,
        TEXT("/Game/Niagara/NS_Cloud.NS_Cloud")
    );

    // 초기 체력
    Health = 100.0f;
}

float ABacteriaBase::getHealth()
{
    return Health;
}

void ABacteriaBase::BeginPlay()
{
    Super::BeginPlay();

    AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
    if (StageManager)
    {
        StageManager->RegisterBacteria(this);
    }
    // 머티리얼/스케일/위치/투명도 등 추가 세팅
    ShieldMesh->SetVisibility(Shield); // 처음엔 안 보이게
    ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 충돌 X
    ShieldMesh->SetWorldScale3D(GetActorScale3D() * 2.f); // 본체보다 조금 크게

    LaunchBounce();
    ChildBegin();
}

void ABacteriaBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (CurrentState == EBacteriaState::CustomBehavior) {
        performBehavior(DeltaTime);
        if (PistolOverlap)
        {
            GetWorld()->GetTimerManager().SetTimer(
                SpawnTimerHandle, this,
                &ABacteriaBase::TakeDamageBacPistol,
                0.1f, true
            );
            PistolOverlap = false;
        }
    }
}

void ABacteriaBase::ClearTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}

void ABacteriaBase::HitBac(AActor* Actor)
{
    float HitDamage = 0.f;
    if (Actor->Tags.Contains("Bullet0")) {
        HitDamage = 40.f;
        Actor->Destroy();
    }
    else if (Actor->Tags.Contains("Bullet1")) HitDamage = 30.f;
    else if (Actor->Tags.Contains("Bullet2")) {
        HitDamage = 40.f;
        Actor->Destroy();
    }
    else if (Actor->ActorHasTag("Pistol")) {
        PistolOverlap = true;
    }
    else return;
    
    if (bShieldHitRecently) return;
    TakeDamageBac(HitDamage);
}

void ABacteriaBase::TakeDamageBac(float HitDamage)
{
    if (bShieldHitRecently) return;
    float TempDam = ShieldHP - HitDamage;
    if (TempDam > 0.f) {
        ShieldHP = TempDam;
        if (TempDam <= 0.f) {
            bShieldHitRecently = true;
            ShieldMesh->SetHiddenInGame(true);
            GetWorldTimerManager().SetTimerForNextTick([this]()
                {
                    bShieldHitRecently = false;
                });
        }
    }
    else {
        Shield = false;
        Health -= TempDam;
        UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
        if (Health <= 0.f) {
            OnDeath();
            if (DeathEffect) {
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    DeathEffect,
                    GetActorLocation()
                );
            }
            Destroy();
        }
    }
}

void ABacteriaBase::TakeDamageBacPistol()
{
    TakeDamageBac(10.f);
}

void ABacteriaBase::Destroyed()
{
    Super::Destroyed();

    AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
    if (StageManager)
    {
        StageManager->UnregisterBacteria(this);
    }
}

void ABacteriaBase::performBehavior(float DeltaTime)
{
    if (CameraComp) {
        PlayerLocation = CameraComp->GetComponentLocation();
    }
}

void ABacteriaBase::LaunchBounce()
{
    float X = FMath::FRandRange(XRangeMin, XRangeMax);
    float Y = FMath::FRandRange(YRangeMin, YRangeMax);

    FVector BounceDir;
    if (GetActorLocation().Z > 0.0f) {
        BounceDir = FVector(X, Y, UptoDownRate);
        SetActorRotation(FRotator(-180.f, 0, 0));
    }
    else {
        BounceDir = FVector(X, Y, DownToUpRate);
    }
    MeshComponent->AddImpulse(BounceDir * Force * Impulse, NAME_None, true);

    GetWorldTimerManager().SetTimerForNextTick([this]()
        {
            CurrentState = EBacteriaState::CustomBehavior;
        });
}

void ABacteriaBase::Init(APawn* InPlayer, float InUptoDownRate, float InDownToUpRate, float InForce, float InXRangeMin, float InXRangeMax, float InYRangeMin, float InYRangeMax)
{
    PlayerPawn = InPlayer;
    if (PlayerPawn)
    {
        CameraComp = PlayerPawn->FindComponentByClass<UCameraComponent>();
    }

    this->UptoDownRate = InUptoDownRate;
    this->DownToUpRate = InDownToUpRate;
    this->Force = InForce;
    this->XRangeMin = InXRangeMin;
    this->XRangeMax = InXRangeMax;
    this->YRangeMin = InYRangeMin;
    this->YRangeMax = InYRangeMax;
}
