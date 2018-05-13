// M3 Android Functions
// (c) 2018 Mark Whitty

#include "M3AndroidFunctionsCameraCallbackProxy.h"
#include "IM3AndroidFunctions.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

static UM3AndroidFunctionsCameraCallbackProxy *pProxy = NULL;

UM3AndroidFunctionsCameraCallbackProxy *UM3AndroidFunctionsCameraCallbackProxy::GetInstance()
{
	if (!pProxy) {
		pProxy = NewObject<UM3AndroidFunctionsCameraCallbackProxy>();
		pProxy->AddToRoot();
	}
	return pProxy;
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_ue4_GameActivity_onImageCaptured(JNIEnv *env, jclass clazz, jstring imagePath)
{
	const char * nativeString = env->GetStringUTFChars(imagePath, 0);
	FString imagePathU = FString(nativeString);

	TArray<uint8> imageData;
	IFileHandle* FileHandle = FPlatformFileManager::Get().GetPlatformFile().OpenRead(*imagePathU);
	if (FileHandle != nullptr)
	{
		int32 byteSize = FileHandle->Size();
		uint8* Bytes = new uint8[byteSize];
		FileHandle->Read(Bytes, byteSize);
		imageData.Append(Bytes, byteSize);
		delete[] Bytes;
		delete FileHandle;
	}

	pProxy->OnPhotoCapturedDelegate.ExecuteIfBound(imagePathU, imageData);
	pProxy->OnPhotoCapturedDynamicDelegate.Broadcast(imagePathU, imageData);
}
#endif
