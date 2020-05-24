#pragma once

// Engine Includes
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Styling/SlateTypes.h"

// Local Includes

// Generated Include
#include "LerpBarWidget.generated.h"

// Forward Includes

UCLASS(Blueprintable)
class LERPBAR_API ULerpBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float WillLerpOverTime() const;

	/** Sets the Main bar and Ghost bar to a percent without lerping */
	UFUNCTION(BlueprintCallable)
	void SetPercentDirectly(float Percent) const;

	/** Set a new percentage to lerp to */
	UFUNCTION(BlueprintCallable)
	void LerpTo(float Percent);
	
protected:
	virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* MainBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* GhostBar;

	/** Set the ghost bar to this color when gaining */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor GhostBarGainColor;
	
private:
	UPROPERTY()
	UProgressBar* BarToLerp = nullptr;

	UPROPERTY()
	FLinearColor OriginalGhostBarColor;
	
	/** Used if we don't lerp over set time. This is how much percent per second */
    UPROPERTY(EditAnywhere, meta = (EditCondition = "!bWillLerpOverSetTime"))
    float SpeedPerSecond = 0.0f;

	/** How long it will take to lerp from start value to new value passed through LerpTo */
	UPROPERTY(EditAnywhere)
    float TimeToMove = 0.5f;

	/** How long before we start lerping after we are told to lerp */
	UPROPERTY(EditAnywhere)
    float DelayTillLerp = 0.5f;

	/** Current time left before we start lerping */
	float DelayTillLerpTimer = 0.0f;

	/** Percentage to interpolate to */
	float PercentToLerpTo = 0.0f;
	
	/** Current speed of interpolation, determined from time and distance */
	float CalculatedSpeed = 0.0f;

	/** Are we currently lerping towards a new percentage? */
	bool bIsLerping = false;

	/** 
	* Will the bar lerp over a set time (e.g. always takes 2 seconds to reach)
	* or will it lerp using a constant speed 
	*/
	UPROPERTY(EditDefaultsOnly)
	bool bWillLerpOverSetTime = true;
};