// Copyright 2017 Dr. Matthis Hölzl

#pragma once

#include "Components/SceneComponent.h"
#include "ChangeColorComponent.generated.h"


UCLASS(ClassGroup = "Blinkenlights", Meta = (BlueprintSpawnableComponent))
class FLICKER_API UChangeColorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UChangeColorComponent();

protected:
	void BeginPlay() override;


public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** The timeline for alternating between the colors */
	UPROPERTY(BlueprintReadWrite, Category = "Blinkenlights")
	FTimeline Timeline;

	/** The color curve for this timeline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blinkenlights")
	UCurveLinearColor* ColorCurve;

	/** Function to set the color. */
	UFUNCTION(BlueprintCallable, Category = "Blinkenlights")
	virtual void SetParentColor(FLinearColor Color);

	bool bIsReversing;

	UFUNCTION()
	void TogglePlayDirection();
};
