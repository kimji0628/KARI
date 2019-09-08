#if !defined(_LIGHT_H_INCLUDED_)
#define _LIGHT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl/gl.h>		// Header File For The GLu32 Library
#include <math.h>

#ifndef	_D2R_DEFINED_
#define	_D2R_DEFINED_
#define D2R							(3.14159265358979323846264338327950288419716939937510 / 180.0 )
#endif

#define	LIGHT_TYPE_INFINITE				1
#define	LIGHT_TYPE_LOCAL				2
#define	LIGHT_TYPE_SPOT					4

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

struct LIGHT_MODEL
{
	float		ambient[4];
	int			localViewer;
	char		name[64];
};

class Light
{
protected:
	int				m_maxNofLight;
	LIGHT*			m_light;
	int				m_currentLightID;	// 현재 사용중인 m_light array ID

	int				m_boundLight[8];	// 각 GL light에 bound된 lightNo

	int				m_maxNofLightModel;
	LIGHT_MODEL*	m_lightModel;

	int				NewLight();

public:
	Light();
	~Light();

	int		InitLight( int maxNofLight, int maxNofLightModel );
	void	DeleteLight();

	//.......... Lighting ..............
	int		NewLight( char* lightName, int lightType );
	int		SelectLight( char* lightName );
	int		LightName2ID( char* name );

	void	SetLightColor( char* lightName, float* ambient, float* diffuse, float* specular );
	void	MoveLight3fv( float* lightPos, int lightID );
	void	MoveLight3f( float lightX, float lightY, float lightZ, int lightID );

	void	SetLightAngle( float az, float in );
	void	SetSpotAngle( float az, float in, float cutOff, float exponent );
	void	SetLightCenter( float x, float y, float z );
	float*	GetLightCenter( char* lightName );
	void	EnableSpotLight( BOOL isSpotLight );
	void	TurnOnLight( int lightNo, int lightID );

	int		NewLightModel( char* lightModelName, int localViewer );
	int		LightModelName2ID( char* name );
	void	SetLightModelColor( char* lightName, float* ambientColor );

	void	TurnOnLightModel( char* lightModelName );
};

//////////////////////////////////////////////////////////////////////

#endif // !defined(_LIGHT_H_INCLUDED_)

//////////////////////////////////////////////////////////////////////
