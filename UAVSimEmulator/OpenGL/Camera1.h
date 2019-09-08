// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__E6A18237_B330_4ACC_9DEE_C64D8B6B7DAA__INCLUDED_)
#define AFX_CAMERA_H__E6A18237_B330_4ACC_9DEE_C64D8B6B7DAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ORBITSENS 0.01

class CCamera  
{
public:
	CCamera();
	virtual ~CCamera();

	void SetOrbit(CPoint pt);
	void SetZoom(CPoint pt);
	void SetOrbitCamera(CPoint pt);

	void SetCurrentAz(float fAz) { m_fCurAz = fAz; }
	void SetCurrentEl(float fEl) { m_fCurEl = fEl; }
	void SetCurrentDist(float fDist) { m_fCurZoom = fDist; }

	float GetCurrentAz() { return m_fCurAz; }
	float GetCurrentEl() { return m_fCurEl; }
	float GetCurrentDist() { return m_fCurZoom; }

	void SetDefaultAz(float fAz) { m_fDefaultAz = fAz; }
	void SetDefaultEl(float fEl) { m_fDefaultEl = fEl; }
	void SetDefaultDist(float fDist) { m_fDefaultDist = fDist; }

	float GetDefaultAz() { return m_fDefaultAz; }
	float GetDefaultEl() { return m_fDefaultEl; }
	float GetDefaultDist() { return m_fDefaultDist; }

	BOOL IsOrbit() { return m_bIsOrbit; }
	BOOL IsZoom() { return m_bIsZoom; }

	void SetTerrainCam(BOOL bIsTerrain) { TERRAIN_CAM  = bIsTerrain; }
	
private:
	// Camera
	CPoint m_FirstPt;
	float m_fCurAz;
	float m_fCurEl;
	float m_fCurZoom;

	// Orbit
	float m_fFirstAz;
	float m_fFirstEl;
	BOOL m_bIsOrbit;

	// Zoom
	float m_fFirstZoom;
	BOOL m_bIsZoom;

	float m_fDefaultAz;
	float m_fDefaultEl;
	float m_fDefaultDist;

	BOOL TERRAIN_CAM;
};

#endif // !defined(AFX_CAMERA_H__E6A18237_B330_4ACC_9DEE_C64D8B6B7DAA__INCLUDED_)

