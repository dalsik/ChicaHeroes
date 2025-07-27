#include "InteractiveActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AInteractiveActor::AInteractiveActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    RootComponent = SkeletalMesh;

    HoverUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HoverUI"));
    HoverUI->SetupAttachment(SkeletalMesh);
    HoverUI->SetVisibility(false);
    //HoverUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //HoverUI->SetGenerateOverlapEvents(false);
}

void AInteractiveActor::BeginPlay()
{
    Super::BeginPlay();

    if (!HoverUI)
    {
        UE_LOG(LogTemp, Warning, TEXT("HoverUI is null"));
        return;
    }

    FString EnumName = StaticEnum<EStageType>()->GetNameStringByValue((int64)StageType);
    HoverUI->Rename(*EnumName);

    // 💡 위젯 내용 초기화
    if (UUserWidget* Widget = Cast<UUserWidget>(HoverUI->GetUserWidgetObject()))
    {
        UImage* ImageWidget = Cast<UImage>(Widget->GetWidgetFromName(TEXT("Image_Icons")));
        UTextBlock* TitleTextWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Title_Text")));
        UTextBlock* ContentTextWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Content_Text")));

        for (const FStageInfo& Info : StageInfos)
        {
            if (Info.StageType == StageType)
            {
                if (ImageWidget && Info.Icon)
                {
                    FSlateBrush Brush;
                    Brush.SetResourceObject(Info.Icon);
                    ImageWidget->SetBrush(Brush);
                    UE_LOG(LogTemp, Warning, TEXT("이미지 icon으로 변경 됨"));
                }

                if (TitleTextWidget)
                {
                    TitleTextWidget->SetText(Info.TitleText);
                    UE_LOG(LogTemp, Warning, TEXT("타이틀 텍스트 변경 됨"));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("타이틀 텍스트 변경 안 됨"));
                }

                if (ContentTextWidget)
                {
                    ContentTextWidget->SetText(Info.ContentText);
                    UE_LOG(LogTemp, Warning, TEXT("컨텐트 텍스트 변경 됨"));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("컨텐트 텍스트 변경 안 됨"));
                }

                break;
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("HoverUI 할당 안 됨"));
    }
}

void AInteractiveActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractiveActor::ShowHoverUI(bool bShow)
{
    if (!HoverUI)
    {
        UE_LOG(LogTemp, Warning, TEXT("HoverUI is null"));
        return;
    }

    HoverUI->SetVisibility(bShow);
    UE_LOG(LogTemp, Warning, TEXT("ShowHoverUI: %s"), bShow ? TEXT("true") : TEXT("false"));
}


