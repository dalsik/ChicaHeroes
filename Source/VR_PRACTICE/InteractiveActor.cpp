// InteractiveActor.cpp

#include "InteractiveActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

AInteractiveActor::AInteractiveActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    RootComponent = SkeletalMesh;

    HoverUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HoverUI"));
    HoverUI->SetupAttachment(SkeletalMesh);
    HoverUI->SetVisibility(false);
}

void AInteractiveActor::BeginPlay()
{
    Super::BeginPlay();

    FString EnumName = StaticEnum<EStageType>()->GetNameStringByValue((int64)StageType);
    // Widget Component 이름 변경하기
    if (image_name == EnumName && HoverUI)
    {
        HoverUI->Rename(*EnumName);

        UE_LOG(LogTemp, Warning, TEXT("HoverUI : %s"), *EnumName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Don't Changed"));
    }

    //위젯 컴포넌트 이름을 Icons 이름과 비교

    FString HoverName = HoverUI->GetName();
    
    if (UUserWidget* Widget = Cast<UUserWidget>(HoverUI->GetUserWidgetObject()))
    {
        if (UImage* ImageWidget = Cast<UImage>(Widget->GetWidgetFromName(TEXT("Image_Icons"))))
        {
            for (UTexture2D* IconTex : Icons)
            {
                if (!IconTex) continue;

                FString TexName = IconTex->GetName();
                
                if (TexName.Equals(HoverName, ESearchCase::IgnoreCase))
                {
                    FSlateBrush Brush;
                    Brush.SetResourceObject(IconTex);
                    ImageWidget->SetBrush(Brush);

                    UE_LOG(LogTemp, Warning, TEXT("Set Image : %s"), *TexName);
                    break;
                }
            }
        }
        else UE_LOG(LogTemp, Warning, TEXT("ImageWidget!~!~!~"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("UserWidget!!~!~!"));
}

void AInteractiveActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AInteractiveActor::ShowHoverUI(bool bShow)
{
    if (HoverUI)
    {
        HoverUI->SetVisibility(bShow);
    }
}

void AInteractiveActor::PerformInteraction()
{
    UE_LOG(LogTemp, Log, TEXT("Performing Interaction!"));
    // 원하는 행동 구현
}
