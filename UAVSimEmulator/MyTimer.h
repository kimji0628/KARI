// MyTimer.h: interface for the CMyTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIMER_H__42A2CAA0_BB3C_410B_B9EF_F2D9CC532737__INCLUDED_)
#define AFX_MYTIMER_H__42A2CAA0_BB3C_410B_B9EF_F2D9CC532737__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTimer  
{
public:
	CMyTimer();
	virtual ~CMyTimer();
public:
	void SetStartTime(float fFirstTime) { m_fStartTime = fFirstTime; }
	void SetEndTime(float fEndTime) { m_fEndTime = fEndTime; }
	void SetPlay();
	void SetPlayBack();
	void SetPause();
	void SetStop();
	void FastForward();
	void FastBackward();

	double GetTimeMilisecond();
	float GetElapseTime() { return m_fElaspTime; }
	void  SetElapseTime(float fTime) { m_fElaspTime = fTime; }
	float GetPlaySpeed() { return m_fPlaySpeed; }
	float GetEndTime() { return m_fEndTime; }
	
	void PassTime(float fTime);

	BOOL IsPlay() { return m_bIsPlay; }
	BOOL IsPause() { return m_bIsPause; }

	int GetDirection() { return m_nDirection; }
public:	
	float m_fSystemTime;
private:
	float m_fStartTime;
	float m_fElaspTime;
	float m_fEndTime;
	float m_fPauseTime;
	float m_fIterationTime;
	float m_fPreviousTime;
	float m_fCurrentTime;
	int	  m_nDirection;

	BOOL m_bIsPlay;
	BOOL m_bIsPause;

	float m_fPlaySpeedStep;
	float m_fPlaySpeed;
};

#endif // !defined(AFX_MYTIMER_H__42A2CAA0_BB3C_410B_B9EF_F2D9CC532737__INCLUDED_)
