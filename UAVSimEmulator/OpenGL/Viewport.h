#if !defined(_VIEWPORT_H_INCLUDED_)
#define _VIEWPORT_H_INCLUDED_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string.h>
#include "Camera.h"

class Viewport : public Camera
{
public:
	int			m_posX;
	int			m_posY;

	double		m_xPosRatio;
	double		m_yPosRatio;
	double		m_widthRatio;
	double		m_heightRatio;

	int			m_enabled;
	int			m_iRenderContent;

public:
	char		m_name[64];

public:
	Viewport();
	~Viewport();

	void		OnAir();
	void		GetViewportPosAndSize( int& xPos, int& yPos, int& width, int& height );
};

#endif
