#include "stdafx.h"
#include "Font.h"
#include "Canvas.h"

Canvas::Canvas()
{
	m_width		= 1280;						// default value
	m_height	= 774;

	m_hDC		= NULL;
	m_hRC		= NULL;
	m_hWnd		= NULL;

	m_viewport	= NULL;
}

Canvas::~Canvas()
{
	if (m_viewport != NULL)
	{
		delete[] m_viewport;
		m_viewport = NULL;
	}
}

int
Canvas::Open( HWND hWnd, int colorDepth, int width, int height, int nofViewport )
{
	unsigned int	PixelFormat;			// Holds The Results After Searching For A Match

	m_hWnd		= hWnd;
	m_width		= width;
	m_height	= height;

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
		32,											// 16Bit Z-Buffer (Depth Buffer)  
		1,											// Use One Stencil Buffer 
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	m_hDC=GetDC(hWnd);
	if ( !m_hDC )									// Did We Get A Device Context?
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	PixelFormat=ChoosePixelFormat( m_hDC, &pfd );
	if ( !PixelFormat )								// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if( !SetPixelFormat( m_hDC, PixelFormat, &pfd ) )	// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	m_hRC=wglCreateContext( m_hDC );
	if ( !m_hRC )									// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if( !wglMakeCurrent( m_hDC, m_hRC ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow( hWnd, SW_SHOW );					// Show The Window
	SetForegroundWindow( hWnd );					// Slightly Higher Priority
	SetFocus( hWnd );								// Sets Keyboard Focus To The Window
	ResizeRC( m_width, m_height );					// Set Up Our Perspective GL Screen

//	glClearDepth( 1.0 );		   					// Optional Depth Buffer Setup (0.0 ~ 1.0)

	cFont.BuildFont( m_hDC, "Tahoma" );

	m_maxViewport	= nofViewport;
	m_viewport		= new Viewport[ m_maxViewport ];

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


	return true;
}

int
Canvas::ViewportName2ID( char* name )
{
	for ( int i = 0; i < m_nofViewport; i++ )
	{
		if ( _stricmp( m_viewport[i].m_name, name ) == 0 )
			return i;
	}

	return -1;
}

int
Canvas::NewViewport( char* name )
{
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

	return i;
}

int
Canvas::AddViewport( char* viewportName, double xPos, double yPos, double width, double height )
{
	int		vNo = NewViewport( viewportName );

	m_viewport[vNo].m_xPosRatio		= xPos;
	m_viewport[vNo].m_yPosRatio		= yPos;
	m_viewport[vNo].m_widthRatio	= width;
	m_viewport[vNo].m_heightRatio	= height;

	m_viewport[vNo].m_posX			= (int)( m_width  * xPos   / 100.0 );
	m_viewport[vNo].m_posY			= (int)( m_height * yPos   / 100.0 );
	m_viewport[vNo].m_frameWidth	= (int)( m_width  * width  / 100.0 );
	m_viewport[vNo].m_frameHeight	= (int)( m_height * height / 100.0 );

	return vNo;
}

void
Canvas::ResizeRC( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
{
	m_width		= width;
	m_height	= height;

	for ( int vNo = 0; vNo < m_nofViewport; vNo++ )
	{
		m_viewport[vNo].m_posX			= (int)( m_width  * m_viewport[vNo].m_xPosRatio		/ 100.0 );
		m_viewport[vNo].m_posY			= (int)( m_height *  m_viewport[vNo].m_yPosRatio	/ 100.0 );
		m_viewport[vNo].m_frameWidth	= (int)( m_width  *  m_viewport[vNo].m_widthRatio	/ 100.0 );
		m_viewport[vNo].m_frameHeight	= (int)( m_height *  m_viewport[vNo].m_heightRatio	/ 100.0 );
	}
}


int
Canvas::SetViewport( char* viewportName, double xPos, double yPos, double width, double height )
{
	int		vNo = ViewportName2ID( viewportName );

	if ( vNo < 0 )
		return vNo;

	m_viewport[vNo].m_xPosRatio		= xPos;
	m_viewport[vNo].m_yPosRatio		= yPos;
	m_viewport[vNo].m_widthRatio	= width;
	m_viewport[vNo].m_heightRatio	= height;

	m_viewport[vNo].m_posX			= (int)( m_width  * xPos   / 100.0 );
	m_viewport[vNo].m_posY			= (int)( m_height * yPos   / 100.0 );
	m_viewport[vNo].m_frameWidth	= (int)( m_width  * width  / 100.0 );
	m_viewport[vNo].m_frameHeight	= (int)( m_height * height / 100.0 );

	return vNo;
}

void
Canvas::OnAirViewport( int viewportID )
{
	m_onAirViewport	= viewportID;

	m_viewport[m_onAirViewport].OnAir();
}

void
Canvas::EnableViewport( int viewportID )
{
	m_viewport[viewportID].m_enabled	= true;
}

void
Canvas::DisableViewport( int viewportID )
{
	m_viewport[viewportID].m_enabled	= false;
}

void
Canvas::Activate()
{
	if( !wglMakeCurrent( m_hDC, m_hRC ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
}

void
Canvas::Inactivate()
{
	if( !wglMakeCurrent( NULL, NULL ) )			// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Inactivate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
}

void
Canvas::Close()
{
	if (m_hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL;										// Set RC To NULL
	}
}
