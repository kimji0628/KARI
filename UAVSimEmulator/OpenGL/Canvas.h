#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include "Viewport.h"
#include "Texture.h"

#if !defined(_CANVAS_H_INCLUDED_)
#define _CANVAS_H_INCLUDED_

class	Canvas
{
protected:

public:
	HDC				m_hDC;
	HGLRC			m_hRC;
	HWND			m_hWnd;

	int				m_width;
	int				m_height;
	double			m_ratio;

	int				m_maxViewport;
	int				m_nofViewport;
//	int				m_focusedViewport;
//	int				m_focusedViewportSave;
//	int				m_pickedViewport;			// MENU_VIEW는 picked는 되지만 focused는 되지 않는다.
	int				m_onAirViewport;

	Viewport*		m_viewport;

public:
	Canvas();
	~Canvas();

	int		Open( HWND hWnd, int colorDepth = 32, int width = 1024, int height = 768, int nofViewport = 1 );
	void	Close();

	int		ViewportName2ID( char* name );
	int		NewViewport( char* name );
	int		AddViewport( char* viewportName, double xPos, double yPos, double width, double height );
	int		SetViewport( char* viewportName, double xPos, double yPos, double width, double height );
	
	void	Activate();
	void	Inactivate();
	void	ResizeRC(GLsizei width, GLsizei height);			// Resize And Initialize The GL Window

	void	OnAirViewport( int viewportID );
	void	EnableViewport( int viewportID );
	void	DisableViewport( int viewportID );

	HDC		GetCanvasDC()		{ return m_hDC; }
	int		GetCanvasWidth()	{ return m_width; }
	int		GetCanvasHeight()	{ return m_height; }
};

extern	PFNGLMULTITEXCOORD1FARBPROC			glMultiTexCoord1fARB;
extern	PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
extern	PFNGLMULTITEXCOORD3FARBPROC			glMultiTexCoord3fARB;
extern	PFNGLMULTITEXCOORD4FARBPROC			glMultiTexCoord4fARB;
extern	PFNGLMULTITEXCOORD1FVARBPROC		glMultiTexCoord1fvARB;
extern	PFNGLMULTITEXCOORD2FVARBPROC		glMultiTexCoord2fvARB;
extern	PFNGLMULTITEXCOORD3FVARBPROC		glMultiTexCoord3fvARB;
extern	PFNGLMULTITEXCOORD4FVARBPROC		glMultiTexCoord4fvARB;
extern	PFNGLMULTITEXCOORD1DARBPROC			glMultiTexCoord1dARB;
extern	PFNGLMULTITEXCOORD2DARBPROC			glMultiTexCoord2dARB;
extern	PFNGLMULTITEXCOORD3DARBPROC			glMultiTexCoord3dARB;
extern	PFNGLMULTITEXCOORD4DARBPROC			glMultiTexCoord4dARB;
extern	PFNGLMULTITEXCOORD1DVARBPROC		glMultiTexCoord1dvARB;
extern	PFNGLMULTITEXCOORD2DVARBPROC		glMultiTexCoord2dvARB;
extern	PFNGLMULTITEXCOORD3DVARBPROC		glMultiTexCoord3dvARB;
extern	PFNGLMULTITEXCOORD4DVARBPROC		glMultiTexCoord4dvARB;
extern	PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;
extern	PFNGLCLIENTACTIVETEXTUREARBPROC		glClientActiveTextureARB;


#endif		// _CANVAS_H_INCLUDED_