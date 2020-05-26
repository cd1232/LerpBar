// This Include
#include "LerpBarWidget.h"

// Engine Includes
#include "Components/ProgressBar.h"

// Local Includes

float ULerpBarWidget::WillLerpOverTime() const
{
	return bWillLerpOverSetTime;
}

void ULerpBarWidget::SetPercentDirectly(const float Percent) const
{
	MainBar->SetPercent(Percent);
	GhostBar->SetPercent(Percent);
}

void ULerpBarWidget::LerpTo(float Percent)
{
	// Don't let percent go less than 0
	PercentToLerpTo = FMath::Min(FMath::Max(0.0f, Percent), 1.0f);
	
	const bool bIsGaining = Percent > MainBar->Percent;
	const bool bWasLerping = bIsLerping;
	
	BarToLerp = bIsGaining ? MainBar : GhostBar;
	DelayTillLerpTimer = DelayTillLerp;
	bIsLerping = true;

	// This will happen once when first starting a lerp
	const float Distance = FMath::Abs(BarToLerp->Percent - PercentToLerpTo);
	CalculatedSpeed = Distance / TimeToMove;
	

	// Main bar should catch up to ghost bar if we're gaining
    if (bIsGaining)
    {
    	GhostBar->SetFillColorAndOpacity(GhostBarGainColor);
    	GhostBar->SetPercent(Percent);
    }
	else
	{
		GhostBar->SetFillColorAndOpacity(OriginalGhostBarColor);
		MainBar->SetPercent(Percent);		
	}
}

void ULerpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();	
	OriginalGhostBarColor = GhostBar->FillColorAndOpacity;
}

void ULerpBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (bIsLerping)
	{
		if (DelayTillLerpTimer > 0.0f)
		{
			DelayTillLerpTimer -= InDeltaTime;
			return;
		}
	
		const float NewPercent = FMath::FInterpConstantTo(BarToLerp->Percent, PercentToLerpTo, InDeltaTime, CalculatedSpeed);
		BarToLerp->SetPercent(NewPercent);

		if (NewPercent == PercentToLerpTo)
		{
			bIsLerping = false;
		}
	}
}
