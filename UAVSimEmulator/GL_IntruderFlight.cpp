#include "StdAfx.h"
#include "GL_IntruderFlight.h"

CGL_IntruderFlight::CGL_IntruderFlight(void)
{
 

}

CGL_IntruderFlight::~CGL_IntruderFlight(void)
{
}




// 기준선 그리기

void	CGL_IntruderFlight::DrawGridCircle(float cx, float cy, float fBasicRadius, float fSpace)
{

	int		i;
	float	x,y;
	float	fR;
	float	fOuterRadius;

	// 원 그리기
	fOuterRadius = fBasicRadius + 2*fSpace;
	glColor3f(1.0f, 1.0f, 0.0f);
	for(fR=0; fR<= fOuterRadius; fR+=fSpace)
	{
		DrawCircle2D(cx, cy,0.0f, fR, 5, 0);
	}
	glColor3f(1.0f, .0f, 0.0f);
	DrawCircle2D(cx, cy,0.0f, fBasicRadius, 5, 0);
	
	// 방사 선 그리기
	glColor3f(1.0f, 1.0f, 0.0f);
	for(i=0;i<12;i++)
	{
		x= fOuterRadius* cos(i*30.0f*D2R);
		y= fOuterRadius* sin(i*30.0f*D2R);

		glBegin(GL_LINES);
			glVertex3f(0.0,0.0, 0.0f);
			glVertex3f(x,y, 0.0f);
		glEnd();    
	}
}




void	CGL_IntruderFlight::Draw2DFlightTracks()
{
	int	i;
	int nOption;
	double x0,y0;
	double x1,y1;
	double x2,y2;
	double x3,y3;
	float	fScreenMoveX;
	float	fScreenMoveY;
	glClearColor(0.0, 0.0, 0.0, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
	
	m_fAspectRatio = (float) m_nWndWidth/(float)(m_nWndHeight);

	//m_fScaleX = ( m_VScreenSize.x *m_fAspectRatio) / (m_nWndWidth);
	//m_fScaleY = m_VScreenSize.y / (m_nWndHeight);

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	//SetOrtho3DView ( -0.5*m_nWndWidth *m_fAspectRatio, 0.5*m_nWndWidth *m_fAspectRatio, -0.5*m_nWndHeight, 0.5*m_nWndHeight, -m_VScreenSize.y, m_VScreenSize.y);

	SetOrtho3DView ( -0.5*m_nWndWidth , 0.5*m_nWndWidth , -0.5*m_nWndHeight, 0.5*m_nWndHeight, -m_VScreenSize.y, m_VScreenSize.y);



//	SetZoomScale(EasyMouse.m_fWheel,1.0f, 100.0f); 

	//nOption = g_CSSSMaster.m_nMapOption;

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);

	
	glPushMatrix();
//		glScalef(m_fScreenZoomScale,m_fScreenZoomScale, 1.0f);
//		fScreenMoveX =  EasyMouse.m_fPanX*m_fScaleX/m_fScreenZoomScale;
//		fScreenMoveY =  EasyMouse.m_fPanY*m_fScaleY/m_fScreenZoomScale;
////		glTranslated(EasyMouse.m_fPanX*m_fScaleX/m_fScreenZoomScale, -EasyMouse.m_fPanY*m_fScaleY/m_fScreenZoomScale, 0.0);
//		glTranslated(fScreenMoveX, -fScreenMoveY, 0.0);


		DrawGridCircle(0,0, 100,20);

//		SurfaceGrid(5000.0, 10);
		glLineWidth(2);
		DrawOrigenAxisWithScale(5000.0, 10);
		glLineWidth(1);

		ShowMouseInput(1, 1, 1);
//		DrawACPosition();

	glPopMatrix();
}














void	
CGL_IntruderFlight::Server()
{

	int			nX, nY,  nGap;;
	int			nXStart = 10;
	int			nYStart = 20;


	char		strTmp[256];
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fScreenX = 1920, ScreenY = 1080;
//	float		fScreenX = 1920, ScreenY = 1080;
	float		fScaleX, fScaleY;
	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	int		w = GetCanvasWidth()	;
	int		h = GetCanvasHeight()	;

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, m_nWndWidth, 0.0 ,  m_nWndHeight);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);


	nGap = -20;

	nX = nXStart;

	nY = m_nWndHeight - nYStart;	


	glColor3f(1.0f, 0.0f, 0.0f);
	sprintf(strTmp,"===================  ADS_B GDL 90 Message Recv   ==============" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	Draw2DFlightTracks();

	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));
}

