#include "stdAfx.h"
#include "COpenGL.h"

#include	"DBase.h"


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



#define	 MAX_OBJECT_NO 10
#define	 MAX_DB_NO   10





/* == Morning light model.......................................... */
LIGHT lightParm[4] = {
	{
    0.0f,	0.0f,	1.0f,	1.0f,
    1.0f,	0.5f,	0.5f,
    1.0f,	0.5f,	0.5f,
    1.0f,	0.5f,	0.5f
	},

	{
    0.3f,	0.0f,	.99f,	0.0f,
	0.0f,	0.0f,	0.0f,
    1.0f,	1.0f,	1.0f,
    1.0f,	1.0f,	1.0f,
	},

	{
    0.1f,   -0.99f,   0.2f,	0.0f,
    0.0f,	0.0f,	0.0f,
    0.55f,	0.5f,	0.5f,
    1.0f,	1.0f,	1.0f,
	},

	{
    0.3f,	0.0f,	0.99f,	0.0f,	
	0.0f,	0.0f,	0.0f,
	0.05f,	0.05f,	0.05f,
    1.0f,	1.0f,	1.0f,
	}
};

LMODEL lmodelParm[4] = {
	{ 0.8f,		0.8f,	0.8f,	FALSE },
	{ 0.6f,		0.6f,	0.6f,	FALSE },
	{ 0.4f,		0.35f,	0.35f,	FALSE },
	{ 0.01f,	0.01f,	0.01f,	FALSE }
};


CGLObject::CGLObject()
{
	m_field_of_view = 35.0f;
	m_near_clipping_distance = 5.0f;
	m_far_clipping_distance = 40000.0f;
	m_view_option = 0;
	m_offset_x = 0.0f;
	m_offset_y = 0.0f;
	m_offset_z = 0.0f;
	m_zoom_active = 0;
	m_pan_active = 0;
	m_rotate_x_active = 0;
	m_rotate_y_active = 0;
	m_rotate_z_active = 0;

	m_texture_selected = FALSE;
	m_bk_texture_id = 15;
	m_pick_pattern = 0;
//	cTexture.InitTexture( MAX_TEXTURE_NUMBER * 3 + 10 );

	m_movObj = NULL;
	m_movDB  = NULL;


	m_movObj	= new Model[MAX_OBJECT_NO];
	m_movDB		= new DBase[MAX_DB_NO];

	m_nofMovObj	= 0;
	m_nofDB		= 0;

}

CGLObject::~CGLObject()
{
	wglMakeCurrent(m_hDC, NULL);

}


void	CGLObject::SetRC()
{
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	glClearColor(.01f, 0.05f, 0.1f, 0.0f );
	glPolygonMode(GL_FRONT_AND_BACK,GL_POLYGON);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void CGLObject::circle_3d(GLfloat x, GLfloat y, GLfloat z, GLfloat azimuth, GLfloat incidence, GLfloat r, int n, int option)
{
	int i;
	float	t_x,t_y, t_z;
	float	i_x, i_y, i_z;

	float	a_x, a_y, a_z;

	if(option == 0) 	glBegin(GL_LINE_STRIP);
	else 	glBegin(GL_POLYGON);
	for (i=0;i<360;i+=n)
	{

		t_x = (float)(x + r * cos(i*M_RAD));
		t_y = (float)(y + r * sin(i*M_RAD));
		t_z = (float)(0.0f);
		i_x = t_x * cos(incidence * M_RAD) - t_z * sin(incidence * M_RAD);
		i_y = t_y;
		i_z = t_x * sin(incidence * M_RAD) + t_z * cos(incidence * M_RAD);
		a_x = i_x * cos(azimuth * M_RAD) - i_y * sin(azimuth * M_RAD);
		a_y = i_x * sin(azimuth * M_RAD) + i_y * cos(azimuth * M_RAD); ;
		a_z = i_z;
		glVertex3f(a_x,a_y, a_z);

	}
	t_x = (float)(x + r * cos(i*M_RAD));
	t_y = (float)(y + r * sin(i*M_RAD));
	t_y = (float)(0.0f);
	i_x = t_x * cos(incidence * M_RAD) - t_z * sin(incidence * M_RAD);
	i_y = t_y;
	i_z = t_x * sin(incidence * M_RAD) + t_z * cos(incidence * M_RAD);
	a_x = i_x * cos(azimuth * M_RAD) - i_y * sin(azimuth * M_RAD);
	a_y = i_x * sin(azimuth * M_RAD) + i_y * cos(azimuth * M_RAD); ;
	a_z = i_z;
	glVertex3f(a_x,a_y, a_z);
	glEnd();
}


void CGLObject::axis(float	axis_size)
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



void CGLObject::Draw3DCoordinate( float length, float width,  
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


void	CGLObject::RenderPlanet(int glType, float Radius, float cellSize, int tex_id)
{

	float	x, y, z;
	float	latitude;
	float	longitude;
	static  float angle = 0.0f;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id ); 
	angle+=10.0f;
	if (angle > 360.0f ) angle = 0.0f;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	for (longitude = 0.0f; longitude < 360.0; longitude+=cellSize)
	{
		float   radius;
		float	sx, sy;
		for (latitude=-90.0f ;latitude<= 90.0f ; latitude+=cellSize)
		{
			glBegin(glType);				
				z = (float)(Radius * sin((latitude + cellSize)* D2R));
				radius = (float)(Radius * cos((latitude+ cellSize) * D2R));
				x = (float)(radius * cos((longitude + cellSize)* D2R));
				y =(float)( radius * sin((longitude  + cellSize)* D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);

				sx = (longitude + cellSize)/ 360.0f;
				sy = (90.0f + (latitude + cellSize))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);

				z = (float)(Radius * sin((latitude + cellSize) * D2R));
				radius = (float)(Radius * cos((latitude + cellSize) * D2R));
				x = (float)(radius * cos(longitude * D2R));
				y =(float)( radius * sin(longitude * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);

				sx = (longitude)/ 360.0f;
				sy = (90.0f +  (latitude + cellSize))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);


				z = (float)(Radius * sin(( latitude)  * D2R));
				radius = (float)(Radius * cos((latitude) * D2R));
				x = (float)(radius * cos(longitude * D2R));
				y =(float)( radius * sin(longitude * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);
				
				sx = (longitude)/ 360.0f;
				sy = (90.0f + (latitude))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);

				z = (float)(Radius * sin(( latitude)  * D2R));
				radius = (float)(Radius * cos((latitude) * D2R));
				x = (float)(radius * cos((longitude + cellSize)  * D2R));
				y =(float)( radius * sin((longitude + cellSize) * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);
				
				sx = (longitude + cellSize)/ 360.0f;
				sy = (90.0f + (latitude))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);

			glEnd();
		}	
	}
	glEnd();
	glPopMatrix();
}


void	CGLObject::CelestialSphere(int glType, float Radius, float cellSize, int tex_id)
{


	float	x, y, z;
	float	latitude;
	float	longitude;
	static  float angle = 0.0f;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,tex_id ); 
	angle+=10.0f;
	if (angle > 360.0f ) angle = 0.0f;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	for (longitude = 0.0f; longitude < 360.0; longitude+=cellSize)
	{
		float   radius;
		float	sx, sy;
		for (latitude=-90.0f ;latitude<= 90.0f ; latitude+=cellSize)
		{
			glBegin(glType);				

				z = (float)(Radius * sin(( latitude)  * D2R));
				radius = (float)(Radius * cos((latitude) * D2R));
				x = (float)(radius * cos((longitude + cellSize)  * D2R));
				y =(float)( radius * sin((longitude + cellSize) * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);
				
				sx = (longitude + cellSize)/ 360.0f;
				sy = (90.0f + (latitude))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);
			

				z = (float)(Radius * sin(( latitude)  * D2R));
				radius = (float)(Radius * cos((latitude) * D2R));
				x = (float)(radius * cos(longitude * D2R));
				y =(float)( radius * sin(longitude * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);
				
				sx = (longitude)/ 360.0f;
				sy = (90.0f + (latitude))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);
				z = (float)(Radius * sin((latitude + cellSize) * D2R));
				radius = (float)(Radius * cos((latitude + cellSize) * D2R));
				x = (float)(radius * cos(longitude * D2R));
				y =(float)( radius * sin(longitude * D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);
				sx = (longitude)/ 360.0f;
				sy = (90.0f +  (latitude + cellSize))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);


				z = (float)(Radius * sin((latitude + cellSize)* D2R));
				radius = (float)(Radius * cos((latitude+ cellSize) * D2R));
				x = (float)(radius * cos((longitude + cellSize)* D2R));
				y =(float)( radius * sin((longitude  + cellSize)* D2R));
				glNormal3f(x/Radius, y/Radius, z/Radius);

				sx = (longitude + cellSize)/ 360.0f;
				sy = (90.0f + (latitude + cellSize))  / 180.0f; 
				glTexCoord2f(sx, sy);
				glVertex3f(x, y, z);

			glEnd();
		}	
	}
	glEnd();
	glPopMatrix();
}


void	CGLObject::SetOrtho3DView(float	left_x, float	right_x, float	btm_y, float	top_y, float near_z, float far_z)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left_x, right_x,btm_y, top_y, near_z, far_z);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}






void	CGLObject::SetPerspectiveView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_field_of_view, m_aspectRatio,m_near_clipping_distance, m_far_clipping_distance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void	CGLObject::SetPilotView(GLdouble x, GLdouble y, GLdouble z, GLdouble roll, GLdouble pitch, GLdouble heading)
{

	glRotated(pitch, 1.0, 0.0,0.0);
	glRotated(roll, 0.0, 1.0,0.0);
	glRotated(heading, 0.0, 0.0,1.0);
	glTranslated(-x, -y,-z);
	
//	glRotated(roll, 1.0, 0.0, 0.0);
//	glRotated(pitch, 0.0, 1.0, 0.0);
//	glRotated(heading, 0.0, 0.0,1.0);
//	glTranslated(-x, -y, -z);
}





HPALETTE CGLObject::GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
		{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
		}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


void	CGLObject::SetColor(int r,int g, int b)
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


void	CGLObject::SetColor(int color_id)
{
	if( color_id == 230)
	{
		glColor3f( 0.996,	0.0,0.496);		
	}
	else
		glColor3fv( ColorIndexACAD[color_id]);	
}

void	CGLObject::SetLightPosition( LIGHT_SOURCE *lgt, float az, float in, float dist, float type )
{

	lgt->position [0] = (float)( cos( in * D2R ) * cos( az * D2R ) );
	lgt->position [1] = (float)( cos( in * D2R ) * sin( az * D2R ) );
	lgt->position [2] = (float)( sin( in * D2R ) );
	lgt->position [3] = type;
}

void	CGLObject::SetLightSource(LIGHT_SOURCE *lgt)
{
	GLfloat  whiteLight[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lgt->diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lgt->specular);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lgt->ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,lgt->position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);

}


void	CGLObject::SetMaterial(MATERIAL *mat, float shininess)
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  mat->diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT,  mat->ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, mat->shineness);
}

void CGLObject::InitLight()
{
	/////////////////////////////////////////////////////////////////
	//	Define Lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv( GL_LIGHT0, GL_AMBIENT,  lightParm[ 0].ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  lightParm[ 0].diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, lightParm[ 0].specular );

	/////////////////////////////////////////////////////////////////
	//	Define Light Environment
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT,			lmodelParm[ 0].ambient );
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER ,	lmodelParm[ 0].localViewer );

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

void CGLObject::gl_printf(int x, int y, char *str)
{
	glRasterPos2i( x, y );
	MediumFont->glPrint( "%s", str );
}

void CGLObject::gl_d_printf(GLdouble x, GLdouble y, char *str)
{
	glRasterPos2d( x, y );
	MediumFont->glPrint( "%s", str );
}

void CGLObject::gl_printf_3d(GLfloat x, GLfloat y, GLfloat z, char *str)
{
	glRasterPos3f( x, y, z );
	LargeFont->glPrint( "%s", str );
}

// ============================= Moving Obj Handler ==================================
void
CGLObject::InitMovDBase( char* dbName, char* dbFileName, char* path )
{
	GEO_BUFF	*gp;

/*
	if( m_movObj != NULL){
		DeleteMovDBase();
	}
*/
//	m_movObj	= new Model[1];
//	m_movDB		= new DBase[1];

//	m_nofMovObj	= 1;
//	m_nofDB		= 1;
	

	

	
	strcpy( m_dbPath, path );

	// ------------------ < Read Terrain database file > -------------------------
	if ( LoadMovDBase( dbName, dbFileName ) == -1 )
	{
		cLog.LogExit( "Load-DB \"%s\" fails!\n", dbFileName );
	}

	gp = m_movDB[m_nofMovObj].GeoBuff();

	// ------------------------------- < Default Material > -------------------------------
	m_movObj[m_nofMovObj].SetDefaultMaterial( m_defaultMatID );
	m_movObj[m_nofMovObj].SetLgtTexID( m_lightTexID );

	gp->defaultMatID	= m_defaultMatID;

	m_movObj[m_nofMovObj].SetAirportXform( NULL );


	m_nofMovObj	++;
	m_nofDB		++;
	if(m_nofMovObj >= MAX_OBJECT_NO)
	{
		cLog.LogExit( "모델이 최대갯수 10을 초과합니다. \n");
	}

}

int
CGLObject::LoadMovDBase( char* dbName, char* dbFileName )
{
	GEO_BUFF*	gp;
	int			i;

	m_movDB[m_nofMovObj].LoadDB( dbName, dbFileName, m_dbPath, cFileName.GetWorkingDirectory(), NULL );

	gp = m_movDB[m_nofMovObj].GeoBuff();

	if ( gp->nofTexture )
	{
		m_movObj[m_nofMovObj].InitTexture( gp->nofTexture );

		for ( i = 0; i < gp->nofTexture; i++ )
		{
			gp->texList[i].boundID = m_movObj[m_nofMovObj].AddTexture( gp->texList[i].texName, gp->texList[i].texFileName, true );

			sTEXTURE*	tp = m_movObj[m_nofMovObj].TexPtr( gp->texList[i].texName );

			memcpy( &gp->texList[i], tp, sizeof(sTEXTURE) );

//			cLog.Log( "DB[%d] : %s -> %d\n", gp->texList[i].extRefID, gp->texList[i].texName, gp->texList[i].boundID );

			if ( gp->texList[i].boundID == -1 )
			{
				gp->texList[i].boundID = 0;
				cLog.Log( "Texture loading error in DB[%d] %s\n", gp->texList->extRefID, gp->texList[i].texFileName );
			}
		}
	}

	if( gp->nofMaterial )
	{
		m_movObj[m_nofMovObj].InitMaterial( gp->nofMaterial );

		for ( i = 0; i < gp->nofMaterial; i++ )
		{
			gp->matList[i].boundID = m_movObj[0].AddMaterial( gp->matList[i].name, (MATERIAL*)&gp->matList[i] );
		}
	}

	gp->defaultMatID	= gp->matList[0].boundID;

	m_movDB[m_nofMovObj].LinkMatAndTexID();

	m_movObj[m_nofMovObj].SetGeoBuffer( gp );
	m_movObj[m_nofMovObj].SetConrolSW( &m_renderFlag, &m_oneShotFlag, &m_prevMatID, &m_prevTexID, &m_prevMultiTexID, &m_dispSW, &m_currentTimeOfDay, m_timeOfDay, &m_timeElapsed );

//	m_movObj[0].SetTraverseCallbackFunc( &DrawBV );

	return true;
}

void
CGLObject::DeleteMovDBase()
{
	int		i;
	m_defaultMat.RemoveAllMaterials();	// 1개

	//m_cloudTex.RemoveAllTexture();		// cloudDawn.tga, cloudDawn.bmp, ...cloudDark.tga, cloudDark.bmp,   8 개
										// sky_01.bmp, sky_02.bmp, lenz01.tga 이상 총 11개

//	DeleteLight();						// Light4개 LightModel 4개

	for(i=0; i< m_nofMovObj;i++)
	{
		m_movObj[i].RemoveAllMaterials();
		m_movObj[i].RemoveAllTexture();

		m_movDB[i].FreeGeoBuff();
	}

	delete[] m_movObj;
	delete[] m_movDB;

	m_renderFlag		= 0;
	m_oneShotFlag		= false;
	m_prevMatID			= -1;
	m_prevTexID			= -1;

	m_dispSW			= 0;

//	m_currentAirport	= -1;

	m_movDB				= NULL;
	m_movObj				= NULL;
}




void CGLObject::HandleKeyUp(UINT nChar)
{
	m_bKeyStatus = KEY_UP;
}

void CGLObject::HandleKeyDown(UINT nChar)
{
	m_bKeyStatus = KEY_DOWN;
}

void CGLObject::HandleLeftMouseUp(CPoint pnt)
{
	m_bLeftMouse = MOUSE_UP;
	m_iReleaseX = pnt.x;
	m_iReleaseY = pnt.y;
}

void CGLObject::HandleLeftMouseDown(CPoint pnt)
{
	m_bLeftMouse = MOUSE_DOWN;
	m_iPressX = pnt.x;
	m_iPressY = pnt.y;

}

void CGLObject::HandleRightMouseUp(CPoint pnt)
{
	m_bRightMouse = MOUSE_UP;
	m_iReleaseX = pnt.x;
	m_iReleaseY = pnt.y;

}

void CGLObject::HandleRightMouseDown(CPoint pnt)
{
	m_bRightMouse = MOUSE_DOWN;
	m_iPressX = pnt.x;
	m_iPressY = pnt.y;

}

void CGLObject::HandleLeftDblClick(CPoint pnt)
{
}

void CGLObject::HandleMouseMove(CPoint pnt)
{

	m_iX  = pnt.x;
	m_iY  = pnt.y;
	m_iDelX = (m_iPreX - m_iX);
	m_iDelY = (m_iPreY - m_iY);
	m_iPreX = m_iX;
	m_iPreY = m_iY;

}
