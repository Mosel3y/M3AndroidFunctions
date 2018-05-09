// M3 Android Functions
// (c) 2018 Mark Whitty

#include "M3AndroidFunctionsBPLibrary.h"
#include "Misc/App.h"

UM3AndroidFunctionsBPLibrary::UM3AndroidFunctionsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UM3AndroidFunctionsBPLibrary::setStatusBarVisibility(bool inVisibility)
{
#if PLATFORM_ANDROID
	AndroidThunkCpp_setStatusBarVisibility(inVisibility);
#endif
	return;
}

FString UM3AndroidFunctionsBPLibrary::getIntentStringExtra(FString keyName)
{
	FString result = "not found";
#if PLATFORM_ANDROID
	result = AndroidThunkCpp_getIntentStringExtra(keyName);
#endif
	return result;
}

void UM3AndroidFunctionsBPLibrary::setPortrait()
{

#if PLATFORM_ANDROID
	AndroidThunkCpp_setPortrait();
#endif
	return;
}

void UM3AndroidFunctionsBPLibrary::setLandscape()
{
#if PLATFORM_ANDROID
	AndroidThunkCpp_setLandscape();
#endif
	return;
}

bool UM3AndroidFunctionsBPLibrary::isPackageInstalled(FString packageName)
{
	bool result = false;
#if PLATFORM_ANDROID
	result = AndroidThunkCpp_isPackageInstalled(packageName);
#endif
	return result; 
}

bool UM3AndroidFunctionsBPLibrary::openExternalApp(FString packageName, TMap<FString, FString> intentStringExtras)
{
	bool result = false;
#if PLATFORM_ANDROID
	TArray<FString> stringExtraKeys;
	TArray<FString> stringExtraKeysOrd;
	TArray<FString> stringExtraValues;

	intentStringExtras.GenerateKeyArray(stringExtraKeys);

	for (int32 i = 0; i != stringExtraKeys.Num(); ++i)
	{
		stringExtraKeysOrd.Insert(stringExtraKeys[i], i);
		stringExtraValues.Insert(intentStringExtras.FindRef(stringExtraKeys[i]), i);
	}
	result = AndroidThunkCpp_openExternalApp(packageName, stringExtraKeysOrd, stringExtraValues);
#endif
	return result;
}

bool UM3AndroidFunctionsBPLibrary::deviceHasCamera()
{
	bool result = false;
#if PLATFORM_ANDROID
	result = AndroidThunkCpp_deviceHasCamera();
#endif
	return result;
}