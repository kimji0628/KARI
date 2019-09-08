// 제 작 사     : 심메드 
// 사 업 명     :  
// 비밀분류     : 심메드 대외비 
// 구 매 처     :  
// 모 듈 명     : CObject  
// 화 일 명     : COpenGL.h
// 파일관리번호 : 1.0 
// 최초 제작일  : 2002.5.1
// 코드형식     : C head file 
// 진행형황     : 개발중
// 관리번호     : SIMLIB 1.0 (VER 1.0)
// 사용언어     : C++ 6.0, Open GL  
// 운영체제     : Windows 
// 제 작 자     : 김 주 일  
// 검 수 자     : 김 주 일
////////////////////////////////////////////////
#ifndef _OPENGL_
#define _OPENGL_
#include <gl\gl.h>            // OpenGL
#include <gl\glu.h>           // GLU library
#include <gl\glut.h>          // GLU library
#include <gl\glaux.h>
#include <math.h>

#include "Font.h"
#include "Canvas.h"
#include "DBase.h"

#define DEG_TO_RAD 0.017453292
#ifndef	_D2R_DEFINED_
#define	_D2R_DEFINED_
#define D2R							(3.14159265358979323846264338327950288419716939937510 / 180.0 )
#endif

#ifndef	_R2D_DEFINED_
#define	_R2D_DEFINED_
#define R2D							( 180.0 / 3.14159265358979323846264338327950288419716939937510 )
#endif

#define	M_RAD	   0.017453292

#define	BLACK		0		
#define	WHITE		7	
#define	RED			1
#define	BLUE		4
#define	GREEN 		3
#define	GREY		1015
#define	YELLOW		2
#define	CYAN		1017



#define	RENDER_MODE	   0
#define	SELECTION_MODE	   1


#define	BUTTON_IDLE			0
#define BUTTON_SELECTED		1
#define BUTTON_PRESSED		2
#define	LEFT_BUTTON_IDLE	0
#define	LEFT_BUTTON_UP		1
#define	LEFT_BUTTON_DOWN	2
#define	RIGHT_BUTTON_IDLE	0
#define	RIGHT_BUTTON_UP		1
#define	RIGHT_BUTTON_DOWN	2
#define	BUTTON_UP			0
#define	BUTTON_DOWN			1
#define	LEFT_BUTTON			0
#define	RIGHT_BUTTON		1


#define MAX_MODEL_NAME		32
#define MAX_ATTRIBUTE_NAME	32
#define MAX_STRUCT_NAME		32

#define MAX_STRUCT_NUMBER	3000
#define MAX_MODEL_NUMBER	3000
#define MAX_POLYGON_NUMBER	10000
#define MAX_VERTEX_NUMBER	20000
#define	MAX_COLOR_NUMBER	500

#define	MAX_TEXTURE_NUMBER	600
#define	MAX_WINDOW_NUMBER	10

#define	TERRIAN_WINDOW		0
#define	TEXTURE_WINDOW		1
#define	LIGHT_WINDOW		2
#define	EDITOR_WINDOW		3

#define	EMR_TYPE			0
#define	DXF_TYPE			1


#define	RANDER_3D_PILOT_VIEW	1
#define	RANDER_3D_LOOK_AT_VIEW	2
#define	RANDER_2D				3


/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */

#define	VK_0					0x30
#define	VK_1					0x31
#define	VK_2					0x32
#define	VK_3					0x33
#define	VK_4					0x34
#define	VK_5					0x35
#define	VK_6					0x36
#define	VK_7					0x37
#define	VK_8					0x38
#define	VK_9					0x39

/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */

#define	VK_A					0x41
#define	VK_B					0x42
#define	VK_C					0x43
#define	VK_D					0x44
#define	VK_E					0x45
#define	VK_F					0x46
#define	VK_G					0x47
#define	VK_H					0x48
#define	VK_I					0x49
#define	VK_J					0x4A
#define	VK_K					0x4B
#define	VK_L					0x4C
#define	VK_M					0x4D
#define	VK_N					0x4E
#define	VK_O					0x4F
#define	VK_P					0x50
#define	VK_Q					0x51
#define	VK_R					0x52
#define	VK_S					0x53
#define	VK_T					0x54
#define	VK_U					0x55
#define	VK_V					0x56
#define	VK_W					0x57
#define	VK_X					0x58
#define	VK_Y					0x59
#define	VK_Z					0x5A

#define	AKEY			VK_A
#define	BKEY			VK_B
#define	CKEY			VK_C
#define	DKEY			VK_D
#define	EKEY			VK_E
#define	FKEY			VK_F
#define	GKEY			VK_G
#define	HKEY			VK_H
#define	IKEY			VK_I
#define	JKEY			VK_J
#define	KKEY			VK_K
#define	LKEY			VK_L
#define	MKEY			VK_M
#define	NKEY			VK_N
#define	OKEY			VK_O
#define	PKEY			VK_P
#define	QKEY			VK_Q
#define	RKEY			VK_R
#define	SKEY			VK_S
#define	TKEY			VK_T
#define	UKEY			VK_U
#define	VKEY			VK_V
#define	WKEY			VK_W
#define	XKEY			VK_X
#define	YKEY			VK_Y
#define	ZKEY			VK_Z

#define	ZEROKEY			VK_0
#define	ONEKEY			VK_1
#define	TWOKEY			VK_2
#define	THREEKEY		VK_3
#define	FOURKEY			VK_4
#define	FIVEKEY			VK_5
#define	SIXKEY			VK_6
#define	SEVENKEY		VK_7
#define	EIGHTKEY		VK_8
#define	NINEKEY			VK_9

#define	PAD0			VK_NUMPAD0 
#define	PAD1			VK_NUMPAD1 
#define	PAD2			VK_NUMPAD2 
#define	PAD3			VK_NUMPAD3 
#define	PAD4			VK_NUMPAD4 
#define	PAD5			VK_NUMPAD5 
#define	PAD6			VK_NUMPAD6 
#define	PAD7			VK_NUMPAD7 
#define	PAD8			VK_NUMPAD8 
#define	PAD9			VK_NUMPAD9 

#define	F1KEY			VK_F1
#define	F2KEY			VK_F2
#define	F3KEY			VK_F3
#define	F4KEY			VK_F4
#define	F5KEY			VK_F5
#define	F6KEY			VK_F6
#define	F7KEY			VK_F7
#define	F8KEY			VK_F8
#define	F9KEY			VK_F9
#define	F10KEY			VK_F10
#define	F11KEY			VK_F11
#define	F12KEY			VK_F12

#define HOMEKEY			VK_HOME
#define DELETEKEY		VK_DELETE
#define INSERTKEY		VK_INSERT
#define	SPACEKEY		VK_SPACE
#define	ESCKEY			VK_ESCAPE 
#define	UPARROWKEY		VK_UP 
#define	DOWNARROWKEY	VK_DOWN 
#define	RIGHTARROWKEY	VK_RIGHT 
#define	LEFTARROWKEY	VK_LEFT 
#define	PAGEUPKEY		VK_PAGE_UP 
#define	PAGEDOWNKEY		VK_PAGE_DOWN 
#define	RETKEY			VK_RETURN
#define	PADENTER		VK_ENTER
#define	PADPLUSKEY		VK_ADD 
#define	PADMINUS		VK_SUBTRACT 
#define	TABKEY			VK_TAB
#define	ENDKEY			VK_END

#define	CONTROLKEY		VK_CONTROL
#define	SHIFTKEY		VK_SHIFT
#define ALTKEY			VK_ALT
#define PRINTSCREENKEY	VK_SNAPSHOT

#define	KEY_UP				0
#define	KEY_DOWN			1
#define	MOUSE_UP			0
#define	MOUSE_DOWN			1

typedef struct {
	float x, y, z;
} OGL_VECTOR;

typedef struct {
    long color;
    OGL_VECTOR start;
    OGL_VECTOR end;
    int layer;
} OGL_LINE;

typedef struct {
    long color;
    OGL_VECTOR start;
    int layer;
	char	str[64];
} OGL_TEXT;

typedef struct {
    long color;
    OGL_VECTOR center;
    float	radious;
    int layer;
} OGL_CIRCLE;

typedef struct {
   long color;
   int	vertexNo;
   int	polyIndex;
   int	layer;
   int	texture_id;
   OGL_VECTOR	n;
} OGL_POLYGON;

typedef struct {
   int color;
   int vertexNo;
   int polyIndex;
   int layer;
} OGL_POLYLINE;

typedef struct {
   float x;
   float y;
   float z;
} OGL_VERTEX;

typedef struct {
   int color;
   char name[20];
} OGL_LAYER;


typedef struct {
	float r, g, b;
} OGL_COLOR;


typedef struct {
	long	start_vertex_id;
	long	end_vertex_id;
	OGL_COLOR	color;
}	OGL_POLY_INFORMATION;

typedef struct {
	float	x;
	float	y;
	float	z;
}	OGL_VORTEX_INFORMATION;

typedef struct {
	float x,y,w,h,t; //t = thick
	int	r,g,b;
	int	label_line_number; // 1 또는 2 
	int	button_type;		// Togle = 0, Steady = 1
	int	draw_type;
	int	active;				// 1 active 0 inactive 
	int	button_status;		// 1 selected 0 unselected
	char	label_one[32];
	char	label_two[32];
	char	label_three[32];
}	INTELIGENT_BUTTON;

typedef struct {
	float	x, y, z;
} VERTEX_EMR;


typedef struct {
	float	s, t;
}TEXCEL_COORD;

typedef struct {
	char	attribute[MAX_ATTRIBUTE_NAME];
	int		attribute_id;
	int		texture_id;
	char	draw_type[32];
	int		no_of_vertex;
	int		start_vertex_index;
	int		end_vertex_index;
	OGL_VECTOR 	n;
} POLYGON_EMR;

typedef struct {
	char	model_name[MAX_MODEL_NAME];
	char	draw_type[32];
	int		no_of_polygon;
	int		start_polygon_index;
	int		end_polygon_index;
} MODEL_EMR;


typedef struct {
	char		attribute_name[MAX_MODEL_NAME];
	short		color_id;
	short		red;
	short		green;
	short		blue;
	char		texture[32];
} COLOR_EMR;

typedef struct {
	short		color_id;
	short		red;
	short		green;
	short		blue;
} COLOR_TABLE;	


typedef struct {
	char	struct_name[MAX_STRUCT_NAME];
	int		no_of_struct;
	int		struct_id[20];
	int		no_of_model;
	int		model_id[20];
} STRUCT_EMR;


typedef struct {
	float	x,y,z;
	float	in_r;
	float	out_r;
}LOD_SPHERE;

typedef struct {
	float	x0,y0;
	float	x1,y1;
	float	x2,y2;
	float	x3,y3;
	float	z_top, z_bottom;
}LOD_P_BOX;	

typedef struct {
	float	plane;
	int		flag;	// 0 : smaller_on,  1 : larger_on
}LOD_PLANE;

typedef struct {
	float	x,y,z;
	int		r;	// 0 : smaller_on,  1 : larger_on
	int		active;
}BOUND_VOL;

typedef struct {
	char		struct_name[MAX_STRUCT_NAME];
	int			struct_id;
	int			struct_type;
	int			no_of_model;
	int			no_of_substruct;
	char		sub_struct_name[40][64];
	char		model_name[40][64];
	int			model_id[40];
	BOUND_VOL	bound_bol;
	LOD_SPHERE	lod_sphere;
	LOD_P_BOX	p_box_outside;
	LOD_P_BOX	p_box_inside;
	LOD_PLANE	plane_x;
	LOD_PLANE	plane_y;
	LOD_PLANE	plane_z;
	int			day_mode; //  M : MORNING - 0, D : DAY - 1, E : EVENING - 2 , N : NIGHT -3
} STRUCT_EMR_DB;


typedef struct {
	short	id;
	char	fn[22];
} BITMAP_FILE_ID;

typedef struct {
	GLfloat  ambient[4];
	GLfloat  diffuse[4];	
	GLfloat  specular[4];
	GLfloat  position[4];
} LIGHT_SOURCE;


#ifndef _MATERIAL_
#define _MATERIAL_
struct MATERIAL
{
	float		ambient[4];
	float		diffuse[4];
	float		specular[4];
	float		shineness;
	char		name[64];
	int			boundID;
};

#endif


typedef struct	{
	int	id;
	int	active;
}	ACTIVE_WINDOW;


#ifndef	_LIGHT_
#define	_LIGHT_
struct LIGHT
{
	int			lightType;			// 0 : infinite Light,		1 : local Light,		2: spot Light
	int			boundNo;
	float		pos[4];				// pos[3] -> infinite property

	float		ambient[4];
	float		diffuse[4];
	float		specular[4];
	float		shineness;
	
	float		attenuation[3];
	
	//...... spot light만 해당 ........
	float		spotDirection[3];
	float		spotCutoff;
	float		spotExponent;
	float		az, in;				// direction of Infinite Light & Spot Light

	char		name[64];
};
#endif

typedef struct
{
	float		ambient[3];
	int			localViewer;
} LMODEL;



typedef	struct _flight_position
{
	float	x;
	float	y;
	float	z;
	float	h;
	float	p;
	float	r;
} OGL_FLIGHT;




#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)

class CGLObject : public Canvas
{
public:
	MyFont		*SmallFont, *MediumFont, *LargeFont;
//	HGLRC		m_hRC;
//	HDC			m_hDC;
	HPALETTE	m_hPalette;
//	HWND		m_hWnd;

	int			m_nofDB;
	DBase*		m_movDB;
	int			m_nofMovObj;
	Model*		m_movObj;

	char			m_dbPath[256];

	int			m_defaultMatID;
	int			m_lightTexID;

	int			m_renderFlag;
	int			m_oneShotFlag;
	int			m_prevMatID;
	int			m_prevTexID;
	int			m_prevMultiTexID;
	int			m_dispSW;

	Material		m_defaultMat;

	int			m_currentTimeOfDay;
	double			m_timeElapsed;
	TIMEOFDAY		m_timeOfDay[ 4 ];			// dawn day dusk dark


public:
//	GLint		m_viewport[4];
	int			m_selected_obj_number;
	int			m_current_texture_id;
	int			m_texture_selected;
	int			m_bk_texture_id;
	int			m_pick_pattern;
	int			m_selected_obj[300];
	int			m_wndWidth;
	int			m_wndHeight;
	float		m_aspectRatio;
	float		m_field_of_view;
	float		m_near_clipping_distance;
	float		m_far_clipping_distance;
	float		m_offset_x;
	float		m_offset_y;
	float		m_offset_z;
	float		m_rotate_x;
	float		m_rotate_y;
	float		m_rotate_z;
	float		m_pilot_x;
	float		m_pilot_y;
	float		m_pilot_z;
	float		m_pilot_heading;
	float		m_pilot_pitch;
	float		m_pilot_roll;
public:
	int			m_view_option;	// 0 : pilot view , 1 : birds eye view
	int			m_projection_option; // 0 : perspective , 1 : ortho
	int			m_zoom_active;
	int			m_pan_active;
	int			m_rotate_x_active;
	int			m_rotate_y_active;
	int			m_rotate_z_active;
public:
	int			m_draw_option;  // 0 :wire_frame, 1 : polygon, 2 :texture
	float		update_rate;
public:
	int			m_rightMouse;
	int			m_leftMouse;
	int			m_mouse_x;
	int			m_mouse_y;
	int			m_pressed_x;
	int			m_pressed_y;
	int			m_drag_x;
	int			m_drag_y;
	int			m_show_mouse_x;
	int			m_show_mouse_y;
public:
	char		bitmap_filename[MAX_TEXTURE_NUMBER][32];
	int			no_of_bitmap_filename;
	int			db_type;
public:
	float		ambientLight[4];
	float		diffuseLight[4];
	float		specularLight[4];
	float		lightPos[4];
	float		specref[4];
	float		lightX, lightY, lightZ;
	int			lightMoved;

public:
	BITMAPINFO	*turnel_info[MAX_TEXTURE_NUMBER];
	void		*turnel_bits[MAX_TEXTURE_NUMBER];
	GLubyte		*turnel_rgb[MAX_TEXTURE_NUMBER];
	GLuint		textureId[MAX_TEXTURE_NUMBER];


public:

	Texture		cTexture;
	Material	cMaterial;
	FileName	cFileName;

public:
				CGLObject::CGLObject();
				CGLObject::~CGLObject();
//	int			SetGL(HWND hWnd);
	void		SetRC();

	void		SetOrtho3DView(float	left_x, float	right_x, float	btm_y, float	top_y, float	neart_z, float	far_z);
	void		SetPerspectiveView();
	void		SetPilotView(GLdouble x, GLdouble y, GLdouble z, GLdouble roll, GLdouble pitch, GLdouble heading);
	void		SetColor(int r,int g, int b);
	void		SetColor(int color_id);
	void		InitLight();
	void		SetLightPosition( LIGHT_SOURCE *lgt, float az, float in, float dist, float type );

	void		SetLightSource(LIGHT_SOURCE *lgt);
	void		SetMaterial(MATERIAL *mat, float shininess);


	HPALETTE	GetOpenGLPalette(HDC hDC);
	HGLRC		CreateGLRC(HDC hDC);
	//
	//			font function start
	//
	GLuint		FontCreateBitmaps(HDC hdc,char *typeface,int height,int weight, DWORD italic);
	void		FontPuts(GLuint font,  char   *s);
	void		gl_printf(int x, int y, char *str);
	void		gl_printf_3d(GLfloat x, GLfloat y, GLfloat z, char *str);
	void		gl_d_printf(GLdouble x, GLdouble y, char *str);

	//
	//			texture function start
	//
/*	void		*LoadDIBitmap(char	*filename,	 BITMAPINFO	**info);	
	void		*ReadDIBitmap(BITMAPINFO **info);
	GLubyte		*ConvertRGB(BITMAPINFO *info, void   *bits);
	GLubyte		*ConvertRGBA(BITMAPINFO *info, void  *bits);
	int			SaveDIBitmap(char  *filename,	 BITMAPINFO *info,	void   *bits);
*/	//
	//			draw object function start
	//
	void		axis(float	axis_size);
	void		Draw3DCoordinate( float length, float width,  
		int x_color, int y_color, int z_color, char x_name[], char y_name[], char z_name[]);
	void		CelestialSphere(int glType, float Radius, float cellSize, int tex_id);
	void		RenderPlanet(int glType, float Radius, float cellSize, int tex_id);
	void		circle_3d(GLfloat x, GLfloat y, GLfloat z, GLfloat azimuth, GLfloat m_incidence, GLfloat r, int n, int option);
	//
	//			calculate normal vector
	//
	void		calculate_normal(float v[3][3], float out[3]);
	void		reduce_to_unit(float vector[3]);

	void		InitMovDBase( char* dbName, char* dbFileName, char* path );
	int			LoadMovDBase( char* dbName, char* dbFileName );
	void		DeleteMovDBase();


//  마우스 입력을 처리하기 위한 변수 
private:
 	int		m_iPressX,	m_iPressY;
	int		m_iReleaseX, m_iReleaseY;
	int		m_iX,		m_iY;
	int		m_iPreX,		m_iPreY;
	int		m_iDelX,		m_iDelY;
	bool	m_bKeyStatus;
	bool	m_bLeftMouse;
	bool	m_bRightMouse;
	bool	m_bShiftKey;
	bool	m_bCtrlKey;
	bool	m_bCapsLock;
public:
	//		마우스 입력처리 
	void	HandleMouseMove(CPoint pnt);
	void	HandleRightMouseDown(CPoint pnt);
	void	HandleRightMouseUp(CPoint pnt);
	void	HandleLeftMouseDown(CPoint pnt);
	void	HandleLeftMouseUp(CPoint pnt);
	void	HandleKeyDown(UINT nChar);
	void	HandleKeyUp(UINT nChar);
	void	HandleLeftDblClick(CPoint pnt);

};

typedef struct													// Create A Structure
{
	GLubyte	*imageData;											// Image Data (Up To 32 Bits)
	GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	width;												// Image Width
	GLuint	height;												// Image Height
	GLuint	texID;												// Texture ID Used To Select A Texture
} TextureImage;		

#endif