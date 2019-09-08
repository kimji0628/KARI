#include "StdAfx.h"

#include "OpenGL/Texture.h"
#include "EasyOpenGL.h"

CEasyOpenGL	g_EasyGL;	




PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB		= NULL;		// 1 dimensional texture
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB		= NULL;		// 2 dimensional texture
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB		= NULL;		// 3 dimensional texture
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB		= NULL;		// 4 dimensional texture

PFNGLMULTITEXCOORD1FVARBPROC		glMultiTexCoord1fvARB		= NULL;		// 1 dimensional texture
PFNGLMULTITEXCOORD2FVARBPROC		glMultiTexCoord2fvARB		= NULL;		// 2 dimensional texture
PFNGLMULTITEXCOORD3FVARBPROC		glMultiTexCoord3fvARB		= NULL;		// 3 dimensional texture
PFNGLMULTITEXCOORD4FVARBPROC		glMultiTexCoord4fvARB		= NULL;		// 4 dimensional texture

PFNGLMULTITEXCOORD1DARBPROC		glMultiTexCoord1dARB		= NULL;		// 1 dimensional texture
PFNGLMULTITEXCOORD2DARBPROC		glMultiTexCoord2dARB		= NULL;		// 2 dimensional texture
PFNGLMULTITEXCOORD3DARBPROC		glMultiTexCoord3dARB		= NULL;		// 3 dimensional texture
PFNGLMULTITEXCOORD4DARBPROC		glMultiTexCoord4dARB		= NULL;		// 4 dimensional texture

PFNGLMULTITEXCOORD1DVARBPROC		glMultiTexCoord1dvARB		= NULL;		// 1 dimensional texture
PFNGLMULTITEXCOORD2DVARBPROC		glMultiTexCoord2dvARB		= NULL;		// 2 dimensional texture
PFNGLMULTITEXCOORD3DVARBPROC		glMultiTexCoord3dvARB		= NULL;		// 3 dimensional texture
PFNGLMULTITEXCOORD4DVARBPROC		glMultiTexCoord4dvARB		= NULL;		// 4 dimensional texture

PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB			= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC		glClientActiveTextureARB	= NULL;


CEasyOpenGL::CEasyOpenGL(void)
{

	m_nTexture = 0;
	m_nNoDynMapTex =0;
	m_nNoDDSPatch =0;

	EasyMouse.m_fWheel = 50.0f;

	m_fScreenZoomScale = 2.0f;
	m_VScreenSize.x = SCREEN_WIDTH;
	m_VScreenSize.y = SCREEN_HEIGHT;


	m_fFOV = 45.0f;
	m_fNearClippingDistance = 1.0f;
	m_fFarClippingDistance  = 1000000.0f;

	EasyMouse.m_fDistance = 1000.0f;
	EasyMouse.m_fIncidence = 45.0f;
	EasyMouse.m_fAzimuth = 0.0f;

	m_nViewMode = ORTHO_MODE;






}

CEasyOpenGL::~CEasyOpenGL(void)
{
}



void CEasyOpenGL::KCEICreate(HWND hWnd)
{
	int nPixelFormat;

	m_hGLWnd = hWnd;
	m_hGLDC = ::GetDC(m_hGLWnd);

	//*
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(	PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,
		0,0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	}; // */

	nPixelFormat = ChoosePixelFormat(m_hGLDC, &pfd);
	SetPixelFormat(m_hGLDC, nPixelFormat, &pfd);
	m_hGLRC = wglCreateContext(m_hGLDC);

	wglMakeCurrent(m_hGLDC, m_hGLRC);
	KCEIOnCreate();
	wglMakeCurrent(m_hGLDC, NULL);
}

int
CEasyOpenGL::Open( HWND hWnd, int colorDepth, int width, int height, int nofViewport )
{
	unsigned int	PixelFormat;			// Holds The Results After Searching For A Match

	m_hGLWnd		= hWnd;
	m_nWndWidth			= width;
	m_nWndHeight		= height;

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		(unsigned char)colorDepth,					// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 16Bit Z-Buffer (Depth Buffer)  
		1,											// Use One Stencil Buffer 
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	m_hGLDC=GetDC(hWnd);
	if ( !m_hGLDC )									// Did We Get A Device Context?
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	PixelFormat=ChoosePixelFormat( m_hGLDC, &pfd );
	if ( !PixelFormat )								// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if( !SetPixelFormat( m_hGLDC, PixelFormat, &pfd ) )	// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	m_hGLRC=wglCreateContext( m_hGLDC );
	if ( !m_hGLRC )									// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if( !wglMakeCurrent( m_hGLDC, m_hGLRC ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	wglMakeCurrent( m_hGLDC, NULL ) ;
//	wglDeleteContext(m_hGLRC);

	/*

	ShowWindow( hWnd, SW_SHOW );					// Show The Window
	SetForegroundWindow( hWnd );					// Slightly Higher Priority
	SetFocus( hWnd );								// Sets Keyboard Focus To The Window
	ResizeRC( m_width, m_height );					// Set Up Our Perspective GL Screen

//	glClearDepth( 1.0 );		   					// Optional Depth Buffer Setup (0.0 ~ 1.0)


	m_maxViewport	= nofViewport;
//	m_viewport		= new Viewport[ m_maxViewport ];

	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC) wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC) wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC) wglGetProcAddress("glMultiTexCoord4fARB");

	glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC) wglGetProcAddress("glMultiTexCoord1fvARB");
	glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) wglGetProcAddress("glMultiTexCoord2fvARB");
	glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC) wglGetProcAddress("glMultiTexCoord3fvARB");
	glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC) wglGetProcAddress("glMultiTexCoord4fvARB");

	glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC) wglGetProcAddress("glMultiTexCoord1dARB");
	glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC) wglGetProcAddress("glMultiTexCoord2dARB");
	glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC) wglGetProcAddress("glMultiTexCoord3dARB");
	glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC) wglGetProcAddress("glMultiTexCoord4dARB");

	glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC) wglGetProcAddress("glMultiTexCoord1dvARB");
	glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC) wglGetProcAddress("glMultiTexCoord2dvARB");
	glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC) wglGetProcAddress("glMultiTexCoord3dvARB");
	glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC) wglGetProcAddress("glMultiTexCoord4dvARB");

	glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");

*/
	return true;
}
void	CEasyOpenGL::SetRC()
{
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f );
	glPolygonMode(GL_FRONT_AND_BACK,GL_POLYGON);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
//////////////////////////////////////////////
//	함 수 명 : 	ShowInformation								
//	설    명 :	선택된 화면에 서 표시하고 싶은 디지털 데이터 표시 
//	입력인수 :	전체 폼뷰의 창에서의 화면이 위치하여야 할 좌표 
//			int btmX : 좌측 하단  X 좌표 
//			int	btmY : 좌측 하단 Y 좌표
//			int	width : 창 폭 
//			int	height : 창 높이 
//			int wnd_id	: 창 종류 
//
//  출력인수 :  없음 				
// 	함수출력 :	멤버변수 중에 필요한 변수 표시    
//  제 작 자 :  김주일  
//  제 작 일 :  2016.7  
//  수정기록 : 

void	CEasyOpenGL::Printf(int	x, int y, char *str, int nFontID)
{
	glRasterPos2i(x,y);
	m_CFont[nFontID].glPrint(str);
}


void CEasyOpenGL::Printf3D(int	x, int y, int z, char *str, int nFontID)
{
	glRasterPos3i(x,y,z);
	m_CFont[nFontID].glPrint(str);

}






























//
////////////////////////////////////////////////////

void	CEasyOpenGL::SetOrtho3DView(float	left_x, float	right_x, float	btm_y, float	top_y, float near_z, float far_z)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left_x, right_x,btm_y, top_y, near_z, far_z);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int
CEasyOpenGL::ViewportName2ID( char* name )
{
/*
	for ( int i = 0; i < m_nofViewport; i++ )
	{
		if ( _stricmp( m_viewport[i].m_name, name ) == 0 )
			return i;
	}
*/
	return -1;
}

int
CEasyOpenGL::NewViewport( char* name )
{
	int i;
/*
	for ( int i = 0; i < m_nofViewport; i++ )
	{
		if ( _stricmp( m_viewport[i].m_name, name ) == 0 )
		{
			cLog.LogExit( "Viewport %s already exist!\n", name );
		}
	}

	if ( i >= m_maxViewport )
	{
		cLog.LogExit( "Viewport overflows at %s!\n", name );
	}

	m_nofViewport	= i + 1;
	strcpy( m_viewport[i].m_name, name );
*/
	return i;
}

int
CEasyOpenGL::AddViewport( char* viewportName, double xPos, double yPos, double width, double height )
{
	int		vNo;
/*
	int		vNo = NewViewport( viewportName );

	m_viewport[vNo].m_xPosRatio		= xPos;
	m_viewport[vNo].m_yPosRatio		= yPos;
	m_viewport[vNo].m_widthRatio	= width;
	m_viewport[vNo].m_heightRatio	= height;

	m_viewport[vNo].m_posX			= (int)( m_width  * xPos   / 100.0 );
	m_viewport[vNo].m_posY			= (int)( m_height * yPos   / 100.0 );
	m_viewport[vNo].m_frameWidth	= (int)( m_width  * width  / 100.0 );
	m_viewport[vNo].m_frameHeight	= (int)( m_height * height / 100.0 );
*/
	return vNo;
}

void
CEasyOpenGL::ResizeRC( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
{
	m_nWndWidth		= width;
	m_nWndHeight	= height;
	m_fCenterX = m_nWndWidth/2.0f;
	m_fCenterY = m_nWndHeight/2.0f;

/*
	for ( int vNo = 0; vNo < m_nofViewport; vNo++ )
	{
		m_viewport[vNo].m_posX			= (int)( m_width  * m_viewport[vNo].m_xPosRatio		/ 100.0 );
		m_viewport[vNo].m_posY			= (int)( m_height *  m_viewport[vNo].m_yPosRatio	/ 100.0 );
		m_viewport[vNo].m_frameWidth	= (int)( m_width  *  m_viewport[vNo].m_widthRatio	/ 100.0 );
		m_viewport[vNo].m_frameHeight	= (int)( m_height *  m_viewport[vNo].m_heightRatio	/ 100.0 );
	}
*/
}


int
CEasyOpenGL::SetViewport( char* viewportName, double xPos, double yPos, double width, double height )
{
	int		vNo = ViewportName2ID( viewportName );

	if ( vNo < 0 )
		return vNo;
/*
	m_viewport[vNo].m_xPosRatio		= xPos;
	m_viewport[vNo].m_yPosRatio		= yPos;
	m_viewport[vNo].m_widthRatio	= width;
	m_viewport[vNo].m_heightRatio	= height;

	m_viewport[vNo].m_posX			= (int)( m_width  * xPos   / 100.0 );
	m_viewport[vNo].m_posY			= (int)( m_height * yPos   / 100.0 );
	m_viewport[vNo].m_frameWidth	= (int)( m_width  * width  / 100.0 );
	m_viewport[vNo].m_frameHeight	= (int)( m_height * height / 100.0 );
*/
	return vNo;
}


void	CEasyOpenGL::SetCanvas(RECT *rect)
{
	m_wndRect.bottom = rect->bottom;
	m_wndRect.top	= rect->top;
	m_wndRect.right	= rect->right;
	m_wndRect.left	= rect->left;



	m_nWndWidth = (m_wndRect.right - m_wndRect.left);
	m_nWndHeight =  (m_wndRect.bottom - m_wndRect.top);

	m_fAspectRatio = (float) m_nWndWidth / (float) m_nWndHeight;

	m_nCenterX = m_nWndWidth/2;
	m_nCenterY = m_nWndHeight/2;

//	m_nSpaceX = 10;
//	m_nSpaceY = 10;

//	m_fScaleX =float( m_nWndWidth / ((m_fMaxX - m_fMinX) * m_fAspectRatio));
//	m_fScaleY =float( m_nWndHeight / (m_fMaxY - m_fMinY));

}


void
CEasyOpenGL::OnAirViewport( int viewportID )
{
	m_onAirViewport	= viewportID;

//	m_viewport[m_onAirViewport].OnAir();
}

void
CEasyOpenGL::EnableViewport( int viewportID )
{
//	m_viewport[viewportID].m_enabled	= true;
}

void
CEasyOpenGL::DisableViewport( int viewportID )
{
//	m_viewport[viewportID].m_enabled	= false;
}

void
CEasyOpenGL::Activate()
{
	if( !wglMakeCurrent( m_hGLDC, m_hGLRC ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
}

void
CEasyOpenGL::Inactivate()
{
	if( !wglMakeCurrent( NULL, NULL ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Inactivate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
}

void
CEasyOpenGL::Close()
{
	if (m_hGLRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hGLRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hGLRC=NULL;										// Set RC To NULL
	}
}


void	CEasyOpenGL::SetColor(int r,int g, int b)
{
	glColor3ub((GLubyte) r, (GLubyte) g, (GLubyte) b);
}

float ColorIndexACAD[300][3] = {
0.0,	0.0,	0.0,			//  BLACK	0
1.0,	0.0,	0.0,			//	RED		1
1.0,	1.0,	0.0,			//	YELLOW	2
0.0,	1.0,	0.0,			//	GREEN	3
0.0,	1.0,	1.0,			//			4
0.0,	0.0,	1.0,			//	BLUE	5
1.0,	0.0,	1.0,			//			6
1.0,	1.0,	1.0,			//	WHITE
0.3,	0.3,	0.3,			//			8
0.6,	0.6,0.6,
0.996,	0.0,0.0,				//	10
0.996,	0.496,0.496,
0.797,	0.0,0.0,
0.797,	0.398,0.398,
0.598,	0.0,0.0,
0.598,	0.297,0.297,
0.496,	0.0,0.0,
0.496,	0.246,0.246,
0.297,	0.0,0.0,
0.297,	0.148,0.148,
0.996,	0.246,0.0,			// 20
0.996,	0.621,0.496,
0.797,	0.199,0.0,
0.797,	0.496,0.398,
0.598,	0.148,0.0,
0.598,	0.371,0.297,
0.496,	0.121,0.0,
0.496,	0.309,0.246,
0.297,	0.074,0.0,
0.297,	0.184,0.148,
0.996,	0.496,0.0,			//  30
0.996,	0.746,0.496,
0.797,	0.398,0.0,
0.797,	0.598,0.398,
0.598,	0.297,0.0,
0.598,	0.445,0.297,
0.496,	0.246,0.0,
0.496,	0.371,0.246,
0.297,	0.148,0.0,
0.297,	0.223,0.148,
0.996,	0.746,0.0,			// 40
0.996,	0.871,0.496,
0.797,	0.598,0.0,
0.797,	0.695,0.398,
0.598,	0.445,0.0,
0.598,	0.52,0.297,
0.496,	0.371,0.0,
0.496,	0.434,0.246,
0.297,	0.223,0.0,
0.297,	0.258,0.148,
0.996,	0.996,0.0,			// 50
0.996,	0.996,0.496,
0.797,	0.797,0.0,
0.797,	0.797,0.398,
0.598,	0.598,0.0,
0.598,	0.598,0.297,
0.496,	0.496,0.0,
0.496,	0.496,0.246,
0.297,	0.297,0.0,
0.297,	0.297,0.148,
0.746,	0.996,0.0,			//  60
0.871,	0.996,0.496,
0.598,	0.797,0.0,
0.695,	0.797,0.398,
0.445,	0.598,0.0,
0.52,	0.598,0.297,
0.371,	0.496,0.0,
0.434,	0.496,0.246,
0.223,	0.297,0.0,
0.258,	0.297,0.148,
0.496,	0.996,0.0,			//  70
0.746,	0.996,0.496,
0.398,	0.797,0.0,
0.598,	0.797,0.398,
0.297,	0.598,0.0,
0.445,	0.598,0.297,
0.246,	0.496,0.0,
0.371,	0.496,0.246,
0.148,	0.297,0.0,
0.223,	0.297,0.148,
0.246,	0.996,0.0,			// 80
0.621,	0.996,0.496,
0.199,	0.797,0.0,
0.496,	0.797,0.398,
0.148,	0.598,0.0,
0.371,	0.598,0.297,
0.121,	0.496,0.0,
0.309,	0.496,0.246,
0.074,	0.297,0.0,
0.184,	0.297,0.148,
0.0,	0.996,0.0,				// 90
0.496,	0.996,0.496,
0.0,	0.797,0.0,
0.398,	0.797,0.398,
0.0,	0.598,0.0,
0.297,	0.598,0.297,
0.0,	0.496,0.0,
0.246,	0.496,0.246,
0.0,	0.297,0.0,
0.148,	0.297,0.148,
0.0,	0.996,0.246,				//  100
0.496,	0.996,0.621,
0.0,	0.797,0.199,
0.398,	0.797,0.496,
0.0,	0.598,0.148,
0.297,	0.598,0.371,
0.0,	0.496,0.121,
0.246,0.496,0.309,
0.0,	0.297,0.074,
0.148,	0.297,0.184,
0.0,	0.996,0.496,				//  110
0.496,	0.996,0.746,
0.0,	0.797,0.398,
0.398,	0.797,0.598,
0.0,	0.598,0.297,
0.297,	0.598,0.445,
0.0,	0.496,0.246,
0.246,	0.496,0.371,
0.0,	0.297,0.148,
0.148,	0.297,0.223,
0.0,	0.996,0.746,				// 120
0.496,	0.996,0.871,
0.0,	0.797,0.598,
0.398,	0.797,0.695,
0.0,	0.598,0.445,
0.297,	0.598,0.52,
0.0,	0.496,0.371,
0.246,	0.496,0.434,
0.0,	0.297,0.223,
0.148,	0.297,0.258,
0.0,	0.996,0.996,				// 130
0.496,	0.996,0.996,
0.0,	0.797,0.797,
0.398,	0.797,0.797,
0.0,	0.598,0.598,
0.297,	0.598,0.598,
0.0,	0.496,0.496,
0.246,	0.496,0.496,
0.0,	0.297,0.297,
0.148,	0.297,0.297,
0.0,	0.746,0.996,				// 140
0.496,	0.871,0.996,
0.0,	0.598,0.797,
0.398,	0.695,0.797,
0.0,	0.445,0.598,
0.297,	0.52,0.598,
0.0,	0.371,0.496,
0.246,	0.434,0.496,
0.0,	0.223,0.297,
0.148,	0.258,0.297,
0.0,	0.496,0.996,				//  150
0.496,	0.746,0.996,
0.0,	0.398,0.797,
0.398,	0.598,0.797,
0.0,	0.297,0.598,
0.297,	0.445,0.598,
0.0,	0.246,0.496,
0.246,	0.371,0.496,
0.0,	0.148,0.297,
0.148,	0.223,0.297,
0.0,	0.246,0.996,				// 160
0.496,	0.621,0.996,
0.0,	0.199,0.797,
0.398,	0.496,0.797,
0.0,	0.148,0.598,
0.297,	0.371,0.598,
0.0,	0.121,0.496,
0.246,	0.309,0.496,
0.0,	0.074,0.297,
0.148,	0.184,0.297,
0.0,	0.0,0.996,					// 170
0.496,	0.496,0.996,
0.0,	0.0,0.797,
0.398,	0.398,0.797,
0.0,	0.0,0.598,
0.297,	0.297,0.598,
0.0,	0.0,0.496,
0.246,	0.246,0.496,
0.0,	0.0,0.297,
0.148,	0.148,0.297,
0.246,	0,0.996,				//180
0.621,	0.496,0.996,
0.199,	0.0,0.797,
0.496,	0.398,0.797,
0.148,	0.0,0.598,
0.371,	0.297,0.598,
0.121,	0.0,0.496,
0.309,	0.246,0.496,
0.074,	0.0,0.297,
0.184,	0.148,0.297,
0.496,	0.0,0.996,			//  190
0.746,	0.496,0.996,
0.398,	0.0,0.797,
0.598,	0.398,0.797,
0.297,	0.0,0.598,
0.445,	0.297,0.598,
0.246,	0.0,0.496,
0.371,	0.246,0.496,
0.148,	0.0,0.297,
0.223,	0.148,0.297,
0.746,	0.0,0.996,			// 200
0.871,	0.496,0.996,
0.598,	0.0,0.797,
0.695,	0.398,0.797,
0.445,	0.0,0.598,
0.52,	0.297,0.598,
0.371,	0.0	,0.496,
0.434,	0.246,0.496,
0.223,	0.0,0.297,
0.258,	0.148,0.297,
0.996,	0,0.996,		// 210
0.996,	0.496,0.996,
0.797,	0.0,0.797,
0.797,	0.398,0.797,
0.598,	0.0,0.598,
0.598,	0.297,0.598,
0.496,	0.0,0.496,
0.496,	0.246,0.496,
0.297,	0.0,0.297,
0.297,	0.148,0.297,
0.996,	0.0,0.746,			//220
0.879,	0.496,0.871,
0.797,	0.0,0.598,
0.797,	0.398,0.695,
0.598,	0,0.445,
0.598,	0.297,0.52,
0.496,	0.0,0.371,
0.496,	0.246,0.434,
0.297,	0.0,0.223,
0.297,	0.148,0.258,
0.996,	0.0,0.496,		// 230
0.879,	0.496,0.746,
0.797,	0.0,0.398,
0.797,	0.398,0.598,
0.598,	0.0,0.297,
0.598,	0.297,0.445,
0.496,	0.0,0.246,
0.496,	0.246,0.371,
0.297,	0.0,0.148,
0.297,	0.148,0.223,
0.996,	0,0.246,				//240
0.879,	0.496,0.621,
0.797,	0,0.199,
0.797,	0.398,0.496,
0.598,	0.0,0.148,
0.598,	0.297,0.371,
0.496,	0.0,0.121,
0.496,	0.246,0.309,
0.297,	0.0,0.074,
0.297,	0.148,0.184,
};

void	CEasyOpenGL::SetColor(int color_id)
{
	if( color_id == 230)
	{
		glColor3f( 0.996,	0.0,0.496);		
	}
	else
		glColor3fv( ColorIndexACAD[color_id]);	
}


void CEasyOpenGL::DrawCircle2D(GLfloat x, GLfloat y,  GLfloat z, GLfloat r, int n, int option)
{
	int i;
	float	t_x,t_y;
	float	i_x, i_y;

	float	a_x, a_y;

	if(option == 0)
		glBegin(GL_LINE_STRIP);
	else
		glBegin(GL_POLYGON);
			for (i=0;i<360;i+=n)
			{
				t_x = (float)(x + r * cos(i*D2R));
				t_y = (float)(y + r * sin(i*D2R));
				glVertex3f(t_x,t_y, z);
			}
			t_x = (float)(x + r * cos(i*D2R));
			t_y = (float)(y + r * sin(i*D2R));
			glVertex3f(t_x,t_y, z);
		glEnd();
}

void CEasyOpenGL::DrawCircle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat azimuth, GLfloat incidence, GLfloat r, int n, int option)
{
	int i;
	float	t_x,t_y, t_z;
	float	i_x, i_y, i_z;

	float	a_x, a_y, a_z;

	if(option == 0) 	glBegin(GL_LINE_STRIP);
	else 	glBegin(GL_POLYGON);
	for (i=0;i<360;i+=n)
	{

		t_x = (float)(x + r * cos(i*D2R));
		t_y = (float)(y + r * sin(i*D2R));
		t_z = (float)(0.0f);
		i_x = t_x * cos(incidence * D2R) - t_z * sin(incidence * D2R);
		i_y = t_y;
		i_z = t_x * sin(incidence * D2R) + t_z * cos(incidence * D2R);
		a_x = i_x * cos(azimuth * D2R) - i_y * sin(azimuth * D2R);
		a_y = i_x * sin(azimuth * D2R) + i_y * cos(azimuth * D2R); ;
		a_z = i_z;
		glVertex3f(a_x,a_y, a_z);

	}
	t_x = (float)(x + r * cos(i*D2R));
	t_y = (float)(y + r * sin(i*D2R));
	t_y = (float)(0.0f);
	i_x = t_x * cos(incidence * D2R) - t_z * sin(incidence * D2R);
	i_y = t_y;
	i_z = t_x * sin(incidence * D2R) + t_z * cos(incidence * D2R);
	a_x = i_x * cos(azimuth * D2R) - i_y * sin(azimuth * D2R);
	a_y = i_x * sin(azimuth * D2R) + i_y * cos(azimuth * D2R); ;
	a_z = i_z;
	glVertex3f(a_x,a_y, a_z);
	glEnd();
}

void CEasyOpenGL::DrawLine(float xs, float ys, float zs, float xe, float ye, float ze)
{
	glBegin(GL_LINES);
		glVertex3f(xs,ys, zs);	
		glVertex3f(xe,ye, ze);	
	glEnd();
}




void	CEasyOpenGL::Draw2DBox(GLfloat x, GLfloat y, GLfloat w, GLfloat h, int option)
{
	if(option == 0)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(x,y+h, 1.0f);
			glVertex3f(x+w,y+h, 1.0f);
			glVertex3f(x+w,y, 1.0f);
			glVertex3f(x, y, 1.0f);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
			glVertex3f(x,y+h, 1.0f);
			glVertex3f(x+w,y+h, 1.0f);
			glVertex3f(x+w,y, 1.0f);
			glVertex3f(x, y, 1.0f);
		glEnd();
	}
}

void	CEasyOpenGL::Draw2DBoxWithLabel(GLfloat x, GLfloat y, GLfloat w, GLfloat h, int option,char ch[])
{
	if(option == 0)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(x,y+h, 1.0f);
			glVertex3f(x+w,y+h, 1.0f);
			glVertex3f(x+w,y, 1.0f);
			glVertex3f(x, y, 1.0f);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
			glVertex3f(x,y+h, 1.0f);
			glVertex3f(x+w,y+h, 1.0f);
			glVertex3f(x+w,y, 1.0f);
			glVertex3f(x, y, 1.0f);
		glEnd();
	}
	

	glColor3f(0.0f, 0.0f, 0.0f);

	Printf3D(x+10, y+5 ,0.0f, ch, SMALL_FONT);


}


void	CEasyOpenGL::Draw2DRect(GLfloat lbx, GLfloat lby, GLfloat rtx, GLfloat rty, int option)
{
	if(option == 0)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(lbx,lby, 1.0f);
			glVertex3f(rtx,lby, 1.0f);
			glVertex3f(rtx,rty, 1.0f);
			glVertex3f(lbx, rty, 1.0f);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
			glVertex3f(lbx,lby, 1.0f);
			glVertex3f(rtx,lby, 1.0f);
			glVertex3f(rtx,rty, 1.0f);
			glVertex3f(lbx, rty, 1.0f);
		glEnd();
	}
}

void CEasyOpenGL::DrawOrigenAxis(float	axis_size)
{
	float	origin[3];
	float	v_line[3];

	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;
	glRGB(255,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[0] = axis_size;
		v_line[1] = 0.0;
		v_line[2] = 0.0;
		glVertex3fv(v_line);	
	glEnd();
	glRGB(255,255,0);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[0] = 0.0;
		v_line[1] = axis_size;
		glVertex3fv(v_line);	
	glEnd();
	glRGB(0,0,255);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[1] = 0.0;
		v_line[2] = axis_size;
		glVertex3fv(v_line);	
	glEnd();
}


///////////////////////////////////////////////
//	함 수 명 : 	DrawOrigenAxisWithScale								
//	설    명 :	3D 공간 좌표축 그리기 	원점을 중심으로 3 축에 대한 스케일을 정해진 간격으로 그림
//	입력인수 :	 	
//  출력인수 :  없음 				
// 	함수출력 :	
//  제 작 자 :  김주일  
//  제 작 일 :  2019.1.11  
//  관리번호 :  xxxxx.xxxx.xxxx.xxxxx

void CEasyOpenGL::DrawOrigenAxisWithScale(float	axis_size, int noScale)
{
	float	origin[3];
	float	v_line[3];
	float	fSize;
	float	f;
	int		i,j;
	char		strTmp[256];

	sprintf(strTmp,"%.0f",axis_size);

	fSize = axis_size / noScale;

	//  x 축
	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;
	glRGB(255,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[0] = axis_size;
		v_line[1] = 0.0;
		v_line[2] = 0.0;
		glVertex3fv(v_line);	
	glEnd();

	for(f=0.0;f < axis_size; f+= fSize)
	{
		glBegin(GL_LINES);
			glVertex3f(f,-10.0f, 0.0f);	
			glVertex3f(f,10.0f, 0.0f);	
		glEnd();
	}

	Printf3D(axis_size, 0.0f,0.0f, strTmp, MIDDLE_FONT);


	glRGB(255,255,0);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[0] = 0.0;
		v_line[1] = axis_size;
		glVertex3fv(v_line);	
	glEnd();

	for(f=0.0;f < axis_size; f+= fSize)
	{
		glBegin(GL_LINES);
			glVertex3f(-10.0f, f, 0.0f);	
			glVertex3f(10.0f, f, 0.0f);	
		glEnd();
	}

	Printf3D(0.0f,axis_size, 0.0f, strTmp, MIDDLE_FONT);





	glRGB(0,0,255);
	glBegin(GL_LINE_STRIP);
		glVertex3fv(origin);	
		v_line[1] = 0.0;
		v_line[2] = axis_size;
		glVertex3fv(v_line);	
	glEnd();

	for(f=0.0;f < axis_size; f+= fSize)
	{
		glBegin(GL_LINES);
			glVertex3f(-10.0f, 0.0, f);	
			glVertex3f(10.0f, 0.0, f);	
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(0.0f, -10.0, f);	
			glVertex3f(0.0f, 10.0, f);	
		glEnd();


	}
	Printf3D(0.0f,0.0f,axis_size,  strTmp, MIDDLE_FONT);


}



void CEasyOpenGL::Draw3DCoordinate( float length, float width,  
		int x_color, int y_color, int z_color, char x_name[], char y_name[], char z_name[])
{
	float	vtx[13][3];
	float	w = width/2.0f;
	vtx[0][0] = 0.0f; vtx[0][1] = w; 	vtx[0][2] = w; 
	vtx[1][0] = 0.0f; vtx[1][1] = -w; 	vtx[1][2] = w; 
	vtx[2][0] = 0.0f; vtx[2][1] = -w; 	vtx[2][2] = -w; 
	vtx[3][0] = 0.0f; vtx[3][1] = w; 	vtx[3][2] = -w; 
	vtx[4][0] = length; vtx[4][1] = w; 	vtx[4][2] = w; 
	vtx[5][0] = length; vtx[5][1] = -w; vtx[5][2] = w; 
	vtx[6][0] = length; vtx[6][1] = -w; vtx[6][2] = -w; 
	vtx[7][0] = length; vtx[7][1] = w; 	vtx[7][2] = -w; 
	vtx[8][0] = length ; vtx[8][1] =  width*1.5f; 	vtx[8][2] = width*1.5f; 
	vtx[9][0] = length; vtx[9][1] = - width*1.5f; vtx[9][2] = width*1.5f; 
	vtx[10][0] = length; vtx[10][1] = -width*1.5f; vtx[10][2] = -width*1.5f; 
	vtx[11][0] = length; vtx[11][1] = width*1.5f; 	vtx[11][2] = -width*1.5f; 
	vtx[12][0] = length+ width*1.5f; vtx[12][1] = 0.0f; 	vtx[12][2] = 0.0f; 
	glPushMatrix();

		SetColor(x_color);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[0]);	
			glVertex3fv(vtx[4]);	
			glVertex3fv(vtx[7]);	
			glVertex3fv(vtx[3]);		
		glEnd();
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[1]);	
			glVertex3fv(vtx[5]);	
			glVertex3fv(vtx[4]);	
			glVertex3fv(vtx[0]);		
		glEnd();
		glNormal3f(0.0f, -1.0f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[2]);	
			glVertex3fv(vtx[6]);	
			glVertex3fv(vtx[5]);	
			glVertex3fv(vtx[1]);		
		glEnd();
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[3]);	
			glVertex3fv(vtx[7]);	
			glVertex3fv(vtx[6]);	
			glVertex3fv(vtx[2]);		
		glEnd();

		SetColor(x_color);
		glNormal3f(0.707f, 0.707f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[8]);	
			glVertex3fv(vtx[12]);	
			glVertex3fv(vtx[11]);	
		glEnd();
		SetColor(WHITE);
		glNormal3f(0.707f, 0.0f, 0.707f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[9]);	
			glVertex3fv(vtx[12]);	
			glVertex3fv(vtx[8]);	
		glEnd();
		SetColor(x_color);
		glNormal3f(0.707f, -0.707f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[10]);	
			glVertex3fv(vtx[12]);	
			glVertex3fv(vtx[9]);	
		glEnd();
		SetColor(WHITE);
		glNormal3f(0.707f, 0.0f, -0.707f);
		glBegin(GL_POLYGON);
			glVertex3fv(vtx[11]);	
			glVertex3fv(vtx[12]);	
			glVertex3fv(vtx[10]);	
		glEnd();

		glPushMatrix();
			glRotatef(90.0f, 0.0, 0.0, 1.0f);
			SetColor(y_color);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[0]);	
				glVertex3fv(vtx[4]);	
				glVertex3fv(vtx[7]);	
				glVertex3fv(vtx[3]);		
			glEnd();
			glNormal3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[1]);	
				glVertex3fv(vtx[5]);	
				glVertex3fv(vtx[4]);	
				glVertex3fv(vtx[0]);		
			glEnd();
			glNormal3f(0.0f, -1.0f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[2]);	
				glVertex3fv(vtx[6]);	
				glVertex3fv(vtx[5]);	
				glVertex3fv(vtx[1]);		
			glEnd();
			glNormal3f(0.0f, 0.0f, -1.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[3]);	
				glVertex3fv(vtx[7]);	
				glVertex3fv(vtx[6]);	
				glVertex3fv(vtx[2]);		
			glEnd();
			SetColor(y_color);
			glNormal3f(0.707f, 0.707f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[8]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[11]);	
			glEnd();
			SetColor(WHITE);
			glNormal3f(0.707f, 0.0f, 0.707f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[9]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[8]);	
			glEnd();
			SetColor(y_color);
			glNormal3f(0.707f, -0.707f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[10]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[9]);	
			glEnd();
			SetColor(WHITE);
			glNormal3f(0.707f, 0.0f, -0.707f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[11]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[10]);	
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90.0f, 0.0, 1.0, 0.0f);
			SetColor(z_color);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[0]);	
				glVertex3fv(vtx[4]);	
				glVertex3fv(vtx[7]);	
				glVertex3fv(vtx[3]);		
			glEnd();
			glNormal3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[1]);	
				glVertex3fv(vtx[5]);	
				glVertex3fv(vtx[4]);	
				glVertex3fv(vtx[0]);		
			glEnd();
			glNormal3f(0.0f, -1.0f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[2]);	
				glVertex3fv(vtx[6]);	
				glVertex3fv(vtx[5]);	
				glVertex3fv(vtx[1]);		
			glEnd();
			glNormal3f(0.0f, 0.0f, -1.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[3]);	
				glVertex3fv(vtx[7]);	
				glVertex3fv(vtx[6]);	
				glVertex3fv(vtx[2]);		
			glEnd();
			SetColor(z_color);
			glNormal3f(0.707f, 0.707f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[8]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[11]);	
			glEnd();
			SetColor(WHITE);
			glNormal3f(0.707f, 0.0f, 0.707f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[9]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[8]);	
			glEnd();
			SetColor(z_color);
			glNormal3f(0.707f, -0.707f, 0.0f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[10]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[9]);	
			glEnd();
			SetColor(WHITE);
			glNormal3f(0.707f, 0.0f, -0.707f);
			glBegin(GL_POLYGON);
				glVertex3fv(vtx[11]);	
				glVertex3fv(vtx[12]);	
				glVertex3fv(vtx[10]);	
			glEnd();
		glPopMatrix();
	glPopMatrix();
}

void	CEasyOpenGL::SetPerspectiveView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, m_fAspectRatio,m_fNearClippingDistance, m_fFarClippingDistance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	
CEasyOpenGL::InitParameters()
{
	m_fFOV = 60.0f;
	m_fNearClippingDistance = 1.0f;
	m_fFarClippingDistance  = 40000.0f;

}

void	
CEasyOpenGL::RenderOnViewport()
{
	glViewport(0, 0 , m_nWndWidth, m_nWndHeight);
	m_fAspectRatio = (float) m_nWndWidth/(float)(m_nWndHeight);
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);


	

	SetPerspectiveView();
//	SetOrtho3DView ( l_long, r_long, b_lat,t_lat, -1800.0f, 1800.0f);


	glClearColor(0.0f, 1.0f, 1.0f, 0.0f );

	SetColor(WHITE);
	DrawOrigenAxis(100.0f);

}






void CEasyOpenGL::KCEIOnCreate()
{

	m_CFont[SMALL_FONT].BuildFont(m_hGLDC, "Arial", 12, FW_BOLD, 0 );
	m_CFont[MIDDLE_FONT].BuildFont(m_hGLDC, "Arial", 16, FW_BOLD, 0 );
	m_CFont[LARGE_FONT].BuildFont(m_hGLDC, "Arial", 20, FW_BOLD, 0 );
	//CGLEXTFunc::GetInstance()->Process();

	/*
	m_font.init("../../../../resource/font/malgun.ttf");
	setFontSize(m_fontSize);
	setFontColor(m_fontColorR, m_fontColorG, m_fontColorB, m_fontColorA);

	m_2D.init();

	m_nowFrame = 0;
	m_frame = 0;
	m_startTime = GetTickCount();
	*/
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


void	CEasyOpenGL::ReadMapTextureFile(char *sFileName)
{
	char			*startBuf;
	char			*endBuf;
	char			*tmpBuf;
	int				file_size;
	char			lineBuf[2048];
	char			copyLineBuf[2048];
	int				columnNumber=0;
	int				ii;
	CFileMan *m_File = new CFileMan;

	m_File->read_file(sFileName,&startBuf, &file_size);
	endBuf   = startBuf + file_size;
	tmpBuf =   startBuf;
	while(tmpBuf < endBuf)
	{	
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		columnNumber++;
	}
	tmpBuf = startBuf;
	for ( ii = 0; ii < columnNumber -1; ii++)
	{
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		char	*torken = NULL;
		strcpy(copyLineBuf, lineBuf);
		torken = (char *) strtok(copyLineBuf," ,;\t\n\r");
		if (torken[0] == '!')
		{
			continue;
		}
		else if (torken[0] == '#')
		{
			break;
		}
		else if (strcmp(torken,"TEXTURE") == 0)
		{
			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy(m_TextureList[m_nTexture].token, torken);
			
			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy(m_TextureList[m_nTexture].pathName, torken);

			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_TextureList[m_nTexture].mipmap = atoi(torken);// mipmap int true, false
			m_nTexture++;
		}
	}
}

void CEasyOpenGL::ReadDyanamicMapTextureFile (char *sFileName)
{
	char			*startBuf;
	char			*endBuf;
	char			*tmpBuf;
	int				file_size;
	CFileMan *m_File = new CFileMan;

	char			lineBuf[256];
	char			copyLineBuf[2048];
	char			*str;
	int				noChar;
	int				columnNumber=0;
	int				ii;
	m_File->read_file(sFileName,&startBuf, &file_size);
	endBuf   = startBuf + file_size;
	tmpBuf =   startBuf;
	while(tmpBuf < endBuf)
	{	
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		columnNumber++;
	}
	tmpBuf = startBuf;

	for ( ii = 0; ii < columnNumber -1; ii++)
	{
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		char	*torken = NULL;
		strcpy(copyLineBuf, lineBuf);
		torken = (char *) strtok(copyLineBuf," ,;\t\n\r");
		if (torken[0] == '!')
		{
			continue;
		}
		else if (torken[0] == '#')
		{
			break;
		}
		else if (strcmp(torken,"DEF_TEXTURE") == 0)
		{
			char	string[16];
			char	str1[16];
			char	name[16];
			int		id;
			float	longLeft, latBtm, longRight, latTop;
			char	texFilename[256];


			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].nType =  atoi(torken);
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].nId =  atoi(torken);

			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy( texFilename,	"texture\\" );
			strcat( texFilename,	 torken );
			strcat( texFilename,	".bmp" );
			strcpy(m_dynMapTex[m_nNoDynMapTex].strTexFileName,texFilename);

			// 0,0 점  
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][1]		= atof(torken);
			latBtm = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][0];
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][0]		= atof(torken);
			longLeft = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][1];

			// 1,0 점  
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][1]		= atof(torken);
			latTop = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][0];
	
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][0]		= atof(torken);
			longRight = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][1];


			// 1,1 점  
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][1]		= atof(torken);
			latBtm = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][0];
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][0]		= atof(torken);
			longLeft = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][1];

			// 0,1 점  
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][1]		= atof(torken);
			latTop = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][0];
	
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][0]		= atof(torken);
			longRight = m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][1];




		
			m_dynMapTex[m_nNoDynMapTex].nTexLevel		= 0;
			m_dynMapTex[m_nNoDynMapTex].nTexComponent	= 3;
			m_dynMapTex[m_nNoDynMapTex].fMapSize		= ( longLeft - longRight) * (latTop - latBtm);

			double dx, dy, gridzone; 

			Gp2Utm(D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][0] , D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[0][1], &gridzone, &dx, &dy);

			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[0][0] =   dx - RWYOFFSET_UTM_X; 
			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[0][1] =   dy - RWYOFFSET_UTM_Y; 



			Gp2Utm(D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][0] , D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[1][1], &gridzone, &dx, &dy);

	

			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[1][0] =   dx - RWYOFFSET_UTM_X ; 
			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[1][1] =   dy - RWYOFFSET_UTM_Y; 


			Gp2Utm(D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][0] , D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[2][1], &gridzone, &dx, &dy);

	
			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[2][0] =   dx - RWYOFFSET_UTM_X; 
			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[2][1] =   dy - RWYOFFSET_UTM_Y; 


			Gp2Utm(D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][0] , D2R*m_dynMapTex[m_nNoDynMapTex].dLongLatVertex[3][1], &gridzone, &dx, &dy);

	

			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[3][0] =   dx - RWYOFFSET_UTM_X ; 
			m_dynMapTex[m_nNoDynMapTex].dUTMVertex[3][1] =   dy - RWYOFFSET_UTM_Y; 



			m_nNoDynMapTex++;

		}
	}
}



void	CEasyOpenGL::LoadTexture()
{
	int	i;
	for ( i = 0; i < m_nTexture; i++ )
	{
		if ( ( m_nTextureBoundID[i] = m_CMyTexture.AddTexture( m_TextureList[i].token, m_TextureList[i].pathName, m_TextureList[i].mipmap ) ) == ERROR )
		{
			MessageBox(NULL,"Loading texture %s error !\n","ERROR",MB_OK|MB_ICONEXCLAMATION);
		}
	}
	/// BMP Texture 로딩
	for(i=0;i<m_nNoDynMapTex;i++)
	{
		m_dynMapTexID[i] = m_CMyTexture.AddTexture( m_dynMapTex[i].strTexFileName, 	m_dynMapTex[i].strTexFileName, false );
	}

	// DDS Texture 로딩 
/*	
	for(i=0;i<m_nNoDDSPatch;i++)
	{
		m_DDSTexBoundID[i] = m_CDDSTexture.AddTexture( m_DDSPatch[i].cTexPathFileName, 	m_DDSPatch[i].cTexPathFileName, true );
	}
*/

}

///////////////////////////////////////////////
//  함 수 명 : 	LoadPatchList								
//  설    명 :	한국지형을 DDS 포맷의 위성사진으로 맵핑하기 위한 데이터 읽기   
//  입력인수 :	
//  출력인수 :  없음 				
//  함수출력 :	없음   
//  제 작 자 :  김주일  
//  제 작 일 :  2015.9
//  관리번호 :  
//  수정기록 : 

void
CEasyOpenGL::ReadDDSTextureFile( char* sFileName )
{
	char			*startBuf;
	char			*endBuf;
	char			*tmpBuf;
	int				file_size;
	CFileMan *m_File = new CFileMan;

	char			lineBuf[256];
	char			copyLineBuf[2048];
	char			*str;
	char			texPathFileName[256];
	int				noChar;
	int				columnNumber=0;
	int				ii;
	m_File->read_file(sFileName,&startBuf, &file_size);
	endBuf   = startBuf + file_size;
	tmpBuf =   startBuf;
	while(tmpBuf < endBuf)
	{	
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		columnNumber++;
	}
	tmpBuf = startBuf;

	for ( ii = 0; ii < columnNumber -2; ii++)
	{
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		char	*torken = NULL;
		strcpy(copyLineBuf, lineBuf);
		torken = (char *) strtok(copyLineBuf," ,;\t\n\r");
		if (torken[0] == '!')
		{
			continue;
		}
		else if (torken[0] == '#')
		{
			break;
		}
		else if (strcmp(torken,"DEF_GRID_TEXTURE") == 0)
		{
			char	string[16];
			char	str1[16];
			char	name[16];
			int		id;
			float	longLeft, latBtm, longRight, latTop;
			char	texFilename[256];


			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy(str1, torken);
			
			torken = (char *) strtok(NULL," ,;\t\n\r");
			id  =  atoi(torken);

			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy(texFilename, torken);
			
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_DDSPatch[m_nNoDDSPatch].fLonMin = atof(torken);

			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_DDSPatch[m_nNoDDSPatch].fLonMax = atof(torken);

			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_DDSPatch[m_nNoDDSPatch].fLatMin = atof(torken);
		
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_DDSPatch[m_nNoDDSPatch].fLatMax = atof(torken);

			strcpy( texPathFileName, "DDStexture\\" );
			strcat( texPathFileName, texFilename );
			strcpy( m_DDSPatch[m_nNoDDSPatch].cTexPathFileName, texPathFileName );
			m_nNoDDSPatch++;
		}
	}


}


void	CEasyOpenGL::DrawKoreaMap()
{
	
	


}


void	CEasyOpenGL::DrawGridScale()
{
	char	strTmp[256];
	int		nX, nY;
	int		i, j, k;
	
	float	fX, fY;
	float	fHeight;

	double	x,y, z;
	double  fXNM, fYNM;

	double  dx, dy, gridzone;
	double	dLongitude, dLatitude;
	double	dMinLong, dMaxLong;
	double	dMinLat, dMaxLat;
	float	fLeftX, fBtmY;
	float	fRightX, fTopY;





	dMinLong = 126.0;
	dMaxLong = 130.0;

	dMinLat = 33.0;
	dMaxLat = 38.1;


	Gp2Utm(D2R*dMinLong , D2R*dMinLat, &gridzone, &dx, &dy);

	fLeftX	= dx - RWYOFFSET_UTM_X;
	fBtmY   = dy - RWYOFFSET_UTM_Y;

	Gp2Utm(D2R*dMaxLong , D2R*dMaxLat, &gridzone, &dx, &dy);
	fRightX  = dx - RWYOFFSET_UTM_X;
	fTopY     = dy - RWYOFFSET_UTM_Y;
	glColor3f(1.0f, 1.0f, 1.0f);

	double	dDeltaLong,  dDeltaLat;

	dDeltaLong = 0.25;
	dDeltaLat  = 0.2;
	for(dLatitude =dMinLat; dLatitude <= dMaxLat; dLatitude +=dDeltaLat)
	{
		for(dLongitude = dMinLong; dLongitude <= dMaxLong; dLongitude += dDeltaLong)
		{
			glBegin(GL_LINES);
				Gp2Utm(D2R*dLongitude , D2R*dLatitude, &gridzone, &dx, &dy);
				fX = dx - RWYOFFSET_UTM_X;
				fY = dy - RWYOFFSET_UTM_Y;
				glVertex3f(fX,fY, 0.0f);
				Gp2Utm(D2R*dLongitude , D2R*(dLatitude+dDeltaLat), &gridzone, &dx, &dy);
				fX = dx - RWYOFFSET_UTM_X;
				fY = dy - RWYOFFSET_UTM_Y;
				glVertex3f(fX,fY, 0.0f);
			glEnd();

			glBegin(GL_LINES);
				Gp2Utm(D2R*dLongitude , D2R*dLatitude, &gridzone, &dx, &dy);
				fX = dx - RWYOFFSET_UTM_X;
				fY = dy - RWYOFFSET_UTM_Y;
				glVertex3f(fX,fY, 0.0f);
				Gp2Utm(D2R*(dLongitude+dDeltaLong) , D2R*dLatitude, &gridzone, &dx, &dy);
				fX = dx - RWYOFFSET_UTM_X;
				fY = dy - RWYOFFSET_UTM_Y;
				glVertex3f(fX,fY, 0.0f);
			glEnd();
		}
	}


	for(dLatitude =dMinLat; dLatitude <= dMaxLat; dLatitude +=dDeltaLat)
	{
		Gp2Utm(D2R*127.0 , D2R*dLatitude, &gridzone, &dx, &dy);
		fX = dx - RWYOFFSET_UTM_X;
		fY = dy - RWYOFFSET_UTM_Y;
		sprintf(strTmp,"%.2f ", dLatitude);
		Printf(fX, fY ,strTmp, LARGE_FONT);
	}

	for(dLongitude = dMinLong; dLongitude <= dMaxLong; dLongitude += dDeltaLong)
	{
		Gp2Utm(D2R*dLongitude , D2R*34.0, &gridzone, &dx, &dy);
		fX = dx - RWYOFFSET_UTM_X;
		fY = dy - RWYOFFSET_UTM_Y;
		sprintf(strTmp,"%.2f ", dLongitude);
		Printf(fX, fY ,strTmp, LARGE_FONT);
	}






}















void	CEasyOpenGL::DrawGridCircle(float cx, float cy)
{
	float		fR;
	float		fSpace = 2000.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	for(fR=0; fR<=10000; fR+=fSpace)
	{
		DrawCircle2D(cx, cy,0.0f, fR, 5, 0);
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	for(fR=11000; fR<=20000; fR+=fSpace)
	{
		DrawCircle2D(cx, cy,0.0f,fR, 5, 0);
	}

	glColor3f(0.0f, 0.0f, 1.0f);
	for(fR=21000; fR<=30000; fR+=fSpace)
	{
		DrawCircle2D(cx, cy,0.0f,fR, 5, 0);
	}

}

void	CEasyOpenGL::SetZoomScale(float fInput, float fMin, float fMax)
{
	m_fScreenZoomScale =  fInput;
	if( m_fScreenZoomScale > fMax ) m_fScreenZoomScale = fMax;
	if( m_fScreenZoomScale < fMin ) m_fScreenZoomScale = fMin;
}

void	CEasyOpenGL::ConvertWordToScreen2D(float wx, float wy, int *sx, int *sy)
{
	float fOffsetX, fOffsetY;
	float fOffsetPointX, fOffsetPointY;

	fOffsetX = wx;
	fOffsetY = wy;

	fOffsetPointX = fOffsetX * m_fScreenZoomScale / m_fScaleX;
	fOffsetPointY = fOffsetY * m_fScreenZoomScale / m_fScaleY;



//	EasyMouse.m_fPosX =  m_fCenterX+ EasyMouse.m_fPanX + fOffsetPointX ;
//	EasyMouse.m_fPosY =  m_fCenterY +EasyMouse.m_fPanY - fOffsetPointY; // 상하가 바뀜

	*sx =  m_fCenterX + EasyMouse.m_fPanX + fOffsetPointX ;
	*sy =  m_fCenterY +  EasyMouse.m_fPanY - fOffsetPointY; // 상하가 바뀜



}

void	CEasyOpenGL::GetPickPosition()
{
	char		strLong[64], strLat[64];
	double		utmPos[3];
	double		llhPos[3];

	float		fOffsetPointX, fOffsetPointY;
	float		fOffsetX, fOffsetY;
	float		fUTMX, fUTMY;
	float		fLong, fLat;

	fOffsetPointX = (EasyMouse.m_fPosX - m_fCenterX)-EasyMouse.m_fPanX;
	fOffsetPointY = -(EasyMouse.m_fPosY - m_fCenterY)+EasyMouse.m_fPanY; // 상하가 바뀜

	fOffsetX = fOffsetPointX*m_fScaleX/m_fScreenZoomScale;
	fOffsetY = fOffsetPointY*m_fScaleY/m_fScreenZoomScale;

	fUTMX = utmPos[0] = fOffsetX + RWY_POSITION_X;
	fUTMY = utmPos[1] = fOffsetY + RWY_POSITION_Y;

	utm2llh( llhPos, utmPos[0], utmPos[1], 52, 'S');	//  int zone, char zone_char  );
	fLat =  llhPos[0]*R2D;
	fLong = llhPos[1]*R2D;	

	ConvertDegToString60(fLong, strLong);
	ConvertDegToString60(fLat, strLat);


	m_fPosUTMX = fUTMX;
	m_fPosUTMY = fUTMY;

	m_fPosLong = fLong ;
	m_fPosLat = fLat;
	strcpy(m_strLong,strLong) ;
	strcpy(m_strLat,strLat);

}



void	CEasyOpenGL::ShowPickPosition()
{
	char		strTmp[256];
	int			nX = 10, nY = 10;
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fOffsetPointX, fOffsetPointY;
	float		fOffsetX, fOffsetY;
	float		fUTMX, fUTMY;
	float		fLong, fLat;

	glColor3f(1.0f, 1.0f, 1.0f);
	SetOrtho3DView (0, m_nWndWidth, 0, m_nWndHeight, -10, 10);

//	m_fScaleX = ( m_VScreenSize.x *m_fAspectRatio) / (m_nWndWidth);
//	m_fScaleY = m_VScreenSize.y / (m_nWndHeight);

	nY = m_nWndHeight - EasyMouse.m_fPosY;
	nX = EasyMouse.m_fPosX + 20;

	sprintf(strTmp,"%.0f,%.0f ", EasyMouse.m_fPosX, EasyMouse.m_fPosY);
	Printf(nX, nY ,strTmp, LARGE_FONT);


	fOffsetPointX = (EasyMouse.m_fPosX - m_fCenterX)-EasyMouse.m_fPanX;
	fOffsetPointY = -(EasyMouse.m_fPosY - m_fCenterY)+EasyMouse.m_fPanY; // 상하가 바뀜
	
	nY -= nHSpace;
	sprintf(strTmp,"%.2f,%.2f ", fOffsetPointX, fOffsetPointY);
	Printf(nX, nY ,strTmp, LARGE_FONT);

	fOffsetX = fOffsetPointX*m_fScaleX/m_fScreenZoomScale;
	fOffsetY = fOffsetPointY*m_fScaleY/m_fScreenZoomScale;
	nY -= nHSpace;
	
	sprintf(strTmp,"%.2f,%.2f ", fOffsetX, fOffsetY);
	Printf(nX, nY ,strTmp, LARGE_FONT);

	char		strLong[64], strLat[64];
	double		utmPos[3];
	double		llhPos[3];

	fUTMX = utmPos[0] = fOffsetX + RWY_POSITION_X;
	fUTMY = utmPos[1] = fOffsetY + RWY_POSITION_Y;

	utm2llh( llhPos, utmPos[0], utmPos[1], 52, 'S');	//  int zone, char zone_char  );
	fLat =  llhPos[0]*R2D;
	fLong = llhPos[1]*R2D;	


	nY -= nHSpace;
	sprintf(strTmp,"%.3f, %.3f",	fLat, fLong);
	Printf(nX, nY,strTmp, LARGE_FONT);

	ConvertDegToString60(fLong, strLong);
	ConvertDegToString60(fLat, strLat);
	nY -= nHSpace;
	sprintf(strTmp,"%s, %s",	strLat, strLong);
	Printf(nX, nY,strTmp, LARGE_FONT);




	m_fPosUTMX = fUTMX;
	m_fPosUTMY = fUTMY;


}



////////////////////////////////////////////////////////////////
// Joystick 입력 디버깅 정보창
void	CEasyOpenGL::ShowJoyStickInput(int nX, int nY, int nShow)
{



}


void	CEasyOpenGL::DrawAireraftID()
{





}



void CEasyOpenGL::DrawFlightScenarioTrack()
{
	int		i,j,k;

}


void	
CEasyOpenGL::DrawAC(float fSize)
{


}

void	
CEasyOpenGL::DrawADS_B_UAT_AC(float fSize)
{
	////////

}


void	
CEasyOpenGL::DrawADS_B_GBT_AC(float fSize)
{


}
void	
CEasyOpenGL::DrawADS_B_GDL90_AC(float fSize)
{

	
}



void	
CEasyOpenGL::DrawCADPAircraft(float fSize)
{

}

void	
CEasyOpenGL::DrawCollisionPoint(float fSize)
{



}


	

	

////////////////////////////////////////////////////////////////
// Joystick 입력 디버깅 정보창
void	CEasyOpenGL::ShowCSSSSendMessage(int nX, int nY, int nShow)
{

}


////////////////////////////////////////////////////////////////
// Joystick 입력 디버깅 정보창
void	CEasyOpenGL::ShowFlightPathData(int nX, int nY, int nShow)
{

}



////////////////////////////////////////////////////////////////
// Joystick 입력 디버깅 정보창
void	CEasyOpenGL::ShowGeneralInformation(int nX, int nY, int nShow)
{




}


void	
CEasyOpenGL::DrawFlightPath()
{


}



/// 디브리핑시에 항공기 그리기 (해당 시간의)
void	
CEasyOpenGL::DrawDebriefACPoistion(float fT)
{

}









// ! 34.6081, 127.205 => 34.36.2916, 127.13.18
// !RWYOFFSET, 335428.72, 3831049.25, 0.0
// RWYOFFSET, 335429, 3831049, 0.0


void	CEasyOpenGL::DrawTest()
{


}

void	CEasyOpenGL::Draw2DScreenDisplay()
{

}


void	
CEasyOpenGL::ShowACInformation(int nShow)
{

}

void	
CEasyOpenGL::ShowACInformation2D(int nShow)
{




}




////////////////////////////////////////////////////////////////
// Joystick 입력 디버깅 정보창
int	CEasyOpenGL::ShowMouseInput(int nX, int nY, int nShow)
{

	return nY;
}


////////////////////////////////////////////////////////////////
// 디버깅 정보창
void	CEasyOpenGL::ShowDebugInformation( )
{

}



void	CEasyOpenGL::RenderAll3DContents()
{

}


void	CEasyOpenGL::RenderAll2DContents()
{

}

void	
CEasyOpenGL::DrawRectangle(float x, float y, float w, float h)
{
	glBegin(GL_LINE_LOOP);
		glVertex3f(x,y,0.0f);
		glVertex3f(x+w,y,0.0f);
		glVertex3f(x+w,y+h,0.0f);
		glVertex3f(x,y+h,0.0f);
	glEnd();
}

void	
CEasyOpenGL::DrawCenterRectangle(float x, float y, float z, float w, float h)
{
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-w/2.0f,y-h/2.0f,z);
		glVertex3f(x+w/2.0f,y-h/2.0f,z);
		glVertex3f(x+w/2.0f,y+h/2.0f,z);
		glVertex3f(x-w/2.0f,y+h/2.0f,z);
	glEnd();
}


void	
CEasyOpenGL::DrawGDL90Aircraft(float fLong, float fLat, float fAlt, float fHeading, int type, float fSize)
{

	char		strTmp[256];
	float fR;
	double	utmX, utmY;
	double dx, dy, gridzone;
	
	fR = fSize/2.0f;
	
	if( fLong > 120.0f && fLong < 130.0f)
	{
		if( fLat > 33.0f && fLat < 38.0f)
		{
			Gp2Utm(D2R*fLong, D2R*fLat, &gridzone, &dx, &dy);
			utmX = (dx - RWY_POSITION_X);
			utmY = (dy - RWY_POSITION_Y);
			DrawCenterRectangle( utmX, utmY,fAlt,fR, fR);
			switch(type)
			{
				case 0 : // Basic
					sprintf(strTmp,"Bas");
					Printf3D( (int)  (utmX-(fR*1.5f)), (int) (utmY+fR/2.0f) ,fAlt, strTmp, MIDDLE_FONT);
				break;
				case 1 : // Long
					sprintf(strTmp,"Lon");
					Printf3D( (int)  (utmX-(fR*1.5f)), (int) (utmY -fR) ,fAlt,strTmp, MIDDLE_FONT);
				break;
				case 2 : // Ownship
					sprintf(strTmp,"Own");
					Printf3D( (int)  (utmX+fR*0.7), (int) (utmY -fR) ,fAlt,strTmp, MIDDLE_FONT);
				break;
				case 3 : // Traffic
					sprintf(strTmp,"Tra");
					Printf3D( (int)  (utmX+fR*0.7), (int) (utmY+fR/2.0f) ,fAlt,strTmp, MIDDLE_FONT);
				break;
			}
		}
	}
}

void	
CEasyOpenGL::DrawGBTAircraft(float fLong, float fLat, float fAlt, float fHeading, int type, float fSize)
{

	char		strTmp[256];
	float fR;
	double	utmX, utmY;
	double dx, dy, gridzone;
	
	fR = fSize/2.0f;
	
	if(fAlt < 10.0) fAlt = 10.0f;

	if( fLong > 120.0f && fLong < 130.0f)
	{
		if( fLat > 33.0f && fLat < 38.0f)
		{
			Gp2Utm(D2R*fLong, D2R*fLat, &gridzone, &dx, &dy);
			utmX = (dx - RWY_POSITION_X);
			utmY = (dy - RWY_POSITION_Y);
			DrawCenterRectangle( utmX, utmY,fAlt,fR, fR);
			switch(type)
			{
				case 0 : // Basic
					sprintf(strTmp,"Bas");
					Printf3D( (int)  (utmX-(fR*1.5f)), (int) (utmY+fR/2.0f) ,fAlt, strTmp, MIDDLE_FONT);
				break;
				case 1 : // Long
					sprintf(strTmp,"Lon");
					Printf3D( (int)  (utmX-(fR*1.5f)), (int) (utmY -fR) ,fAlt,strTmp, MIDDLE_FONT);
				break;
				case 2 : // Ownship
					sprintf(strTmp,"Own");
					Printf3D( (int)  (utmX+fR*0.7), (int) (utmY -fR) ,fAlt,strTmp, MIDDLE_FONT);
				break;
				case 3 : // Traffic
					sprintf(strTmp,"Tra");
					Printf3D( (int)  (utmX+fR*0.7), (int) (utmY+fR/2.0f) ,fAlt,strTmp, MIDDLE_FONT);
				break;
				default: // GBT
					sprintf(strTmp,"GBT");
					Printf3D( (int)  (utmX+fR*0.7), (int) (utmY+fR/2.0f) ,fAlt,strTmp, MIDDLE_FONT);
				break;
			}
		}
	}
}

void
CEasyOpenGL::DrawAircraft(float fLong, float fLat, float fAlt, float fHeading)
{
	float	fSize;
	float	x, y, z;

	x =100.0f;
	y = 100.0f;
	z = 1.0f;

	fSize  =100.0f;

	DrawCircle2D( x, y, z, fSize , 16, 1);

}


// 111215 UTM=>위경도 변환 추가 - 항우연 제공 skh
// llh : radian
// utmzone_char: 'C' <=  <= 'X'
void CEasyOpenGL::utm2llh( double *llh, double x, double y, int zone, char zone_char)
{
	double sa, sb;
	double e2, e2cuadrada, c;
	double X, Y;
	double s, lat, v, a, a1, a2, j2, j4, j6, alfa, beta, gama, Bm, b;
	double Epsi, Eps, nab, senoheps, Delt, TaO;
	double longitude, latitude;
	double cosLat, cosLat2;

	sa = 6378137.000000 ; sb = 6356752.314245;

	e2 = sqrt( sa*sa - sb*sb ) / sb;
	e2cuadrada = e2 * e2;
	c = ( sa*sa ) / sb;

	X = x - 500000.;
	if( zone_char > 'M' )	// northern hemisphere, 
		Y = y;
	else						// southern hemisphere, 
		Y = y - 10000000.;

	s = ( ( zone * 6. ) - 183. ); 
	lat =  Y / ( 6366197.724 * 0.9996 );           
	cosLat = cos(lat);
	cosLat2 = cosLat*cosLat;
	v = ( c / sqrt( 1 + e2cuadrada * cosLat2 ) ) * 0.9996;
	a = X / v;
	a1 = sin( 2. * lat );
	a2 = a1 * cosLat2;
	j2 = lat + ( a1 / 2. );
	j4 = ( ( 3. * j2 ) + a2 ) / 4.;
	j6 = ( ( 5. * j4 ) + ( a2 * cosLat2) ) / 3.;
	alfa = ( 3. / 4. ) * e2cuadrada;
	beta = ( 5. / 3. ) * alfa*alfa;
	gama = ( 35. / 27. ) * alfa*alfa*alfa;
	Bm = 0.9996 * c * ( lat - alfa * j2 + beta * j4 - gama * j6 );
	b = ( Y - Bm ) / v;
	Epsi = ( e2cuadrada*a*a/2. ) *cosLat2;
	Eps = a * ( 1. - Epsi/3. );
	nab = ( b * ( 1. - Epsi ) ) + lat;
	senoheps = ( exp(Eps) - exp(-Eps) ) / 2.;
	Delt = atan(senoheps / cos(nab) );
	TaO = atan(cos(Delt) * tan(nab));
	longitude = Delt + s*0.0174532925199433;
	latitude = lat + ( 1. + e2cuadrada*cosLat2 - 3./2.*e2cuadrada*sin(lat)*cosLat*(TaO - lat) ) * ( TaO - lat );

	llh[0] = latitude;
	llh[1] = longitude;
}



void CEasyOpenGL::Gp2Utm(const double lon_rad, const double lat_rad, 
					 double *gridzone, double *east_mtr, double *north_mtr)
{
	double base_lon, base_lat;
	double gzone;
	double e1s, e2s;
	double sin_lat, cos_lat, tan_lat;
	double n;
	double t, t2;
	double c, c2;
	double a, a2, a3, a4, a5, a6;
	double array[4];
	double e4, e6;
	double m, m0;
	double tmp1, tmp2, tmp3;
	
	gzone = (unsigned int)(lon_rad*R2D*(1.0/6.0) + 31.0);
	
	base_lon = (6 * gzone - 183.0)*D2R;
	base_lat = 0.0;  
	
	e1s = ( 2.0 / 298.257223563 - 1.0 / (298.257223563 * 298.257223563) );
	e2s = e1s / (1.0 - e1s);
	
	sin_lat = sin(lat_rad);
	cos_lat = cos(lat_rad);
	tan_lat = tan(lat_rad);
	
	n = 6378137 / sqrt(1 - e1s * sin_lat * sin_lat);
	
	t  = tan_lat * tan_lat;
	t2 = t * t;
	
	c  = e2s * cos_lat * cos_lat;
	c2 = c * c;
	
	a  = (lon_rad - base_lon) * cos_lat;
	a2 = a * a;
	a3 = a * a2;
	a4 = a * a3;
	a5 = a * a4;
	a6 = a * a5;
	
	e4 = e1s * e1s;
	e6 = e4 * e1s;
	
	array[0] = 1.0 - e1s*(1.0/4.0) - e4*(3.0/64.0) - e6*(5.0/256.0);
	array[1] = e1s*(3.0/8.0) + e4*(3.0/32.0) + e6*(45.0/1024.0);
	array[2] = e4*(15.0/256.0) + e6*(45.0/1024.0);
	array[3] = e6*(35.0/3072.0);
	
	if (lat_rad == 0.0) 
	{
		m = 0.0;
	} 
	else 
	{
		m = 6378137 * ( array[0]*lat_rad - array[1]*sin(2*lat_rad) + 
			array[2]*sin(4*lat_rad) - array[3]*sin(6*lat_rad) );
	}

	if (base_lat == 0.0) 
	{
		m0 = 0.0;
	} 
	else 
	{
		m0 = 6378137 * ( array[0]*base_lat - array[1]*sin(2*base_lat) + 
			array[2]*sin(4*base_lat) - array[3]*sin(6*base_lat) );
	}
	
	*gridzone  = gzone;
	
	
	tmp1 = a + (1-t+c)*a3*(1.0/6.0);
	tmp2 = (5 - 18*t + t2 + 72*c - 58*e2s)*a5*(1.0/120.0);

	if( (lon_rad *R2D) >= 126.0f)
	{
		*east_mtr = 0.9996*n*(tmp1+tmp2) + 500000;
	}
	else
	{
		*east_mtr = 0.9996*n*(tmp1+tmp2)-155000;
	}  
	
	tmp1 =  m - m0;
	tmp2 = a2*(1.0/2.0) + (5 - t + 9*c + 4*c2)*a4*(1.0/24.0);
	tmp3 = (61 - 58*t + t2 + 600*c - 330*e2s)*a6*(1.0/720.0);
	*north_mtr = 0.9996*( tmp1 + n*tan_lat*(tmp2+tmp3) );
	
}


void CEasyOpenGL::ConvertDegToString60(float fDeg, char *strDeg60)
{
	char	strMin[8];
	char	strSec[8];
	int	nDeg;
	int	nMin;
	int	nSec;
	int	nSec100;
	float	fMin;
	float	fSec;
	float	fSec100;

	if( fDeg >10.0f && fDeg <360.0f)
	{
		nDeg = fDeg;
		fMin = (fDeg - nDeg)*60.0f;
		nMin = fMin;
		fSec = (fMin - nMin) * 60.0f;
		nSec = fSec;
		fSec100 = fSec - nSec;


		if(nMin < 10)
		{
			sprintf(strMin,"0%d",nMin);
		}
		else
		{
			sprintf(strMin,"%d",nMin);
		}
		nSec100 = fSec100 *100.0f;
		if(nSec < 10)
		{
			sprintf(strSec,"0%d.%d",nSec,nSec100);
		}
		else
		{
			sprintf(strSec,"%d.%d",nSec,nSec100);
		}

		if( nDeg < 100 )
		{
			sprintf(strDeg60," %d:%s:%s",nDeg,strMin,strSec);
		}
		else
		{
			sprintf(strDeg60,"%d:%s:%s",nDeg,strMin,strSec);
		}
	}
	else
	{

		sprintf(strDeg60,"00:00:00");

	}



}

// 색상표
//  직사각형내에 값에 따른 색상 표시


//  흰색 : 1.0, 1.0, 1.0
//  333
//
//  녹색 : 0.0, 1.0, 0.0
//
//  333
//  노란색1.0, 1.0, 0.0
//  
//  333
//
//  적색 : 1.0, 0.0, 0.0

void CEasyOpenGL::SetTableColor(float fValue, float fValueRange)
{

	float	fStep;
	float	fColor;
	fStep = fValueRange/ 6;

	if( fValue > fValueRange ) return;

	if( fValue < fStep )
	{

		if( fValue < fStep/2)
		{
			fColor = 1.0f -  fValue / fStep;
			glColor4f(fColor, 1.0f, fColor, 0.1f);
		}
		else
		{
			fColor = 1.0f -  fValue / fStep;
			glColor4f(fColor, 1.0f, fColor, 0.3f);
		}
	}
	else 	if( fValue < (fStep* 3.0))
	{
		fColor = (fValue - fStep) / fStep;
		glColor4f(fColor, 1.0f, 0.0f, 0.5);


	}
	else 	
	{
		fColor = 1.0f - (fValue - (fStep*3)) / (fStep*3);
		glColor4f(1.0, fColor, 0.0f, 0.6);


	}


	//float	fStep;
	//float	fColor;
	//fStep = fValueRange/ 4;

	//if( fValue > fValueRange ) return;

	//if( fValue < fStep )
	//{
	//	fColor = 1.0f -  fValue / fStep;
	//	glColor4f(fColor, 1.0f, fColor, 0.1+fColor/2.0f);

	//}
	//else 	if( fValue < (fStep* 2.0))
	//{
	//	fColor = (fValue - fStep) / fStep;
	//	glColor4f(fColor, 1.0f, 0.0f, 0.5);


	//}
	//else 	
	//{
	//	fColor = 1.0f - (fValue - (fStep*2)) / (fStep*2);
	//	glColor4f(1.0, fColor, 0.0f, 0.5);


	//}

}

void CEasyOpenGL::DrawColorTable(int  x, int y, int  w, int h, int nStep)
{
	// 색상을 10 
	int		i, j, k;
	char	strTmp[64];

	int		hh;
	hh = h/nStep;
	for(i=0;i<=nStep;i++)
	{
		SetTableColor(i,11);

		sprintf(strTmp,"%d",i*100);
		Draw2DBoxWithLabel(x+10, y- hh*i , w, h/nStep, 1,strTmp);
	}
}

void	
CEasyOpenGL::Server()
{

	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));


	RenderAll3DContents();

	RenderAll2DContents();
	
	if( m_nViewMode ==  ORTHO_MODE)
	{
		DrawTest();
	}
	Draw2DScreenDisplay();



	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));
}



