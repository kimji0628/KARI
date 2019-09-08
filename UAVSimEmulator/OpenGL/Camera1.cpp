// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera1.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern	float	mouse_sensitivity;

CCamera::CCamera()
{
	m_fCurAz = 0.0f;
	m_fCurEl = 10.0f;
	m_fCurZoom = 120.0f;

	// Orbit
	m_fFirstAz = 0.0f;
	m_fFirstEl = 0.0f;
	m_bIsOrbit = FALSE;

	// Zoom
	m_fFirstZoom = 0.0f;
	m_bIsZoom = FALSE;

	m_fDefaultAz = m_fCurAz;
	m_fDefaultEl = m_fCurEl;
	m_fDefaultDist = m_fCurZoom;
	
	TERRAIN_CAM = FALSE;
}

CCamera::~CCamera()
{

}

void CCamera::SetOrbit(CPoint pt)
{
	// Start Orbit camera
	if(!m_bIsOrbit && !m_bIsZoom)// && pFrm->IsCursor())
	{
		m_FirstPt = pt;
		m_fFirstAz = m_fCurAz;
		m_fFirstEl = m_fCurEl;

		m_bIsOrbit = TRUE;
	}
	else
	{
		m_bIsOrbit = FALSE;
	}
}

void CCamera::SetZoom(CPoint pt)
{
	// Start Zoom
	if(!m_bIsZoom && !m_bIsOrbit)// && pFrm->IsCursor())
	{
		m_FirstPt = pt;
		m_fFirstZoom = m_fCurZoom;

		m_bIsZoom = TRUE;
	}
	else
	{
		m_bIsZoom = FALSE;
	}
}

void CCamera::SetOrbitCamera(CPoint pt)
{
	// Set Orbit Angle
	if(m_bIsOrbit)
	{
		// Set azmuth angle
		m_fCurAz = m_fFirstAz - float(pt.x - m_FirstPt.x) * ORBITSENS * mouse_sensitivity;
		// Set elevation angle
		m_fCurEl = m_fFirstEl + float(pt.y - m_FirstPt.y) * ORBITSENS * mouse_sensitivity;

		if(TERRAIN_CAM)
		{
			if(m_fCurEl < 1.0f)
				m_fCurEl = 1.0f;
			else if(m_fCurEl > 179.0f)
				m_fCurEl = 179.0f;
		}
	}
	// Set Zoom Distance
	else if(m_bIsZoom )
	{
		// Set zoom distance
		m_fCurZoom = m_fFirstZoom / pow( 2.0, (pt.y - m_FirstPt.y) / 200.0 );
		if( m_fCurZoom < 10.0) m_fCurZoom = 10.0;
	}
}
