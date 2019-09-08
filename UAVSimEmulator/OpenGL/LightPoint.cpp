#include "stdafx.h"
#include "LightPoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LightPoint::LightPoint()
{
	m_maxNofLPAppear	= 0;

	m_lpAppear		= NULL;
}

LightPoint::~LightPoint()
{
	RemoveAllLightPointAppear();

	if (m_lpAppear != NULL)
	{
		delete[] m_lpAppear;
		m_lpAppear = NULL;
	}
}

void
LightPoint::InitLightPoint( int maxlpAppear, int maxlpAmin )
{
	if ( maxlpAppear )
	{
		if ( ( m_lpAppear = new LGTPNT_APPEAR[ maxlpAppear ] ) == NULL )
		{
			MessageBox( NULL, "Cannot alloc m_lpAppear memory.", "ERROR", MB_OK|MB_ICONEXCLAMATION );
		}

		m_maxNofLPAppear = maxlpAppear;

		memset( m_lpAppear, 0, sizeof(LGTPNT_APPEAR)*m_maxNofLPAppear );
	}

	if ( maxlpAmin )
	{
		if ( ( m_lpAnim = new LGTPNT_ANIM[ maxlpAmin ] ) == NULL )
		{
			MessageBox( NULL, "Cannot alloc m_lpAnim memory.", "ERROR", MB_OK|MB_ICONEXCLAMATION );
		}

		m_maxNofLPAnim = maxlpAmin;

		memset( m_lpAnim, 0, sizeof(LGTPNT_ANIM)*m_maxNofLPAnim );
	}
}

// ====================================== LightPoint Appearance ======================================
int
LightPoint::LightPointAppearName2ID( char* lpAppearName )
{
	for ( int i = 0; i < m_maxNofLPAppear; i++ )
	{
		if ( m_lpAppear[i].lpName && strcmp( m_lpAppear[i].lpName, lpAppearName ) == 0 )
			return i;
	}

	return -1;
}

int
LightPoint::NewLightPointAppear()
{
	for ( int i = 0; i < m_maxNofLPAppear; i++ )
	{
		if ( !m_lpAppear[i].lpName[0] )
			return i;
	}

	return -1;
}

int
LightPoint::AddLightPointAppear( char* lpAppearName )
{
	int		lpID;
	char	strTmp[128];

	if ( LightPointAppearName2ID( lpAppearName ) != -1 )
	{
		sprintf( strTmp, "LightPoint %s already exits\n", lpAppearName );
		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	if ( ( lpID = NewLightPointAppear() ) == -1 )
	{
		sprintf( strTmp, "OpenGL LightPoint overflows : %s\n", lpAppearName );
		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	strcpy( m_lpAppear[lpID].lpName,	lpAppearName );
	
	return	lpID;			// non zero value for glBindLightPoint
}

int
LightPoint::RemoveLightPointAppear( char* lpAppearName )
{
	int	lpID = LightPointAppearName2ID( lpAppearName );

	if ( lpID == -1 )
		return -1;

	memset( &m_lpAppear[lpID], 0, sizeof(LGTPNT_APPEAR) );

	return true;
}

void
LightPoint::RemoveAllLightPointAppear()
{
	if ( m_lpAppear )
	{
		memset( m_lpAppear, 0, sizeof(LGTPNT_APPEAR)*m_maxNofLPAppear );
	}
}

LGTPNT_APPEAR*
LightPoint::LightPointAppearPtr( char* lpAppearName )
{
	int	lpID = LightPointAppearName2ID( lpAppearName );

	if ( lpID == -1 )
		return NULL;

	return &m_lpAppear[lpID];
}

// ====================================== LightPoint Animation ======================================
int				
LightPoint::NewLightPointAnim()
{
	for ( int i = 0; i < m_maxNofLPAnim; i++ )
	{
		if ( !m_lpAnim[i].lpaName[0] )
			return i;
	}

	return -1;
}

int				
LightPoint::LightPointAnimName2ID( char* lpAnimName )
{
	for ( int i = 0; i < m_maxNofLPAnim; i++ )
	{
		if ( m_lpAnim[i].lpaName && strcmp( m_lpAnim[i].lpaName, lpAnimName ) == 0 )
			return i;
	}

	return -1;
}

int				
LightPoint::AddLightPointAnim( char* lpAnimName )			// return true if success, if fail return false
{
	int		lpaID;
	char	strTmp[128];

	if ( LightPointAppearName2ID( lpAnimName ) != -1 )
	{
		sprintf( strTmp, "LightPoint %s already exits\n", lpAnimName );
		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	if ( ( lpaID = NewLightPointAnim() ) == -1 )
	{
		sprintf( strTmp, "OpenGL LightPoint overflows : %s\n", lpAnimName );
		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	strcpy( m_lpAnim[lpaID].lpaName, lpAnimName );
	
	return	lpaID;			// non zero value for glBindLightPoint
}

int				
LightPoint::RemoveLightPointAnim( char* lpAnimName )
{
	int	lpID = LightPointAnimName2ID( lpAnimName );

	if ( lpID == -1 )
		return -1;

	memset( &m_lpAnim[lpID], 0, sizeof(LGTPNT_ANIM) );

	return true;
}

void			
LightPoint::RemoveAllLightPointAnim()
{
	if ( m_lpAnim )
	{
		memset( m_lpAnim, 0, sizeof(LGTPNT_APPEAR)*m_maxNofLPAnim );
	}
}

LGTPNT_ANIM*
LightPoint::LightPointAnimPtr( char* lpAnimName )
{
	int	lpaID = LightPointAnimName2ID( lpAnimName );

	if ( lpaID == -1 )
		return NULL;

	return &m_lpAnim[lpaID];
}

