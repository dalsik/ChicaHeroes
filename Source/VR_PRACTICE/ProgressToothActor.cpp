#include "ProgressToothActor.h"

AProgressToothActor::AProgressToothActor()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void AProgressToothActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<USceneComponent*> ChildrenComp;
	GetRootComponent()->GetChildrenComponents(true, ChildrenComp);

	for (USceneComponent* Comp : ChildrenComp) 
	{
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Comp)) 
		{
			if (MeshComp->GetName().Contains(TEXT("Tooth"))) 
			{
				ToothMeshes.Add(MeshComp);		// 뽑을 이빨 메시 할당
				InitialToothLocations.Add(MeshComp->GetRelativeLocation());		// 이빨 메시 초기 위치 저장
				TargetToothLocations.Add(MeshComp->GetRelativeLocation());		//초기 목표도 초기 위치

			}
		}
	}
}

void AProgressToothActor::OnProgressUpdated(float NewProgress)
{
	CurrentProgress = FMath::Clamp(NewProgress, 0.f, 100.f);




	if (ToothMeshes.Num() == 0)
	{

		return;
	}

	const float NormalizedProgress = CurrentProgress / 100.0f;
	const int32 ToothIndex = FMath::FloorToInt(NormalizedProgress * ToothMeshes.Num());

	if (!ToothMeshes.IsValidIndex(ToothIndex))
	{
		return;
	}

	float LocalProgress = (NormalizedProgress * ToothMeshes.Num()) - ToothIndex;

	FVector StartLocation = InitialToothLocations[ToothIndex];
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, MaxHeight * LocalProgress);


	TargetToothLocations[ToothIndex] = EndLocation;
}


void AProgressToothActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < ToothMeshes.Num(); ++i)
	{
		if (!ToothMeshes[i]) continue;

		FVector CurrentLoc = ToothMeshes[i]->GetRelativeLocation();
		FVector TargetLoc = TargetToothLocations[i];

		// 보간
		FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLoc, DeltaTime, MoveSpeed);
		ToothMeshes[i]->SetRelativeLocation(NewLoc);
	}
}





