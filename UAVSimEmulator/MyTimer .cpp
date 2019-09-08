// MyTimer.cpp: implementation of the CMyTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdAfx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMyTimer::CMyTimer()
{
	m_fStartTime = 0.0f;
	m_fElaspTime = 0.0f;
	m_fPauseTime = 0.0f;

	m_bIsPlay = 0.0f;
	m_bIsPause = 0.0f;
	m_fPlaySpeed = 1.0f;
	m_fPlaySpeedStep = 1.0f;
	m_nDirection = 1;

	m_fEndTime = 100000.0f;
}

CMyTimer::~CMyTimer()
{

}

double CMyTimer::GetTimeMilisecond()
{
	double	dTime;
	dTime =  clock()*1000.0/CLOCKS_PER_SEC;
	return	dTime;
}




void CMyTimer::SetPlay()
{
	if(m_bIsPause)
	{
		m_bIsPause = FALSE;
	}
	m_nDirection = 1;
	m_bIsPlay = TRUE;
}

void CMyTimer::SetPlayBack()
{
	if(m_bIsPause)
	{
		m_bIsPause = FALSE;
	}
	m_nDirection = -1;
	m_bIsPlay = TRUE;
}

void CMyTimer::SetPause()
{
	if(m_bIsPlay)
	{
		m_bIsPlay = FALSE;
	}

	m_bIsPause = TRUE;
}

void CMyTimer::SetStop()
{
	m_bIsPause = TRUE;
	m_bIsPlay = FALSE;

	m_fIterationTime = 0.0f;
	m_fPreviousTime = (float) (GetTimeMilisecond()/1000.0);
	m_fCurrentTime =m_fPreviousTime;
	m_fElaspTime = 0.0f;
}

void CMyTimer::PassTime(float	fTime)
{
	m_fCurrentTime = (float) (GetTimeMilisecond()/1000.0);
	m_fIterationTime = m_fCurrentTime - m_fPreviousTime;
	m_fPreviousTime = m_fCurrentTime;
	
	if(m_bIsPlay)
	{
		if(m_nDirection == 1)
		{
			m_fElaspTime += (m_fIterationTime* m_fPlaySpeed);
			//if(m_fElaspTime < 0.0f) m_fElaspTime = 0.0f;
		}
		else if (m_nDirection == -1)
		{
			m_fElaspTime -= (m_fIterationTime* m_fPlaySpeed);
			if(m_fElaspTime < 0.0f) m_fElaspTime = 0.0f;
			//if(m_fElaspTime > 3600.0f) m_fElaspTime = 3600.0f;
		}
		if( m_fEndTime < m_fElaspTime ) 
		{
			m_fElaspTime = m_fEndTime;
		}
	}
	else if(m_bIsPause)
			m_fIterationTime = 0.0f;

}

void CMyTimer::FastForward()
{
//	m_nDirection = 1;
	m_fPlaySpeed += m_fPlaySpeedStep;
	if(m_fPlaySpeed >20) m_fPlaySpeed = 20;

}

void CMyTimer::FastBackward()
{
//	m_nDirection = -1;
	m_fPlaySpeed -= m_fPlaySpeedStep;
	if(m_fPlaySpeed <1 ) m_fPlaySpeed = 1;
}



