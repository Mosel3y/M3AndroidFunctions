// M3 Android Functions
// (c) 2018 Mark Whitty

#pragma once

#include "ModuleManager.h"

class IM3AndroidFunctions : public IModuleInterface
{
public:
	static inline IM3AndroidFunctions& Get()
	{
		return FModuleManager::LoadModuleChecked< IM3AndroidFunctions >("M3AndroidFunctions");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("M3AndroidFunctions");
	}
};