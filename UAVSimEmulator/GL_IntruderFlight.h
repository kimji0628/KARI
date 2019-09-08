#pragma once
#include "easyopengl.h"

class CGL_IntruderFlight 	: public CEasyOpenGL
{
public:
	CGL_IntruderFlight(void);
	~CGL_IntruderFlight(void);

	void	DrawGridCircle(float cx, float cy, float fBasicRadius, float fSpace);
	void	Draw2DFlightTracks();
	void	Server();

};
