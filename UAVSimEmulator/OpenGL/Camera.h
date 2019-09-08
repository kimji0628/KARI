#if !defined(_CAMERA_H_INCLUDED_)
#define _CAMERA_H_INCLUDED_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string.h>

#include "eGL.h"
#include "Log.h"

#ifndef _MATRIX_DEFINED_
#define	_MATRIX_DEFINED_
typedef	double	Matrix[4][4];
#endif

// -------------------- Camera Angle ---------------------
#define	POLAR_POV		0
#define	FRONT_POV		1
#define	TOP_POV			2
#define	SIDE_POV		3
#define	SCREEN_POV		4

#define	SHIP_POV		5
#define	MISSLE_POV		6
#define	GUN_POV			7
#define	CAMERA_POV		8

#define	PICK_NAME_SIZE	16
#define	MAX_PICK		5000

struct	PICK
{
	float	zMin;
	float	zMax;
	int		names;
	int		pickName[ PICK_NAME_SIZE ];
};

#ifndef	_SIXDOF_
#define	_SIXDOF_
struct	SIXDOF
{
	double		x, y, z;
	double		az, in, tw;
};
#endif

#define	PICK_BUFFER_SIZE	512

#define	NOT_PICK			0
#define	BEFORE_PICK			1
#define	AFTER_PICK			2

//////////////////////////////////////////////////////////////////////
class Camera
{
public:
	int				m_frameWidth;
	int				m_frameHeight;

	double			m_nearClip;
	double			m_farClip;

	//.............. Camera ..........
	double			m_FOV;
	double			m_FOH;

	int				m_cameraMode;				// 0: polat		1: ortho

	// ............ 3D Camera parameter .........
	double			m_polarCenter[3],	m_refPolarCenter[3];
	double			m_polarAz,			m_refPolarAz;
	double			m_polarIn,			m_refPolarIn;
	double			m_polarTw,			m_refPolarTw;
	double			m_polarDist,		m_refPolarDist;
	double			m_scale,			m_refScale;

	SIXDOF				m_cam6DOF;

	double			m_eyePos[3];
	double			m_a, m_b, m_c, m_d;

	eGL				m_cameraMVM;
	eGL				m_inverseCameraMVM;

	// ============= Pick operation 을 위한 변수들 ================
	int				m_nofPicked;
	unsigned int	m_pickBuffer[ PICK_BUFFER_SIZE ];
	unsigned int*	m_pickBuffPtr;						// pick emulation을 위한 ptr
	int				m_pickWidth, m_pickHeight;

	int				m_pickPosX, m_pickPosY;
	PICK			m_pick[ MAX_PICK ];

public:
	Camera();
	virtual		~Camera();

	// Initialize module
	void		SetFOV( double fov )									{ m_FOV = fov; }
	void		SetClipDistance( double nearDist, double farDist )		{ m_nearClip = nearDist;	m_farClip = farDist; }

	void		SetCameraMatrix( int pov, float* lgtPos, int pickMode = 0 );
	void		SetScreenView();									// x y coord를 사용할 때 호출함(0, width, 0, height) lower left 가 (0,0) 위치

	void		SetCameraMode( int mode )								{ m_cameraMode = mode; }
	void		SetPolarTranslate( double* polarCenter );
	void		SetPolarTranslate( double x, double y, double z );
	void		SetPolarDist( double polarDist )						{ m_polarDist = polarDist; }
	void		SetPolarAttitude( double polarAz, double polarIn, double polarTw );
	void		Set2DScale( double scale )								{ m_scale = scale; }
	int			GetCameraMode()											{ return m_cameraMode; };
	double		GetFov()												{ return m_FOV; }
	void		GetClipDistance( double& nearDist, double& farDist )	{ nearDist = m_nearClip;	farDist = m_farClip; }
	double		GetNearClip()											{ return m_nearClip; }
	double		GetFarClip()											{ return m_farClip; }
	void		GetPolarTranslate( double* polarCenter );
	double		GetPolarDist()											{ return m_polarDist; }
	void		GetPolarAttitude( double& polarAz, double& polarIn, double& polarTw );
	double		Get2DScale()											{ return m_scale; }

	void		SetCrossPlane( double a, double b, double c, double d );
	void		Screen2World( int sx, int sy, double w[3] );

//	void		SetLightAngle( float az, float in );
//	void		SetLightPos( float* lgtPos )	{ memcpy( m_lgtPos, lgtPos, sizeof(float)* 4 ); }
	void		InvertMatrix( double* src, double* dest );
	void		SetInverseCameraMVM();

	void		SetPickParam( int pickX, int pickY, int pickWidth, int pickHeight );
};

//extern	Camera	cCamera;

#endif // !defined(_CAMERA_H_INCLUDED_)
