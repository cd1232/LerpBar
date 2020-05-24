#pragma once

// Engine Includes
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

// Local Includes

// Generated Include

// Forward Includes

class ILerpBarModule : public IModuleInterface
{

public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ILerpBarModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ILerpBarModule>("LerpBarModule");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("LerpBarModule");
	}
};

