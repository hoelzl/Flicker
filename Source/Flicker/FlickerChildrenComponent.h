#pragma once

#include "Components/ActorComponent.h"
#include "FlickerChildrenComponent.generated.h"


/** The state of the lights attached to the actor. */
UENUM()
enum class ELightState : uint8
{
	On UMETA(DisplayName = "Lights are switched on"),   /**< The lights are on... */
	Off UMETA(DisplayName = "Lights are switched off")  /**< But you're not home...*/
};

UCLASS(ClassGroup = "Blinkenlights", Meta = (BlueprintSpawnableComponent))
class FLICKER_API UFlickerChildrenComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFlickerChildrenComponent();

protected:
	void BeginPlay() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** The interval in which lights are turned on or off. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blinkenlights")
	float FlickerInterval;


protected:
	ELightState CurrentLightState;
	void ToggleLightState();
	void SetLightIntensity(UActorComponent* Child, ELightState LightState);

	UPROPERTY(Transient)
	TMap<ULightComponentBase*, float> StoredLightIntensities;
};
