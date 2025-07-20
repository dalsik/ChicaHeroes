// InteractiveActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Image.h"

UENUM(BlueprintType)
enum class EStageType : uint8
{
    CavityFighting UMETA(DisplayName = "denture_Teeth"),
    ToothReplacement UMETA(DisplayName = "broke_Teeth"),
    PoseMatching UMETA(DisplayName = "VR PoseMatching"),
    Scaling UMETA(DisplayName = "Scaling")
};

#include "InteractiveActor.generated.h"

class USkeletalMeshComponent;
class UWidgetComponent;
class UImage;

UCLASS()
class VR_PRACTICE_API AInteractiveActor : public AActor
{
    GENERATED_BODY()

public:
    AInteractiveActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Hover UI를 켜고 끄는 함수
    UFUNCTION(BlueprintCallable)
    void ShowHoverUI(bool bShow);

    // 트리거 상호작용 함수
    UFUNCTION(BlueprintCallable)
    void PerformInteraction();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
    EStageType StageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "image_name")
    FString image_name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "image_name")
    TArray<UTexture2D*> Icons;

       
protected:
    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* HoverUI;
};
