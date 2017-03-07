#pragma once
 
#include <InputDevice.h>


// Input Mapping Keys
struct EKeys3DRudder
{
	static const FKey XAxis;
	static const FKey YAxis;
	static const FKey ZAxis;
	static const FKey ZRotation;
	static const FKey Status;
	static const FKey Sensor1;
	static const FKey Sensor2;
	static const FKey Sensor3;
	static const FKey Sensor4;
	static const FKey Sensor5;
	static const FKey Sensor6;
};
 
/**
* Interface class for 3DRudder devices 
*/
class F3DRudderDevice : public IInputDevice
{
public:
	F3DRudderDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
 
	/** Tick the interface (e.g. check for new controllers) */
	void Tick(float DeltaTime) override;
 
	/** Poll for controller state and send events if needed */
	void SendControllerEvents() override;
 
	/** Set which MessageHandler will get the events from SendControllerEvents. */
	void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;
 
	/** Exec handler to allow console commands to be passed through for debugging */
	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	// IForceFeedbackSystem pass through functions
	void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

	virtual ~F3DRudderDevice();
private:
 
	TSharedRef< FGenericApplicationMessageHandler > m_MessageHandler;
};