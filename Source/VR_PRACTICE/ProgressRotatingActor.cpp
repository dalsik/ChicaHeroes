#include "ProgressRotatingActor.h"

// 생성자
AProgressRotatingActor::AProgressRotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// BeginPlay: 자동으로 회전 메시 할당
void AProgressRotatingActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> ChildrenComp;
	GetRootComponent()->GetChildrenComponents(true, ChildrenComp);

	for (USceneComponent* Comp : ChildrenComp)
	{
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Comp))
		{
			if (Mesh->GetName().Contains(TEXT("Rotate_Tool1")))
			{
				RotateComp = Mesh;
				InitialRotation = RotateComp->GetRelativeRotation();
				break;
			}
		}
	}
}

// Tick: 진행도 기반 회전 로직
void AProgressRotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!RotateComp) return;

	FRotator CurrentRot = RotateComp->GetRelativeRotation();
	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRotation, DeltaTime, RotationInterpSpeed);

	RotateComp->SetRelativeRotation(NewRot);
}

// 진행도 수신 함수
void AProgressRotatingActor::OnProgressUpdate_Rot(float NewProgress)
{
	CurrentProgress = FMath::Clamp(NewProgress, 0.f, 100.f);


	const float NormalizedProgress = CurrentProgress / 100.f;
	const float SineValue = FMath::Sin(NormalizedProgress * PI);

	TargetRotation = InitialRotation + MaxRotationOffset * SineValue;
}

