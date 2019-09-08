#include "stdafx.h"
#include "Viewport.h"

Viewport::Viewport()
{
	m_enabled	= false;
}

Viewport::~Viewport()
{
}

//==============================( InitViewport )============================================
void
Viewport::OnAir()
{
	glViewport( m_posX, m_posY, m_frameWidth, m_frameHeight );
}

void
Viewport::GetViewportPosAndSize( int& xPos, int& yPos, int& width, int& height )
{
	xPos	= m_posX;
	yPos	= m_posY;
	width	= m_frameWidth;
	height	= m_frameHeight;
}

