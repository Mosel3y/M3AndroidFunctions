// M3 Android Functions
// (c) 2018 Mark Whitty

#pragma once

#include "CoreMinimal.h"
#include "M3AndroidFunctionsBPLibrary.generated.h"

UCLASS()
class M3ANDROIDFUNCTIONS_API UM3AndroidFunctionsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	/**
	* Set  the visibility of the status bar NOTE: Must also have "Show Status Bar" true in plugin config settings
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Status Bar Visibility", Keywords = "status bar visibility android"), Category = "M3AndroidFunctions")
	static void setStatusBarVisibility(bool inVisibility);


	/**
	* Return intent string extra by key name
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Intent string extra", Keywords = "intent string extra"), Category = "M3AndroidFunctions")
	static FString getIntentStringExtra(FString keyName);

	/**
	* Set orientation to Portrait
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set to Portrait mode", Keywords = "orientation android Portrait"), Category = "M3AndroidFunctions")
	static void setPortrait();


	/**
	* Set orientation to Landscape
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set to Landscape mode", Keywords = "orientation android landscape"), Category = "M3AndroidFunctions")
	static void setLandscape();

	/**
	* Check is package installed
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName  = "Is Package Installed", Keywords = "package installed"), Category = "M3AndroidFunctions")
	static bool isPackageInstalled(FString packageName);

	/**
	* Open an external app, returns false on failure
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open External App", Keywords = "open external app android"), Category = "M3AndroidFunctions")
	static bool openExternalApp(FString packageName, TMap<FString, FString> intentStringExtras);

	/**
	* Check does device have a camera
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Device Has Camera", Keywords = "camera mobile android"), Category = "M3AndroidFunctions")
	static bool deviceHasCamera();

	/**
	* Open native camera app
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Native Camera", Keywords = "Open native camera android"), Category = "AndroidFunctions")
	static UM3AndroidFunctionsCameraCallbackProxy* openNativeCamera();

	/**
	* Opens gallery app for user to select image
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Gallery for Content", Keywords = "Open gallery get image"), Category = "AndroidFunctions")
	static UM3AndroidFunctionsCameraCallbackProxy* openGallery();
};
