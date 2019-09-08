#pragma once
#include <wingdi.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <GL/glext.h>
#include "openGL/Texture.h"

#define	BLACK		0		
#define	WHITE		7	
#define	RED			1
#define	BLUE		4
#define	GREEN 		3
#define	GREY		1015
#define	YELLOW		2
#define	CYAN		1017

#define	EASY_GL_HIDE		0
#define	EASY_GL_SHOW		1

// ! 34.6081, 127.205 => 34.36.2916, 127.13.18
// !RWYOFFSET, 335428.72, 3831049.25, 0.0
#define	RWYOFFSET_UTM_X		 335429.0
#define	RWYOFFSET_UTM_Y		3831049.0


#define	SCREEN_WIDTH		400000.0
#define	SCREEN_HEIGHT		400000.0


#define MAX_TEXTURE			600
///////////////////////////////////
// 글씨체 
// 
#define MAX_FONT_TYPE		5
#define	SMALL_FONT			0
#define	MIDDLE_FONT			1
#define	LARGE_FONT			2

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)



typedef struct {
	float	x,y;
} GL_2D_VECTOR;

typedef struct {
	float	x,y,z;


} GL_3D_VECTOR;


struct	TEXLIST1
{
	char		token[64];
	char		pathName[128];
	int			mipmap;
};

struct	PATCH
{
	char		cTexFileName[64];
	char		cTexPathFileName[128];
	int			nTexBoundID;
	int			nType;
	int			nStatus;
	float		fLonMin, fLonMax, fLatMin, fLatMax;
};



struct MAP_TEX
{
	double			dLongLatVertex[4][2]; // 꼬지점 4 개의 위경도 좌표
	double			dUTMVertex[4][2];	  // 꼬지점 4 개의 UTM 좌표
	
	float 			fMapSize;
	int				nTexLevel;
	int				nTexComponent;
	int				nId; 
	int				nType;
	char			strTexFileName[128];
};


class CEasyOpenGL
{
public:
	void	Gp2Utm(const double lon_rad, const double lat_rad, 
						 double *gridzone, double *east_mtr, double *north_mtr);

	void	utm2llh( double *llh, double x, double y, int zone, char zone_char);
	void	ConvertDegToString60(float fDeg, char *strDeg60);
public:
	HDC				m_hGLDC;
	HGLRC			m_hGLRC;
	HWND			m_hGLWnd;


	float			m_fAspectRatio;
	float			m_fFOV;
	float			m_fNearClippingDistance;
	float			m_fFarClippingDistance;
	float			m_fScreenZoomScale;

	int				m_nWndWidth;
	int				m_nWndHeight;
	RECT			m_wndRect;

	int				m_nCenterX;
	int				m_nCenterY;
	int				m_nSpaceX;
	int				m_nSpaceY;

	float			m_fInitMinX;
	float			m_fInitMaxX;
	float			m_fInitMinY;
	float			m_fInitMaxY;
	
	
	float			m_fMinX,m_fMaxX;
	float			m_fMinY,m_fMaxY;

	GL_2D_VECTOR	m_VScreenSize;


	float			m_fCenterX;
	float			m_fCenterY;
	float			m_fScaleX;
	float			m_fScaleY;
	//				마우스 위치
	float			m_fPosUTMX;
	float			m_fPosUTMY;
	float			m_fPosLong;
	float			m_fPosLat;
	char			m_strLong[64];
	char			m_strLat[64];

	float			m_fScreenMoveX;
	float			m_fScreenMoveY;


	CEasyMouse		EasyMouse;

	double			m_ratio;

	int				m_maxViewport;
	int				m_nofViewport;
//	int				m_focusedViewport;
//	int				m_focusedViewportSave;
//	int				m_pickedViewport;			// MENU_VIEW는 picked는 되지만 focused는 되지 않는다.
	int				m_onAirViewport;
	int				m_nMapOption; // 0 위성, 1 지도 
	int				m_nMap3D; // 0 2D, 1 3D 
	int				m_nViewMode; // 0 2D, 1 3D 


//	Viewport*		m_viewport;
//// Font
	CEasyGLFont		m_CFont[MAX_FONT_TYPE];    // 글씨체 
	void			Printf(int	x, int y, char *str, int nFontID);
	void			Printf3D(int	x, int y, int z, char *str, int nFontID);
	

//////////////////////////////////////////
	CEasyTexture	m_CMyTexture;
	int				m_nTexture;
	TEXLIST1		m_TextureList[MAX_TEXTURE];
	unsigned int	m_nTextureBoundID[ MAX_TEXTURE ];
	void			ReadMapTextureFile(char *sFileName);
/// Dynamics Map
	// BMP Texture
	int				m_nNoDynMapTex;
	unsigned int	m_dynMapTexID[MAX_TEXTURE];
	MAP_TEX			m_dynMapTex[MAX_TEXTURE];
	void			ReadDyanamicMapTextureFile (char *sFileName);
	/// DDS Texture
	CEasyTexture	m_CDDSTexture;
	int				m_nNoDDSPatch;
	unsigned int	m_DDSTexBoundID[1000];
	PATCH			m_DDSPatch[1000];
	void			ReadDDSTextureFile( char* filename );

public:
	CEasyOpenGL(void);
	~CEasyOpenGL(void);


	int		Open( HWND hWnd, int colorDepth = 32, int width = 1024, int height = 768, int nofViewport = 1 );
	void	SetRC();
	void	Close();
	void	InitParameters();

	void	SetCanvas(RECT *rect);
	int		SetViewport( char* viewportName, double xPos, double yPos, double width, double height );
	void	SetPerspectiveView();
	void	SetOrtho3DView(float	left_x, float	right_x, float	btm_y, float	top_y, float	neart_z, float	far_z);
	void	SetZoomScale(float fInput, float fMin, float fMax);

	int		ViewportName2ID( char* name );
	int		NewViewport( char* name );
	int		AddViewport( char* viewportName, double xPos, double yPos, double width, double height );
	void	Activate();
	void	Inactivate();
	void	ResizeRC(int width, int height);			// Resize And Initialize The GL Window

	void	OnAirViewport( int viewportID );
	void	EnableViewport( int viewportID );
	void	DisableViewport( int viewportID );

	HDC		GetCanvasDC()		{ return m_hGLDC; }
	int		GetCanvasWidth()	{ return m_nWndWidth; }
	int		GetCanvasHeight()	{ return m_nWndHeight; }
/////////////////////////////////////////////////////
	void	LoadTexture( );
	
	void	SetColor(int r,int g, int b);
	void	SetColor(int color_id) ;

	void	DrawColorTable(int  x, int y, int  w, int h, int nStep);
	void	SetTableColor(float fValue, float fValueRange);


	void	ConvertWordToScreen2D(float wx, float wy, int *sx, int *sy);
	void	DrawLine(float xs, float ys, float zs, float xe, float ye, float ze);


	void	Draw2DScreenDisplay();
	void	DrawAC(float fSize);



	//////
	///  2018.06.24
	///   UAT_AC 항공기 그리기
	///   항공기 위치를 ADS_B UAT 양식으로  변환하여 보내는 실제 값을 확인하기 위함 
	void	DrawADS_B_UAT_AC(float fSize);

	void	DrawADS_B_GDL90_AC(float fSize);
	void	DrawCADPAircraft(float fSize);
	void	DrawCollisionPoint(float fSize);

	void	DrawADS_B_GBT_AC(float fSize);

	void	DrawTest();
	void	DrawFlightScenarioTrack();
	void	DrawAireraftID();

	

	void	DrawGridScale();
	void	DrawGridCircle(float cx, float cy);
	void	DrawOrigenAxis(float	axis_size);
	void	DrawOrigenAxisWithScale(float	axis_size, int noScale);



	void	Draw3DCoordinate( float length, float width,  
	int x_color, int y_color, int z_color, char x_name[], char y_name[], char z_name[]);
	void	DrawCircle2D(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int n, int option);
	void	DrawCircle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat azimuth, GLfloat incidence, GLfloat r, int n, int option);
	void	Draw2DBox(GLfloat x, GLfloat y, GLfloat w, GLfloat h, int option);
	void	Draw2DBoxWithLabel(GLfloat x, GLfloat y, GLfloat w, GLfloat h, int option,char ch[]);

	void	Draw2DRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, int option);
	void	DrawKoreaMap();
	void	DrawFlightPath();
	void	DrawDebriefACPoistion(float fT);

	void	DrawRectangle(float x, float y, float w, float h);
	void	DrawCenterRectangle(float x, float y,float z,  float w, float h);

	void	DrawAircraft(float fLong, float fLat, float fAlt, float fHeading);

	void	DrawGDL90Aircraft(float fLong, float fLat, float fAlt, float fHeading, int type, float fSize);
	void	DrawGBTAircraft(float fLong, float fLat, float fAlt, float fHeading, int type, float fSize);




	void	GetPickPosition();

	void	RenderOnViewport();
	void	RenderAll3DContents();
	void	RenderAll2DContents();

	void	ShowPickPosition();
	void	ShowJoyStickInput(int nX, int nY, int nShow);
	void	ShowCSSSSendMessage(int nX, int nY, int nShow);
	void	ShowFlightPathData(int nX, int nY, int nShow);
	void	ShowHILSUDPInput(int nX, int nY, int nShow);
	void	ShowGeneralInformation(int nX, int nY, int nShow);
	void	ShowACInformation(int nShow);
	void	ShowACInformation2D(int nShow);
	int		ShowMouseInput(int nX, int nY, int nShow);

	void	ShowDebugInformation( );

	void	Server();



	void	KCEICreate(HWND hWnd);
	void	KCEIOnCreate();



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
