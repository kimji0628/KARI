#pragma once
#include "easyopengl.h"


#define MAX_FLIGHT_TEST_AC	5


typedef struct {
	SIX_DOF	org;
	SIX_DOF	utm;
	SIX_DOF	wgd84;
} AC_POSITION_SMART;



class CGL_FlightTrack :
	public CEasyOpenGL
{

public:

	AC_POSITION_SMART   ACPos[MAX_FLIGHT_TEST_AC];

	int		m_nDrawType;
	int		m_nSymbolType; // 0 = 구, 1 = 화살표 
public:
	CGL_FlightTrack(void);
	~CGL_FlightTrack(void);

///  화살표 그리기
	void	DrawArrow3D(float x, float y, float z, float fDir, float fSize, float fScale); 
	void	DrawSphere3D(float x, float y, float z, float fMsnValue, float fSize, float fScale); 

	void	DrawDisplayTimeRange(void);
	void	Draw2DFlightTracks();
	void	Draw3DFlightTracks();

	void	SelectDrawType();

	void	SetACPosition();
	void	DrawACPosition();

	void	DrawAltRange(float	 btm, float top);

	void	SurfaceGrid(float	axis_size, int noScale);
	void	DrawFlightPaths(void);
	void	DrawTerrian();
	void	ShowDebugInformation();
	void	Server(void);
};
