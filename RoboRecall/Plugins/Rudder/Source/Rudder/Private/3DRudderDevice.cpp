#include "3DRudderPrivatePCH.h"
 
#include "3DRudderDevice.h"
 
#include "SlateBasics.h"
 
#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "WindowsCursor.h"
#include "GenericApplicationMessageHandler.h"

#include "InputDevice.h"

#define _3DRUDDER_SDK_STATIC
#include "3DRudderSDK.h"

#define LOCTEXT_NAMESPACE "3DRudder"

const FKey EKeys3DRudder::XAxis("XAxis");
const FKey EKeys3DRudder::YAxis("YAxis");
const FKey EKeys3DRudder::ZAxis("ZAxis");
const FKey EKeys3DRudder::ZRotation("ZRotation");
const FKey EKeys3DRudder::Status("Status");
const FKey EKeys3DRudder::Sensor1("Sensor1");
const FKey EKeys3DRudder::Sensor2("Sensor2");
const FKey EKeys3DRudder::Sensor3("Sensor3");
const FKey EKeys3DRudder::Sensor4("Sensor4");
const FKey EKeys3DRudder::Sensor5("Sensor5");
const FKey EKeys3DRudder::Sensor6("Sensor6");


 
DEFINE_LOG_CATEGORY_STATIC(Log3DRudderDevice, Log, All);

//UE v4.6 IM event wrappers
bool EmitKeyUpEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool EmitKeyDownEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool EmitAnalogInputEventForKey(FKey key, float value, int32 user, bool repeat)
{
	FAnalogInputEvent AnalogInputEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0, value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}


F3DRudderDevice::F3DRudderDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
	: m_MessageHandler(InMessageHandler)
{
	UE_LOG(Log3DRudderDevice, Log, TEXT("Starting 3DRudderDevice"));
 
 
	// Register the FKeys (Gamepad key for controllers)
	EKeys::AddMenuCategoryDisplayInfo("3DRudder", LOCTEXT("3DRudderSubCateogry", "3DRudder"), TEXT("GraphEditor.PadEvent_16x"));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::XAxis		,LOCTEXT("XAxis"	,"3DRudder XAxis")		,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::YAxis		,LOCTEXT("YAxis"	,"3DRudder YAxis")		,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::ZAxis		,LOCTEXT("ZAxis"	,"3DRudder ZAxis")		,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::ZRotation	,LOCTEXT("ZRotation","3DRudder ZRotation")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Status		,LOCTEXT("Status"	,"3DRudder Status")		,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor1	,LOCTEXT("Sensor1"	,"3DRudder Sensor1")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor2	,LOCTEXT("Sensor2"	,"3DRudder Sensor2")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor3	,LOCTEXT("Sensor3"	,"3DRudder Sensor3")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor4	,LOCTEXT("Sensor4"	,"3DRudder Sensor4")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor5	,LOCTEXT("Sensor5"	,"3DRudder Sensor5")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
	EKeys::AddKey(FKeyDetails(EKeys3DRudder::Sensor6	,LOCTEXT("Sensor6"	,"3DRudder Sensor6")	,FKeyDetails::FloatAxis, FName(TEXT("3DRudder"))));
}
 
void F3DRudderDevice::Tick(float DeltaTime)
{
	// This will spam the log heavily, comment it out for real plugins :)
	// UE_LOG(Log3DRudderDevice, Log, TEXT("Tick %f"), DeltaTime);
}
 
void F3DRudderDevice::SendControllerEvents() 
{
	ns3dRudder::CSdk* pSdk = ns3dRudder::GetSDK();
	ns3dRudder::ModeAxis mode = ns3dRudder::ModeAxis::ValueWithCurve;
	ns3dRudder::CurveArray *curves = new ns3dRudder::CurveArray;
	for (unsigned int i = 0;i < _3DRUDDER_SDK_MAX_DEVICE;i++)
	{
		if (pSdk->IsDeviceConnected(i))
		{
			ns3dRudder::Axis axis;
			ns3dRudder::Status status;
			if (pSdk->GetAxis(i, mode, &axis, curves) == ns3dRudder::Success)
			{
				status = pSdk->GetStatus(i);
				EmitAnalogInputEventForKey(EKeys3DRudder::XAxis, axis.m_aX, i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::YAxis, axis.m_aY, i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::ZAxis, axis.m_aZ, i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::ZRotation, axis.m_rZ, i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Status, status, i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor1, pSdk->GetSensor(i, 0), i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor2, pSdk->GetSensor(i, 1), i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor3, pSdk->GetSensor(i, 2), i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor4, pSdk->GetSensor(i, 3), i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor5, pSdk->GetSensor(i, 4), i, 0);
				EmitAnalogInputEventForKey(EKeys3DRudder::Sensor6, pSdk->GetSensor(i, 5), i, 0);
			}							   
		}
	}
}
 
void F3DRudderDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) 
{
	UE_LOG(Log3DRudderDevice, Log, TEXT("Set Message Handler"));
	m_MessageHandler = InMessageHandler;
}
 
bool F3DRudderDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) 
{
	UE_LOG(Log3DRudderDevice, Log, TEXT("Execute Console Command: %s"), Cmd);
 
	// Put your fancy custom console command code here... 
	// ToDo: use this to let you fire pseudo controller events
 
	return true;
}

// IForceFeedbackSystem pass through functions
void F3DRudderDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) {
	UE_LOG(Log3DRudderDevice, Log, TEXT("Set Force Feedback %f"), Value);
}
void F3DRudderDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) {
	// This will spam the log heavily, comment it out for real plugins :)
	UE_LOG(Log3DRudderDevice, Log, TEXT("Set Force Feedback Values"));
}
 

// This is where you nicely clean up your plugin when its told to shut down!
F3DRudderDevice::~F3DRudderDevice() 
{
	UE_LOG(Log3DRudderDevice, Log, TEXT("Closing 3DRudderDevice"));
}