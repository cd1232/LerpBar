// This Include
#include "LerpBarModule.h"

// Engine Includes
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

// Local Includes

class FLerpBarModule : public ILerpBarModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FLerpBarModule, LerpBar)


void FLerpBarModule::StartupModule()
{
}

void FLerpBarModule::ShutdownModule()
{
}



