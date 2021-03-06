// Copyright 2017 Dr. Matthis Hölzl

#include "Flicker.h"
#include "ChangeColorComponent.h"
#include "Components/TimelineComponent.h"


UChangeColorComponent::UChangeColorComponent()
	: bIsReversing{ false }
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UCurveLinearColor> ColorCurveFinder;

		FConstructorStatics()
			: ColorCurveFinder{ TEXT("CurveLinearColor'/Game/Curves/DefaultColorCurve.DefaultColorCurve'") }
		{}
	};

	static FConstructorStatics ConstructorStatics;

	if (ConstructorStatics.ColorCurveFinder.Succeeded())
	{
		ColorCurve = ConstructorStatics.ColorCurveFinder.Object;
	}

	PrimaryComponentTick.bCanEverTick = true;
}

void UChangeColorComponent::BeginPlay()
{
	if (ColorCurve)
	{
		Timeline.AddInterpLinearColor(ColorCurve, TBaseDelegate<void, FLinearColor>::CreateUObject(this, &UChangeColorComponent::SetParentColor));
	}

	Timeline.SetLooping(false);
	Timeline.SetTimelineFinishedFunc(TBaseDelegate<void>::CreateUObject(this, &UChangeColorComponent::TogglePlayDirection));
	Timeline.PlayFromStart();
}

void UChangeColorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timeline.TickTimeline(DeltaTime);
}

void UChangeColorComponent::SetParentColor(FLinearColor Color)
{
	if (USceneComponent* Parent{ GetAttachParent() })
	{
		if (ULightComponent* ParentLight{ Cast<ULightComponent>(Parent) })
		{
			ParentLight->SetLightColor(Color);
		}
	}
}

void UChangeColorComponent::TogglePlayDirection()
{
	if (bIsReversing)
	{
		Timeline.PlayFromStart();
	}
	else
	{
		Timeline.ReverseFromEnd();
	}
	bIsReversing = !bIsReversing;
}

