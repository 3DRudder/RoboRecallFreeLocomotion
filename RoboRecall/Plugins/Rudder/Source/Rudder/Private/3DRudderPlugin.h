#pragma once
#include "3DRudderDevice.h"
 
class F3DRudderPlugin : public I3DRudderPlugin
{
public:
	/** I3DRudderInterface implementation */
	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
 
	//virtual void StartupModule() OVERRIDE; // This is not required as IInputDeviceModule handels it!
	virtual void ShutdownModule() override;
 
	TSharedPtr< class F3DRudderDevice > m_3DRudderDevice;
};