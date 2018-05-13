// M3 Android Functions
// (c) 2018 Mark Whitty

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "UObject/ObjectMacros.h" 
#include "UObject/ScriptMacros.h"
#include "Delegates/Delegate.h"
#include "M3AndroidFunctionsCameraCallbackProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FM3AndroidCameraCallbackDynamicDelegate, const FString&, imagePath, const TArray<uint8>&, imageData);
DECLARE_DELEGATE_TwoParams(FM3AndroidCameraCallbackDelegate, const FString& /*imagePath*/, const TArray<uint8>& /*imageData*/);


UCLASS()
class M3ANDROIDFUNCTIONS_API UM3AndroidFunctionsCameraCallbackProxy : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "M3AndroidFunctions")
	FM3AndroidCameraCallbackDynamicDelegate OnPhotoCapturedDynamicDelegate;

	FM3AndroidCameraCallbackDelegate OnPhotoCapturedDelegate;

	static UM3AndroidFunctionsCameraCallbackProxy *GetInstance();
};
