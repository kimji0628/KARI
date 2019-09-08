#if !defined(_LIGHTPOINT_H_INCLUDED_)
#define _LIGHTPOINT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glaux.h>	// Header File For The Glaux Library
#include <gl/glext.h>



//////////////////////////////////////////////////////////////////////
struct	LGTPNT_APPEAR
{
	char			lpName[256];
	int				lpDirectionalityType;
	float			lpMinPixelSize;
	float			lpMaxPixelSize;
	float			lpActualPixelSize;
	float			lpVisibilityRange;
	int				lpTOD;						// TOD_HIDE_ON_DAY, TOD_HIDE_ON_DUSK, TOD_HIDE_ON_DARK

	float			lpHorizLobeAngle;
	float			lpVertLobeAngle;
	float			lpLobeRollAngle;
	float			lpLobeFallOff;

	float			lpAmbientIntensity;

	bool			lpNoBackColor;
	float			lpBackColorIntensity;

	BYTE			color[4];
	BYTE			backColor[4];
};

struct	LGTPNT_ANIM
{
	char			lpaName[256];
	int				lpaType;
	int				lpaRotOn;
	int				lpaFlashOn;
	int				lpaRotDirection;				// if true CCW
	int				lpaSeqLength;
	float			lpaPeriod;
	float			lpaPhaseDelay;
	float			lpaTimeOn;

	BYTE			color[4];
	BYTE			backColor[4];
};

class LightPoint
{
protected:			// private method 만 ID로 호출함	
	int				m_maxNofLPAppear;
	LGTPNT_APPEAR*	m_lpAppear;

	int				m_maxNofLPAnim;
	LGTPNT_ANIM*	m_lpAnim;

public:				// public method는 lpName으로 interface됨
	LightPoint();
	~LightPoint();

	void			InitLightPoint( int maxlpAppear, int maxlpAnim );

	// ------------------------- < LightPoint Appearance > ----------------------
	int				NewLightPointAppear();
	int				AddLightPointAppear( char* lpAppearName );			// return true if success, if fail return false
	void			SetDirectionalityType( int type );
	void			SetPixelSize( int lpID, float actualPixelSize, float minPixelSize, float maxPixelSize );
	void			SetTODMode( int lpID, int tod );
	void			SetColor( int lpID, float coPtr, float backCoPtr = NULL );

	int				RemoveLightPointAppear( char* lpAppearName );
	void			RemoveAllLightPointAppear();
	int				LightPointAppearName2ID( char* lpAppearName );
	LGTPNT_APPEAR*	LightPointAppearPtr( char* lpAppearName );

	// ------------------------- < LightPoint Animation > ----------------------
	int				NewLightPointAnim();
	int				AddLightPointAnim( char* lpAnimName );			// return true if success, if fail return false
	int				LightPointAnimName2ID( char* lpAppearName );

	int				RemoveLightPointAnim( char* lpAnimName );
	void			RemoveAllLightPointAnim();
	LGTPNT_ANIM*	LightPointAnimPtr( char* lpAnimName );
};

//////////////////////////////////////////////////////////////////////

#endif // !defined(_LIGHTPOINT_H_INCLUDED_)

//////////////////////////////////////////////////////////////////////
