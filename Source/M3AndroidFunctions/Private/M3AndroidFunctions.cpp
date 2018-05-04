// M3 Android Functions
// (c) 2018 Mark Whitty

#include "IM3AndroidFunctions.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "M3AndroidFunctionsClasses.h"
#include "M3AndroidFunctionsSettings.h"
#include "ISettingsModule.h"

#if PLATFORM_ANDROID
#include "../../../ApplicationCore/Public/Android/AndroidApplication.h"
#include "../../../Launch/Public/Android/AndroidJNI.h"
#include <android/log.h>
#include "Misc/App.h"

#define LOG_TAG "M3AndroidFunctionsLOG"

int SetupJNIM3AndroidFunctions(JNIEnv* env);
JNIEnv* ENV = NULL;
static jmethodID AndroidThunkJava_setStatusBarVisibility;
static jmethodID AndroidThunkJava_getIntentStringExtra;
static jmethodID AndroidThunkJava_setPortrait;
static jmethodID AndroidThunkJava_setLandscape;
static jmethodID AndroidThunkJava_isPackageInstalled;
static jmethodID AndroidThunkJava_openExternalApp;
#endif

#define LOCTEXT_NAMESPACE "FM3AndroidFunctionsModule"

class FM3AndroidFunctions : public IM3AndroidFunctions
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FM3AndroidFunctions, M3AndroidFunctions)

// Startup Module
void FM3AndroidFunctions::StartupModule()
{
	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "M3AndroidFunctions",
			LOCTEXT("RuntimeSettingsName", "M3 Android Functions"),
			LOCTEXT("RuntimeSettingsDescription", "Configure settings for the M3 Android Functions plugin"),
			GetMutableDefault<UM3AndroidFunctionsSettings>()
			);
	}
#if PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	SetupJNIM3AndroidFunctions(env);
#endif
}


// Shutdown Module
void FM3AndroidFunctions::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

#if PLATFORM_ANDROID
int SetupJNIM3AndroidFunctions(JNIEnv* env)
{
	if (!env) return JNI_ERR;

	ENV = env;

	AndroidThunkJava_setStatusBarVisibility = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_setStatusBarVisibility", "(Z)V", true);
	AndroidThunkJava_getIntentStringExtra = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_getIntentStringExtra", "(Ljava/lang/String;)Ljava/lang/String;", false);
	AndroidThunkJava_setPortrait = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_setPortrait", "()V", false);
	AndroidThunkJava_setLandscape = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_setLandscape", "()V", false);
	AndroidThunkJava_isPackageInstalled = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_isPackageInstalled", "(Ljava/lang/String;)Z", false);
	AndroidThunkJava_openExternalApp = FJavaWrapper::FindMethod(ENV, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_openExternalApp", "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)Z", false);

	return JNI_OK;
}

void AndroidThunkCpp_setStatusBarVisibility(const bool& inVisibility)
{
	if (!AndroidThunkJava_setStatusBarVisibility || !ENV) return;
	FJavaWrapper::CallVoidMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_setStatusBarVisibility, inVisibility);
	return;
}

FString AndroidThunkCpp_getIntentStringExtra(const FString keyName)
{
	if (!AndroidThunkJava_getIntentStringExtra || !ENV) return "not found";
	jstring keyNameJ = ENV->NewStringUTF(TCHAR_TO_UTF8(*keyName));
	jstring Return = (jstring)FJavaWrapper::CallObjectMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_getIntentStringExtra, keyNameJ);
	const char * nativeString = ENV->GetStringUTFChars(Return, 0);
	FString result = FString(nativeString);
	return result;
}

void AndroidThunkCpp_setPortrait()
{
	if (!AndroidThunkJava_setPortrait || !ENV) return;
	FJavaWrapper::CallVoidMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_setPortrait);
	return;
}

void AndroidThunkCpp_setLandscape()
{
	if (!AndroidThunkJava_setLandscape || !ENV) return;
	FJavaWrapper::CallVoidMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_setLandscape);
	return;
}

bool AndroidThunkCpp_isPackageInstalled(const FString packageName)
{
	if (!AndroidThunkJava_isPackageInstalled || !ENV) return false;
	jstring packageNameJ = ENV->NewStringUTF(TCHAR_TO_UTF8(*packageName));
	return FJavaWrapper::CallBooleanMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_isPackageInstalled, packageNameJ);
}

bool AndroidThunkCpp_openExternalApp(const FString packageName, const TArray<FString> stringExtraKeys, const TArray<FString> stringExtraValues)
{
	if (!AndroidThunkJava_openExternalApp || !ENV) return false;
	jstring packageNameJ = ENV->NewStringUTF(TCHAR_TO_UTF8(*packageName));

	jstring stringExtraKeysCh[stringExtraKeys.Num()];
	jstring stringExtraValuesCh[stringExtraKeys.Num()];

	for (int32 i = 0; i != stringExtraKeys.Num(); ++i)
	{
		stringExtraKeysCh[i] = ENV->NewStringUTF(TCHAR_TO_UTF8(*stringExtraKeys[i]));
		stringExtraValuesCh[i] = ENV->NewStringUTF(TCHAR_TO_UTF8(*stringExtraValues[i]));
	}

	jstring str;
	jobjectArray stringExtraKeysJ = 0;
	jobjectArray stringExtraValuesJ = 0;
	jsize len = stringExtraKeys.Num();

	stringExtraKeysJ = ENV->NewObjectArray(len, ENV->FindClass("java/lang/String"), 0);
	stringExtraValuesJ = ENV->NewObjectArray(len, ENV->FindClass("java/lang/String"), 0);

	for (int i = 0; i <len; ++i)
	{
		str = stringExtraKeysCh[i];
		ENV->SetObjectArrayElement(stringExtraKeysJ, i, str);
		str = stringExtraValuesCh[i];
		ENV->SetObjectArrayElement(stringExtraValuesJ, i, str);
	}

	return FJavaWrapper::CallBooleanMethod(ENV, FJavaWrapper::GameActivityThis, AndroidThunkJava_openExternalApp, packageNameJ, stringExtraKeysJ, stringExtraValuesJ);
}
#endif
