#include "StdAfx.h"
#include "EasyInput.h"






CEasyInput::CEasyInput(void)
{

	m_MaxInput.fElevator = -10000.0;
	m_MaxInput.fRudder = -10000.0;
	m_MaxInput.fAileron = -10000.0;
	m_MaxInput.fThrottleLever = -10000.0;
	m_MinInput.fElevator = 10000.0;
	m_MinInput.fRudder= 10000.0;
	m_MinInput.fAileron= 10000.0;
	m_MinInput.fThrottleLever= 10000.0;


}

CEasyInput::~CEasyInput(void)
{
}


void	CEasyInput::Init()
{


}


void	CEasyInput::Server(DIJOYSTATE2 *joy)
{
	memcpy((DIJOYSTATE2	*)&m_Joy,joy, sizeof(DIJOYSTATE2));
	SetNeutralPosition();
	SetControlInput(0.00005f, 0.00005f,0.00005f,0.003f);


}


void	CEasyInput::SetNeutralPosition()
{
/// Pitch 입력 
	if(m_Joy.lY > m_MaxInput.fElevator)
	{
		m_MaxInput.fElevator = m_Joy.lY; 
	}
	if(m_Joy.lY < m_MinInput.fElevator)
	{
		m_MinInput.fElevator = m_Joy.lY; 
	}
	m_Neutral.fElevator = (m_MaxInput.fElevator + m_MinInput.fElevator) / 2.0f;

/// Roll 입력 
	if(m_Joy.lX > m_MaxInput.fAileron)
	{
		m_MaxInput.fAileron = m_Joy.lX; 
	}
	if(m_Joy.lX < m_MinInput.fAileron)
	{
		m_MinInput.fAileron = m_Joy.lX; 
	}
	m_Neutral.fAileron = (m_MaxInput.fAileron + m_MinInput.fAileron) / 2.0f;

/// Yaw 입력 
	if(m_Joy.lRz > m_MaxInput.fRudder)
	{
		m_MaxInput.fRudder = m_Joy.lRz; 
	}
	if(m_Joy.lRz < m_MinInput.fRudder)
	{
		m_MinInput.fRudder = m_Joy.lRz; 
	}
	m_Neutral.fRudder = (m_MaxInput.fRudder + m_MinInput.fRudder) / 2.0f;

/// Throttle 입력 
	float fThrottleJoy = 0.0f;
	if( g_CSSSMaster.m_nJoyStickType == 0 )
	{
		fThrottleJoy = m_Joy.lZ;
	}
	else if( g_CSSSMaster.m_nJoyStickType == 1 )
	{
		fThrottleJoy = m_Joy.rglSlider[0];

	} 
	else
	{
		fThrottleJoy = m_Joy.lZ;

	}

	if(m_Joy.lZ > m_MaxInput.fThrottleLever)
	{
		m_MaxInput.fThrottleLever = fThrottleJoy; 
	}
	if(m_Joy.lZ < m_MinInput.fThrottleLever)
	{
		m_MinInput.fThrottleLever = fThrottleJoy; 
	}
	m_Neutral.fThrottleLever = (m_MaxInput.fThrottleLever + m_MinInput.fThrottleLever) / 2.0f;
	
}

void	CEasyInput::SetControlInput(float fScaleEle, float fScaleRudder,float fScaleAileron,float fScaleThrottle)
{
	m_fElevator = (m_Joy.lY - m_Neutral.fElevator) * fScaleEle;
// Throttle 입력 
	float fThrottleJoy  = 0.0f;
	if( g_CSSSMaster.m_nJoyStickType == 0 )
	{
		fThrottleJoy = m_Joy.lZ;
	}
	else if( g_CSSSMaster.m_nJoyStickType == 1 )
	{
		fThrottleJoy = m_Joy.rglSlider[0];

	} 
	else
	{
		fThrottleJoy = m_Joy.lZ;

	}

	m_fThrottleLever = ( fThrottleJoy - m_Neutral.fThrottleLever) * fScaleThrottle;
	
	
	
	m_fRudder = (m_Joy.lRz - m_Neutral.fRudder) * fScaleRudder;
	if( g_CSSSMaster.m_nJoyStickType == 0 )
	{
		m_fAileron = (m_Joy.lX - m_Neutral.fAileron) * fScaleAileron;
	}
	else
	{
		m_fAileron = -(m_Joy.lX - m_Neutral.fAileron) * fScaleAileron;

	}
}




float	CEasyInput::GetElevatorContolInput(float fScale)
{
	float	fV;
	fV = (m_Joy.lY - m_Neutral.fElevator) * fScale;
	return(fV);
}


float	CEasyInput::GetThrottleContolInput(float fScale)
{
	float	fV;
	fV = (m_Joy.lZ - m_Neutral.fThrottleLever) * fScale;
	return(fV);


}
float	CEasyInput::GetRudderContolInput(float fScale)
{

	float	fV;
	fV = (m_Joy.lRz - m_Neutral.fRudder) * fScale;

	return(fV);
}
float	CEasyInput::GetAileronContolInput(float fScale)
{

	float	fV;
	fV = (m_Joy.lX - m_Neutral.fAileron) * fScale;
	return(fV);

}