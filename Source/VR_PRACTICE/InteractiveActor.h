// InteractiveActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "InteractiveActor.generated.h"
UENUM(BlueprintType)
enum class EStageType : uint8
{
    CavityFighting UMETA(DisplayName = "denture_Teeth"),
    ToothReplacement UMETA(DisplayName = "broke_Teeth"),
    PoseMatching UMETA(DisplayName = "VR PoseMatching"),
    Scaling UMETA(DisplayName = "Scaling")
};

USTRUCT(BlueprintType)
struct FStageInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStageType StageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText TitleText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ContentText;
};


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

    // Hover UI�� �Ѱ� ���� �Լ�
    UFUNCTION(BlueprintCallable)
    void ShowHoverUI(bool bShow);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
    EStageType StageType;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Info")
    TArray<FStageInfo> StageInfos;


protected:
    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* HoverUI;
};