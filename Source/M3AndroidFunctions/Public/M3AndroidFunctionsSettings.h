// M3 Android Functions
// (c) 2018 Mark Whitty

#pragma once

#include "M3AndroidFunctionsSettings.generated.h"



UCLASS(config = Engine, defaultconfig)
class UM3AndroidFunctionsSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UM3AndroidFunctionsSettings(const FObjectInitializer& ObjectInitializer);

	/** Whether to show the status bar or not, defaults to false */
	UPROPERTY(Config, EditAnywhere, Category = "Theme", meta = (DisplayName = "Show Status Bar"))
	bool bShowTitleBar;

	/** Add Camera permission to manifest */
	UPROPERTY(Config, EditAnywhere, Category = "Permissions", meta = (DisplayName = "Add camera permission"))
	bool bAddCameraPermission;
};
