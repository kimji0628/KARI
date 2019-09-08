#include "stdafx.h"
#include "Light.h"

Light::Light()
{
	m_maxNofLight	= 0;

	m_light			= NULL;
}

Light::~Light()
{
	if (m_light != NULL)
	{
		delete[] m_light;
		m_light = NULL;
	}
}

int
Light::InitLight( int maxNofLight, int maxNofLightModel )
{
	m_maxNofLight		= maxNofLight;
	m_maxNofLightModel	= maxNofLightModel;

	// --------------- light ---------------
	if ( ( m_light = new LIGHT[maxNofLight] ) == NULL )
	{
		MessageBox( NULL, "Cannot alloc light buffer!", "ERROR", MB_OK|MB_ICONEXCLAMATION );
		return false;
	}

	memset( m_light, 0, sizeof(LIGHT) * maxNofLight );

	// --------------- lightModel ---------------
	if ( ( m_lightModel = new LIGHT_MODEL[maxNofLightModel] ) == NULL )
	{
		MessageBox( NULL, "Cannot alloc lightModel buffer!", "ERROR", MB_OK|MB_ICONEXCLAMATION );
		return false;
	}

	memset( m_lightModel, 0, sizeof(LIGHT_MODEL) * maxNofLightModel );

	return true;
}

void
Light::DeleteLight()
{
	if (m_lightModel != NULL)
	{
		delete[] m_lightModel;
		m_lightModel = NULL;
	}

	if (m_light != NULL)
	{
		delete[] m_light;
		m_light = NULL;
	}
}

int
Light::LightName2ID( char* name )
{
	for ( int i = 0; i < m_maxNofLight; i++ )
	{
		if ( _stricmp( m_light[i].name, name ) == 0 )
			return i;
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////
//	m_light에 light이름과 속성을 집어넣기 위한 방을 만드는데 불과함.
//	만일 같은 이름이 있거나 꽉 찰 경우 -1 return함
//
//	Input : char*	lightName -> Name of the light
//			int		lightType -> INFINITE, LOCAL, SPOT 중 하나.
//
//	lightID : m_light를 access하기위한 array index값
//	lightNo : GL_LIGHT0 + n 에 사용할 0 ~ 7값 
/////////////////////////////////////////////////////////////////////////
int
Light::NewLight( char* lightName, int lightType )
{
	int		lightID = LightName2ID( lightName );

	if ( lightID >= 0 )
	{
		MessageBox(NULL,"Same Light name exist !","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	for ( lightID = 0; lightID < m_maxNofLight; lightID++ )
	{
		if ( !m_light[lightID].name[0] )
			break;
	}

	if ( lightID == m_maxNofLight )
	{
		MessageBox(NULL,"Light instance full!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}


	strcpy( m_light[ lightID ].name, lightName );
	m_light[ lightID ].lightType = lightType;

	return lightID;
}

int
Light::SelectLight( char* lightName )
{
	int		m_currentLightID = LightName2ID( lightName );

	return m_currentLightID;
}

/////////////////////////////////////////////////////////////////
//	Input : char*	lightName -> Name of the light
//			float*	colorArray -> ambient red ~ specular blue
/////////////////////////////////////////////////////////////////
void
Light::SetLightColor( char* lightName, float* ambient, float* diffuse, float* specular )
{
	int		lightID = LightName2ID( lightName );

	if ( lightID < 0 )
		return;

	memcpy( m_light[ lightID ].ambient,		ambient,	sizeof(float)*4 );
	memcpy( m_light[ lightID ].diffuse,		diffuse,	sizeof(float)*4 );
	memcpy( m_light[ lightID ].specular,	specular,	sizeof(float)*4 );
}

/////////////////////////////////////////////////////////////////
//	Input : lightID 0 - 7	( GL_LIGHT0 - GL_LIGHT7 에 해당)
//			lightPos ( x, y, z )
//	Comment : 여러개의 light를 동시에 이동시키기 위하여 
//			  lightID를 줌
/////////////////////////////////////////////////////////////////
void
Light::MoveLight3fv( float* lightPos, int lightID )
{
	if ( lightID < 0 )
		return;

	memcpy( m_light[lightID].pos, lightPos, sizeof(float)*3 );
}

void
Light::MoveLight3f( float lightX, float lightY, float lightZ, int lightID )
{
	if ( lightID < 0 )
		return;
	m_light[lightID].pos[0] = lightX;
	m_light[lightID].pos[1] = lightY;
	m_light[lightID].pos[2] = lightZ;
}

/////////////////////////////////////////////////////////////////
//	Input : x, y, z
//	Comment : m_currentLightID의 polar coord 중심점을 지정
/////////////////////////////////////////////////////////////////
void
Light::SetLightCenter( float x, float y, float z )
{
	int		lightID = m_currentLightID;

	if ( lightID < 0 )
		return;

	m_light[ lightID ].pos[0] = x;
	m_light[ lightID ].pos[1] = y;
	m_light[ lightID ].pos[2] = z;
	if ( !m_light[ lightID ].lightType )
		m_light[ lightID ].pos[3] = 0.0;
	else
		m_light[ lightID ].pos[3] = 1.0;
}

float*
Light::GetLightCenter( char* lightName )
{
	int		lightID = LightName2ID( lightName );

	if ( lightID < 0 )
		return NULL;

	return	m_light[ lightID ].pos;
}

/////////////////////////////////////////////////////////////////
//	Input : az, in
//	Comment : m_currentLightID의 polar angle을 지정
/////////////////////////////////////////////////////////////////
void
Light::SetLightAngle( float az, float in )
{
	float	dist = 500.0f;
	int		lightID = m_currentLightID;

	if ( lightID < 0 )
		return;

	if ( m_light[ lightID ].pos[3] != 0.0 )
	{
		dist = m_light[ lightID ].pos[3];
	}

	m_light[ lightID ].az = az;
	m_light[ lightID ].in = in;

	m_light[ lightID ].pos[0] = (float)( cos( in * D2R ) * cos( az * D2R ) );
	m_light[ lightID ].pos[1] = (float)( cos( in * D2R ) * sin( az * D2R ) );
	m_light[ lightID ].pos[2] = (float)( sin( in * D2R ) );
}

/////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////
void
Light::SetSpotAngle( float az, float in, float cutOff, float exponent )
{
	int		lightID = m_currentLightID;

	if ( lightID < 0 || lightID >= 8 )
		return;

	m_light[ lightID ].az				= az;
	m_light[ lightID ].in				= in;
	m_light[ lightID ].spotCutoff		= cutOff;
	m_light[ lightID ].spotExponent		= exponent;

	m_light[ lightID ].spotDirection[0] = (float)( cos( in * D2R ) * cos( az * D2R ) );
	m_light[ lightID ].spotDirection[1] = (float)( cos( in * D2R ) * sin( az * D2R ) );
	m_light[ lightID ].spotDirection[2] = (float)( sin( in * D2R ) );
}

/////////////////////////////////////////////////////////////////
//	GL_LIGHT0 - GL_LIGHT7 중 Bind된 Light를 GPU로 보낸다.
/////////////////////////////////////////////////////////////////
void
Light::TurnOnLight( int lightNo, int lightID )		// 매번 RenderScene하기전 호출해서 현재의 Light를 다 켠다.
{
	if ( m_light[ lightID ].lightType < 0 )
		return;

	glLightfv( GL_LIGHT0 + lightNo,		GL_AMBIENT,					m_light[ lightID ].ambient );
	glLightfv( GL_LIGHT0 + lightNo,		GL_DIFFUSE,					m_light[ lightID ].diffuse );
	glLightfv( GL_LIGHT0 + lightNo,		GL_SPECULAR,				m_light[ lightID ].specular );

	if ( m_light[ lightID ].lightType != LIGHT_TYPE_INFINITE && m_light[ lightNo ].attenuation[0] != 0.0 )
	{
		glLightf( GL_LIGHT0 + lightNo,	GL_CONSTANT_ATTENUATION,	m_light[ lightID ].attenuation[0] );
		glLightf( GL_LIGHT0 + lightNo,	GL_LINEAR_ATTENUATION,		m_light[ lightID ].attenuation[1] );
		glLightf( GL_LIGHT0 + lightNo,	GL_QUADRATIC_ATTENUATION,	m_light[ lightID ].attenuation[2] );
	}
	else
	{
		glLightf( GL_LIGHT0 + lightNo,	GL_CONSTANT_ATTENUATION,	1.0 );
		glLightf( GL_LIGHT0 + lightNo,	GL_LINEAR_ATTENUATION,		0.0 );
		glLightf( GL_LIGHT0 + lightNo,	GL_QUADRATIC_ATTENUATION,	0.0 );
	}

	if ( m_light[ lightNo ].lightType == LIGHT_TYPE_SPOT )
	{
		glLightf( GL_LIGHT0 + lightNo, GL_SPOT_CUTOFF,	 m_light[ lightID ].spotCutoff );
		glLightf( GL_LIGHT0 + lightNo, GL_SPOT_EXPONENT,	 m_light[ lightID ].spotExponent );

		glLightfv( GL_LIGHT0 + lightNo, GL_SPOT_DIRECTION, m_light[ lightID ].spotDirection );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
int
Light::NewLightModel( char* lightModelName, int localViewer )
{
	int		lightModelID = LightModelName2ID( lightModelName );

	if ( lightModelID >= 0 )
	{
		MessageBox(NULL,"Same LightModel name exist !","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	for ( lightModelID = 0; lightModelID < m_maxNofLightModel; lightModelID++ )
	{
		if ( !m_lightModel[lightModelID].name[0] )
			break;
	}

	if ( lightModelID == m_maxNofLightModel )
	{
		MessageBox(NULL,"LightModel instance full!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}


	strcpy( m_lightModel[ lightModelID ].name, lightModelName );
	m_lightModel[ lightModelID ].localViewer = localViewer;

	return lightModelID;
}

int
Light::LightModelName2ID( char* name )
{
	for ( int i = 0; i < m_maxNofLightModel; i++ )
	{
		if ( _stricmp( m_lightModel[i].name, name ) == 0 )
			return i;
	}

	return -1;
}

/////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////
void
Light::SetLightModelColor( char* lightModelName, float* ambientColor )
{
	int		lightModelID = LightModelName2ID( lightModelName );

	if ( lightModelID < 0 )
		return;

	memcpy( m_lightModel[ lightModelID ].ambient, ambientColor, sizeof(float)*3 );
}

/////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////
void
Light::TurnOnLightModel( char* lightModelName )
{
	int		lightModelID = LightModelName2ID( lightModelName );

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT,			m_lightModel[lightModelID].ambient );
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER ,	m_lightModel[lightModelID].localViewer );
}

