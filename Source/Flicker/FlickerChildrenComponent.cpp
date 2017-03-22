
#include "Flicker.h"
#include "FlickerChildrenComponent.h"


UFlickerChildrenComponent::UFlickerChildrenComponent()
	: FlickerInterval{ 2.f }
	, CurrentLightState{ ELightState::Off }
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickInterval = FlickerInterval;
}


void UFlickerChildrenComponent::BeginPlay()
{
	Super::BeginPlay();
	
	StoredLightIntensities.Empty();
	for (UActorComponent* Child : GetAttachChildren())
	{
		if (ULightComponent* ChildLight{ Cast<ULightComponent>(Child) })
		{
			StoredLightIntensities.Add(ChildLight, ChildLight->Intensity);
		}
	}
}

#if WITH_EDITOR
void UFlickerChildrenComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UFlickerChildrenComponent, FlickerInterval))
	{
		PrimaryComponentTick.TickInterval = FlickerInterval;
	}
}
#endif // WITH_EDITOR

void UFlickerChildrenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ToggleLightState();

	for (UActorComponent* Child : GetAttachChildren())
	{
		SetLightIntensity(Child, CurrentLightState);
	}
}

void UFlickerChildrenComponent::SetLightIntensity(UActorComponent* Child, ELightState LightState)
{
	if (ULightComponent* ChildLight{ Cast<ULightComponent>(Child) })
	{
		if (LightState == ELightState::On)
		{
			if (StoredLightIntensities.Contains(ChildLight))
			{
				ChildLight->SetIntensity(StoredLightIntensities[ChildLight]);
			}
			else
			{
				ChildLight->SetIntensity(5000.f);
			}
		}
		else
		{
			StoredLightIntensities.Add(ChildLight, ChildLight->Intensity);
			ChildLight->SetIntensity(0.f);
		}
	}
}

void UFlickerChildrenComponent::ToggleLightState()
{
	if (CurrentLightState == ELightState::Off)
	{
		CurrentLightState = ELightState::On;
	}
	else
	{
		CurrentLightState = ELightState::Off;
	}
}

