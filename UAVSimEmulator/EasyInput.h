#pragma once

typedef struct {
	float		fElevator;
	float		fRudder;
	float		fAileron;
	float		fThrottleLever;
} CONTROL_INPUT;


class CEasyInput
{
public:
	DIJOYSTATE2		m_Joy;
	CONTROL_INPUT	m_MaxInput;
	CONTROL_INPUT	m_MinInput;
	CONTROL_INPUT	m_Neutral;

public:
	float	m_fElevator;
	float	m_fRudder;
	float	m_fAileron;
	float	m_fThrottleLever;



public:
	CEasyInput(void);
	~CEasyInput(void);
	void	Init();
	void	Server(DIJOYSTATE2 *joy);
	void	SetNeutralPosition();
	void	SetControlInput(float fScaleEle, float fScaleRudder,float fScaleAileron,float fScaleThrottle);


	float	GetElevatorContolInput(float fScale);
	float	GetThrottleContolInput(float fScale);
	float	GetRudderContolInput(float fScale);
	float	GetAileronContolInput(float fScale);
	
};

