#include "stdafx.h"
#include "Camera.h"

const Matrix UM = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

Camera::Camera()
{
	m_FOV				= 27.0;
	m_FOH				= 35.0;

	m_cameraMode		= 0;					// polar view default

	// ........... 3D Camera param ............
	m_polarCenter[0]	= 0.0;
	m_polarCenter[1]	= 0.0;
	m_polarCenter[2]	= 0.0;

	m_polarAz			= 0.0;
	m_polarIn			= 0.0;
	m_polarTw			= 0.0;
	m_polarDist			= 1000.0;
	m_scale				= 1.0;
}

Camera::~Camera()
{
}

/***************************************************************************************
CAMERA_MODE 0: Modeler POV camera mode
	world axis center로부터 xlat(polarCenter[3]), rot(polarAz,polarIn,polarTw=0.0)

CAMERA_MODE 1: Driver POV camera mode
	world axis center로부터 xlat(polarCenter[3]), rot(polarAz,polarIn,polarTw)
	vehicle center axis로부터 xlat(offset[3]) rot(camAz,camIn) xlat(0,0,camDist)

CAMEAR_MODE 2: Tracking vehicle & watch attitude
	world axis center로부터 vehicle center까지 xlat(polarCenter[3])
	rot(camAz,camIn) xlat(0,0,camDist)

SetPolarTranslate	: polarCenter[3]
SetPolarAttitude	: polarAz, polarIn, polarTw
SetCameraOffset		: camOffset[3]
SetCameraAngle		: camAz, camIn, camTw
SetCameraDist		: camDist
***************************************************************************************/
void
Camera::SetCameraMatrix( int pov, float* lgtPos, int pickMode )
{
	int			viewport[4];

	glGetIntegerv( GL_VIEWPORT, viewport );

	if ( m_frameWidth != viewport[2] || m_frameHeight != viewport[3] )
	{
		cLog.LogExit( "Camera frame mismatch!\n" );
	}

	// ################################################################################
	// Light setting.
	glLightfv( GL_LIGHT0, GL_POSITION, lgtPos );

	// ....................... Set Camera Angle ........................
	switch ( m_cameraMode )
	{
	case SCREEN_POV:			// Screen View
		if ( pickMode == BEFORE_PICK )
		{
			glSelectBuffer( PICK_BUFFER_SIZE, m_pickBuffer );
			glRenderMode( GL_SELECT );
			glInitNames();

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();
			gluPickMatrix( (double)m_pickPosX, (double)m_pickPosY, m_pickWidth, m_pickHeight, viewport );
			glOrtho( 0, m_frameWidth, 0, m_frameHeight, -m_nearClip / 2.0f, m_farClip / 2.0f );
			glMatrixMode( GL_MODELVIEW );
		}
		else if ( pickMode == AFTER_PICK )
		{
			glMatrixMode( GL_PROJECTION );
			glPopMatrix();
			glMatrixMode( GL_MODELVIEW );

			m_nofPicked = glRenderMode( GL_RENDER );
		}
		else
		{
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, m_frameWidth, 0, m_frameHeight, -m_nearClip / 2.0f, m_farClip / 2.0f );
			glMatrixMode( GL_MODELVIEW );
		}

		glLoadIdentity();

		glTranslated( 0.0, 0.0, -100.0 );					// 카메라를 뒤로 
		break;

	case POLAR_POV:		// Modeler POV camera mode
		if ( pickMode == BEFORE_PICK )
		{
			glSelectBuffer( PICK_BUFFER_SIZE, m_pickBuffer );
			glRenderMode( GL_SELECT );
			glInitNames();

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();
			gluPickMatrix( (double)m_pickPosX, (double)m_pickPosY, m_pickWidth, m_pickHeight, viewport );
			gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
			glMatrixMode( GL_MODELVIEW );
		}
		else if ( pickMode == AFTER_PICK )
		{
			glMatrixMode( GL_PROJECTION );
			glPopMatrix();
			glMatrixMode( GL_MODELVIEW );

			m_nofPicked = glRenderMode( GL_RENDER );
		}
		else
		{
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
			
			glMatrixMode( GL_MODELVIEW );

			m_inverseCameraMVM.LoadIdentity();
			m_inverseCameraMVM.Translated( m_polarCenter[0], m_polarCenter[1], m_polarCenter[2] );
			m_inverseCameraMVM.Rotated( m_polarAz, 'z' );
			m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
			m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );
		}

		glLoadIdentity();

		glTranslated( 0.0, 0.0, -m_polarDist );
		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );
		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );

		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
		break;

	case FRONT_POV:
	case TOP_POV:
	case SIDE_POV:
		if ( pickMode == BEFORE_PICK )
		{
			glSelectBuffer( PICK_BUFFER_SIZE, m_pickBuffer );
			glRenderMode( GL_SELECT );
			glInitNames();

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();
			gluPickMatrix( (double)m_pickPosX, (double)m_pickPosY, m_pickWidth, m_pickHeight, viewport );
			glOrtho( -0.5*m_frameWidth, 0.5*m_frameWidth, -0.5*m_frameHeight, 0.5*m_frameHeight, -m_farClip / 2.0f, m_farClip / 2.0f );
			glMatrixMode( GL_MODELVIEW );
		}
		else if ( pickMode == AFTER_PICK )
		{
			glMatrixMode( GL_PROJECTION );
			glPopMatrix();
			glMatrixMode( GL_MODELVIEW );

			m_nofPicked = glRenderMode( GL_RENDER );
		}
		else
		{
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( -0.5*m_frameWidth, 0.5*m_frameWidth, -0.5*m_frameHeight, 0.5*m_frameHeight, -m_farClip / 2.0f, m_farClip / 2.0f );
			
			glMatrixMode( GL_MODELVIEW );

			m_inverseCameraMVM.LoadIdentity();
			m_inverseCameraMVM.Scaled( 1.0/m_scale, 1.0/m_scale, 1.0/m_scale );
			m_inverseCameraMVM.Translated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );
			m_inverseCameraMVM.Rotated( m_polarAz, 'z' );
			m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
	//		m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );
		}
		glLoadIdentity();

		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );
		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );
		glScaled( m_scale, m_scale, m_scale );
		break;

	case GUN_POV:
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();
		glTranslated( 0.0, 0.0, -m_polarDist );
		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );
		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );

		m_inverseCameraMVM.LoadIdentity();

		m_inverseCameraMVM.Translated( m_cam6DOF.x, m_cam6DOF.y, m_cam6DOF.z );
		m_inverseCameraMVM.Rotated( m_cam6DOF.az, 'z' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.in, 'x' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.tw, 'z' );

		m_inverseCameraMVM.Translated( m_polarCenter[0], m_polarCenter[1], m_polarCenter[2] );
		m_inverseCameraMVM.Rotated( m_polarAz, 'z' );
		m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
		m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );

		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
		break;

	case CAMERA_POV:
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();
		glTranslated( 0.0, 0.0, -m_polarDist );
		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );
		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );

		m_inverseCameraMVM.LoadIdentity();

		m_inverseCameraMVM.Translated( m_cam6DOF.x, m_cam6DOF.y, m_cam6DOF.z );
		m_inverseCameraMVM.Rotated( m_cam6DOF.az, 'z' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.in, 'x' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.tw, 'z' );

		m_inverseCameraMVM.Translated( m_polarCenter[0], m_polarCenter[1], m_polarCenter[2] );
		m_inverseCameraMVM.Rotated( m_polarAz, 'z' );
		m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
		m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );

		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
		break;

	case MISSLE_POV:
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();
		glTranslated( 0.0, 0.0, -m_polarDist );
		
//		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
//		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );

		glRotated( -90.0/*-m_polarIn*/, 1.0, 0.0, 0.0 );
		glRotated( 0.0/*m_polarAz*/, 0.0, 0.0, 1.0 );

//		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );

		glRotated( 90.0-m_cam6DOF.tw, 0.0, 0.0, 1.0 );
		glRotated( m_cam6DOF.in, 0.0, 1.0, 0.0 );
		glRotated( -m_cam6DOF.az, 0.0, 0.0, 1.0 );
		glTranslated( -m_cam6DOF.x, -m_cam6DOF.y, -m_cam6DOF.z );

		m_inverseCameraMVM.LoadIdentity();

		m_inverseCameraMVM.Translated( m_cam6DOF.x, m_cam6DOF.y, m_cam6DOF.z );
		m_inverseCameraMVM.Rotated( m_cam6DOF.az, 'z' );
		m_inverseCameraMVM.Rotated( 90.0-m_cam6DOF.in, 'y' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.tw, 'z' );

		m_inverseCameraMVM.Translated( m_polarCenter[0], m_polarCenter[1], m_polarCenter[2] );
		m_inverseCameraMVM.Rotated( -90.0, 'z' );
		m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
		m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );

		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
		break;

	case SHIP_POV:
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( m_FOV, (double)m_frameWidth / m_frameHeight, m_nearClip, m_farClip );
		glMatrixMode( GL_MODELVIEW );

		glLoadIdentity();
		glTranslated( 0.0, 0.0, -m_polarDist );
		glRotated( -m_polarIn, 1.0, 0.0, 0.0 );
		glRotated( -m_polarAz, 0.0, 0.0, 1.0 );
		glTranslated( -m_polarCenter[0], -m_polarCenter[1], -m_polarCenter[2] );

		m_inverseCameraMVM.LoadIdentity();

		m_inverseCameraMVM.Translated( m_cam6DOF.x, m_cam6DOF.y, m_cam6DOF.z );
		m_inverseCameraMVM.Rotated( m_cam6DOF.az, 'z' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.in, 'x' );
		m_inverseCameraMVM.Rotated( m_cam6DOF.tw, 'z' );

		m_inverseCameraMVM.Translated( m_polarCenter[0], m_polarCenter[1], m_polarCenter[2] );
		m_inverseCameraMVM.Rotated( m_polarAz, 'z' );
		m_inverseCameraMVM.Rotated( m_polarIn, 'x' );
		m_inverseCameraMVM.Translated( 0.0, 0.0, m_polarDist );

		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
		break;
	}
}

void		
Camera::SetPolarTranslate( double* polarCenter )
{
	m_polarCenter[0]	= polarCenter[0];
	m_polarCenter[1]	= polarCenter[1];
	m_polarCenter[2]	= polarCenter[2];
}

void		
Camera::SetPolarTranslate( double x, double y, double z )
{
	m_polarCenter[0]	= x;
	m_polarCenter[1]	= y;
	m_polarCenter[2]	= z;
}

void		
Camera::SetPolarAttitude( double polarAz, double polarIn, double polarTw )
{
	m_polarAz			= polarAz;
	m_polarIn			= polarIn;
	m_polarTw			= polarTw;
}

void
Camera::GetPolarTranslate( double* polarCenter )
{
	polarCenter[0]		= m_polarCenter[0];
	polarCenter[1]		= m_polarCenter[1];
	polarCenter[2]		= m_polarCenter[2];
}

void
Camera::GetPolarAttitude( double& polarAz, double& polarIn, double& polarTw )
{
	polarAz				= m_polarAz;
	polarIn				= m_polarIn;
	polarTw				= m_polarTw;
}

void
Camera::SetCrossPlane( double a, double b, double c, double d )
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
}

void
Camera::Screen2World( int sx, int sy, double w[3] )
{
	double	p, q, r;
	double	l;
	double	x1, y1, z1;
	double	div;
	double	a = m_a, b = m_b, c = m_c, d = m_d;
	double	mouse3DPos[3];

	if ( m_cameraMode == 0 )		// Polar view
	{
		m_inverseCameraMVM.PassMVMd( 0.0, 0.0, 0.0, m_eyePos );
	}
	else
	{
		m_inverseCameraMVM.PassMVMd( sx - m_frameWidth/2.0, sy - m_frameHeight/2.0,
								0.0, m_eyePos );
	}

	m_inverseCameraMVM.PassMVMd( sx - m_frameWidth/2.0, sy - m_frameHeight/2.0,
							-0.5 * m_frameHeight / tan(0.5f*m_FOV*D2R), mouse3DPos );
	x1 = mouse3DPos[0];
	y1 = mouse3DPos[1];
	z1 = mouse3DPos[2];

	p = x1 - m_eyePos[0];
	q = y1 - m_eyePos[1];
	r = z1 - m_eyePos[2];
	l = (float)sqrt( p*p + q*q + r*r );

	p /= l;
	q /= l;
	r /= l;

	div = (a*p + b*q + c*r );
	w[0] = ( b*q*x1 + c*r*x1 - b*p*y1 - c*p*z1 - p*d ) / div;
	w[1] = ( a*p*y1 + c*r*y1 - a*q*x1 - c*q*z1 - q*d ) / div;
	w[2] = ( a*p*z1 + b*q*z1 - a*r*x1 - b*r*y1 - r*d ) / div;
}

void
Camera::SetScreenView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, m_frameWidth, 0, m_frameHeight, -m_farClip / 2.0f, m_farClip / 2.0f );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated( 0.0, 0.0, -m_farClip / 2.0f );		// 카메라를 뒤로 
}

void
Camera::SetInverseCameraMVM()
{
	Matrix camMVM, invcamMVM;

	m_cameraMVM.GetMatrix( (double*)&camMVM );

	InvertMatrix( (double*)&camMVM, (double*)&invcamMVM );

	m_inverseCameraMVM.LoadMatrix( (double*)&invcamMVM );
}

void
Camera::InvertMatrix( double* mat, double* dst ) 
{
	double	tmp[12];
	double	src[16];
	double	det;

	// transpose matrix
	for( int i = 0; i < 4; i++ )
	{
		src[i]			= mat[i*4];
		src[i+4]		= mat[i*4 + 1];
		src[i+8]		= mat[i*4 + 2];
		src[i+12]		= mat[i*4 + 3];
	}

	// calculate pairs for first 8 element(cofactors)
	tmp[0]	= src[10] * src[15];
	tmp[1]	= src[11] * src[14];
	tmp[2]	= src[9]  * src[15];
	tmp[3]	= src[11] * src[13];
	tmp[4]	= src[9]  * src[14];
	tmp[5]	= src[10] * src[13];
	tmp[6]	= src[8]  * src[15];
	tmp[7]	= src[11] * src[12];
	tmp[8]	= src[8]  * src[14];
	tmp[9]	= src[10] * src[12];
	tmp[10]	= src[8]  * src[13];
	tmp[11]	= src[9]  * src[12];

	// calculate first 8 elements (cofactors)
	dst[0]	 = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
	dst[0]	-= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
	dst[1]	 = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
	dst[1]	-= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
	dst[2]	 = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
	dst[2]	-= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
	dst[3]	 = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
	dst[3]	-= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
	dst[4]	 = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
	dst[4]	-= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
	dst[5]	 = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
	dst[5]	-= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
	dst[6]	 = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
	dst[6]	-= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
	dst[7]	 = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
	dst[7]	-= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];

	// calculate pairs for second 8 element (cofactors)
	tmp[0]	= src[2]*src[7];
	tmp[1]	= src[3]*src[6];
	tmp[2]	= src[1]*src[7];
	tmp[3]	= src[3]*src[5];
	tmp[4]	= src[1]*src[6];
	tmp[5]	= src[2]*src[9];
	tmp[6]	= src[0]*src[7];
	tmp[7]	= src[3]*src[4];
	tmp[8]	= src[0]*src[6];
	tmp[9]	= src[2]*src[4];
	tmp[10]	= src[0]*src[5];
	tmp[11]	= src[1]*src[4];

	// calculate second 8 element (cofactors)
	dst[8]	 = tmp[0]*src[13]  + tmp[3]*src[14]  + tmp[4]*src[15];
	dst[8]	-= tmp[1]*src[13]  + tmp[2]*src[14]  + tmp[5]*src[15];
	dst[9]	 = tmp[1]*src[12]  + tmp[6]*src[14]  + tmp[9]*src[15];
	dst[9]	-= tmp[0]*src[12]  + tmp[7]*src[14]  + tmp[8]*src[15];
	dst[10]	 = tmp[2]*src[12]  + tmp[7]*src[13]  + tmp[10]*src[15];
	dst[10]	-= tmp[3]*src[12]  + tmp[6]*src[13]  + tmp[11]*src[15];
	dst[11]	 = tmp[5]*src[12]  + tmp[8]*src[13]  + tmp[11]*src[14];
	dst[11]	-= tmp[4]*src[12]  + tmp[9]*src[13]  + tmp[10]*src[14];
	dst[12]	 = tmp[2]*src[10]  + tmp[5]*src[11]  + tmp[1]*src[9];
	dst[12]	-= tmp[4]*src[11]  + tmp[0]*src[9]   + tmp[3]*src[10];
	dst[13]	 = tmp[8]*src[11]  + tmp[0]*src[8]   + tmp[7]*src[10];
	dst[13]	-= tmp[6]*src[10]  + tmp[9]*src[11]  + tmp[1]*src[8];
	dst[14]	 = tmp[6]*src[9]   + tmp[11]*src[11] + tmp[3]*src[8];
	dst[14]	-= tmp[10]*src[11] + tmp[2]*src[8]   + tmp[7]*src[9];
	dst[15]	 = tmp[10]*src[10] + tmp[4]*src[8]   + tmp[9]*src[9];
	dst[15]	-= tmp[8]*src[9]   + tmp[11]*src[10] + tmp[5]*src[8];

	// calculate determinant
	det = src[0]*dst[0] + src[1]*dst[1] + src[2]*dst[2] + src[3]*dst[3];

	// calculate matrix inverse
	for( int j = 0; j < 16; j++ )
		dst[j] *= det;
}

void
Camera::SetPickParam( int pickX, int pickY, int pickWidth, int pickHeight )
{
	m_pickPosX		= pickX;
	m_pickPosY		= pickY;

	m_pickWidth		= pickWidth;
	m_pickHeight	= pickHeight;
}

