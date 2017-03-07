#pragma once
#if defined(_WINDOWS) && ! defined ( _3DRUDDER_SDK_STATIC) 
	#ifdef _USRDLL
		#define _3DRUDDER_SDK_EXPORT __declspec(dllexport)
	#else
		#define _3DRUDDER_SDK_EXPORT __declspec(dllimport)
	#endif
#else
	#define _3DRUDDER_SDK_EXPORT
#endif

#define  _3DRUDDER_SDK_MAX_DEVICE 4
#define  _3DRUDDER_SDK_VERSION 0x0070

#include <stdint.h>

#if defined(__GNUC__)
#define     _3DR_UNUSED(a)          		({__typeof__ (&a) __attribute__ ((unused)) __tmp = &a; })
#else
#define     _3DR_UNUSED(a)          		(a)
#endif



namespace ns3dRudder
{
	enum ErrorCode
	{
		Success = 0, NotConnected, Fail, IncorrectCommand, Timeout, WrongSignature,NotReady, Other = 0xFF
	};

	enum CurveType
	{
		CurveXAxis = 2, CurveYAxis = 1, CurveZAxis = 3, CurveZRotation = 0,  CurveYaw = 0, CurvePitch=1, CurveRoll=2, CurveUpDown=3, CurveMax=4
	};

	enum Status
	{
		NoStatus = 0, NoFootStayStill = 1, Initialisation, PutYourFeet, PutSecondFoot, StayStill, InUse, ExtendedMode, End = 0xffff
	};

	enum ModeAxis
	{
		UserRefAngle						=0,
		Angle								=0,
		NormalizedValue						=2,
		NormalisedValue						=2,
		ValueWithCurve						=3,
		NormalizedValueNonSymmetricalPitch	=4,
		NormalisedValueNonSymmetricalPitch	=4,
		ValueWithCurveNonSymmetricalPitch	=5
	};

	class Curve
	{
	public:
		Curve()
		{
			m_fDeadZone = 0; m_fxSat = 0; m_fyMax = 0; m_fExp = 0;
		}
		Curve(float fDeadZone,float fxSat,float fyMax,float fExp)
		{
			m_fDeadZone = fDeadZone; m_fxSat = fxSat; m_fyMax = fyMax; m_fExp = fExp;
		}
		virtual ~Curve() {}
		float GetDeadZone()  const { return m_fDeadZone; }
		float GeXSat()		 const { return m_fxSat; }
		float GetYMax()		 const { return m_fyMax; }
		float GetExp()		 const { return m_fExp; }

		void SetDeadZone(float fV)	{ m_fDeadZone=fV; }
		void SeXSat(float fV)		{ m_fxSat = fV; }
		void SetYMax(float fV)		{ m_fyMax = fV; }
		void SetExp(float fV)		{ m_fExp = fV; }

		virtual float CalcCurveValue(float fValue)  const;

		float m_fDeadZone;
		float m_fxSat;
		float m_fyMax;
		float m_fExp;
	};

	class CurveArray
	{
	public:
		CurveArray()
		{
			InitFactory();
		}
		void InitLinear()
		{
			m_Curve[CurveRoll] = Curve(0.0f, 1.0f, 1.0f, 1.0f);
			m_Curve[CurvePitch] = Curve(0.0f, 1.0f, 1.0f, 1.0f);
			m_Curve[CurveUpDown] = Curve(0.0f, 1.0f, 1.0f, 1.0f);
			m_Curve[CurveYaw] = Curve(0.0f, 1.0f, 1.0f, 1.0f);

			m_pCurve[CurveRoll]		= &m_Curve[CurveRoll];
			m_pCurve[CurvePitch]	= &m_Curve[CurvePitch];
			m_pCurve[CurveUpDown]	= &m_Curve[CurveUpDown];
			m_pCurve[CurveYaw]		= &m_Curve[CurveYaw];
		}
		void InitFactory()
		{
			m_Curve[CurveRoll] = Curve(2.0f / 18.0f, 12.0f / 18.0f, 1.0f, 2.0f);
			m_Curve[CurvePitch] = Curve(2.0f / 18.0f, 14.0f / 18.0f, 1.0f, 2.0f);
			m_Curve[CurveUpDown] = Curve(0.08f, 0.6f, 1.0f, 4.0f);
			m_Curve[CurveYaw] = Curve(3.0f / 25.0f, 20.0f / 25.0f, 1.0f, 2.0f);

			m_pCurve[CurveRoll]		= &m_Curve[CurveRoll];
			m_pCurve[CurvePitch]	= &m_Curve[CurvePitch];
			m_pCurve[CurveUpDown]	= &m_Curve[CurveUpDown];
			m_pCurve[CurveYaw]		= &m_Curve[CurveYaw];
		}
		Curve *GetCurve(CurveType nCurve)  const { return m_pCurve[nCurve]; }
		void SetCurve(CurveType nCurve, Curve *pCurve) { m_pCurve[nCurve] = pCurve; }
	private:
		Curve m_Curve[CurveMax];
		Curve *m_pCurve[CurveMax];

	};


	class Axis
	{
	public:

		Axis()
		{
			m_aX = m_aY = m_aZ = m_rZ = 0;
		}

		float m_aX;
		float m_aY;
		float m_aZ;
		float m_rZ;

		float GetXAxis()		const { return m_aX; }
		float GetYAxis()		const { return m_aY; }
		float GetZAxis()		const { return m_aZ; }
		float GetZRotation()	const { return m_rZ; }

		float GetPhysicalRoll()		{ return GetXAxis(); }
		float GetPhysicalPitch()	{ return GetYAxis(); }
		float GetUpDown()			{ return GetZAxis(); }
		float GetPhysicalYaw()		{ return GetZRotation(); }
	};

	class IEvent
	{
	public:
		virtual ~IEvent() {}
		virtual void OnConnect(uint32_t nDeviceNumber) { _3DR_UNUSED(nDeviceNumber); };
		virtual void OnDisconnect(uint32_t nDeviceNumber) { _3DR_UNUSED(nDeviceNumber); };
	};


	class CSdk
	{
	public:
		CSdk();
		~CSdk();
		virtual void Init()  const;
		virtual uint16_t GetSDKVersion() const;
		virtual int32_t GetNumberOfConnectedDevice() const ;
		virtual bool IsDeviceConnected(uint32_t nPortNumber) const;
		virtual uint16_t GetVersion(uint32_t nPortNumber,bool bUseCmd=false)  const;
		virtual ErrorCode HideSystemDevice(uint32_t nPortNumber, bool bHide)  const;
		virtual bool IsSystemDeviceHidden(uint32_t nPortNumber)  const;
		virtual ErrorCode PlaySnd(uint32_t nPortNumber, uint16_t nFrequency, uint16_t nDuration)  const;
		virtual ErrorCode ReadCurveFromDevice(uint32_t nPortNumber, CurveType nType, Curve *pCurve)  const;
		virtual ErrorCode WriteCurveToDevice(uint32_t nPortNumber, CurveType nType, Curve *pCurve)  const;
		virtual ErrorCode GetUserOffset(uint32_t nPortNumber, Axis *pAxis)  const;
		virtual ErrorCode GetAxis(uint32_t nPortNumber,ModeAxis nMode,Axis *pAxis,const CurveArray *pCurve=nullptr) const;
		virtual Status GetStatus(uint32_t nPortNumber)  const;
		virtual uint16_t GetSensor(uint32_t nPortNumber,uint32_t nIndex) const;

		virtual const char *GetErrorText(ErrorCode nError) const;
		virtual void SetEvent(IEvent *pEvent)  const;

	};

	_3DRUDDER_SDK_EXPORT CSdk* GetSDK();
	_3DRUDDER_SDK_EXPORT void EndSDK();
}
