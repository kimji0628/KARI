// Ç¥½Ãºä ¸ðµå 
#define PILOT_MODE		0	// ¿îÀüÀÚ ºä
#define CAMERA_MODE		1	// Ä«¸Þ¶ó ºä
#define TOWER_MODE		2	// Å¸¿ö ºä
#define OBSERVER_MODE	3	// °üÂûÀÚ ºä
#define PERSPEC_MODE	4	// Perspective ºä
#define ORTHO_MODE		5	// Ortho ºä
#define RWY_MODE		6	// RWY ºä

#ifndef	_CONSTANT_DEFINED_
#define	_CONSTANT_DEFINED_
#define		PHI					3.14159265358979323846264338327950288419716939937510
#define		D2R					(PHI / 180.0 )
#define		R2D					( 180.0 / PHI )
// ´ÜÀ§ º¯È¯ °ü·Ã »ó¼ö
#define		FT2M				0.3047999902464
#define		M2FT				3.2808400000000
#define		KPH2FPS				0.91
#define		FEETS_TO_METERS		0.3047999
#define		FEETS_TO_KM			0.0003047999
#define		METERS_TO_FEETS		3.28084097 
#define		NM_TO_FEETS			6076.115
#define		NM_TO_METERS		1852.0
#define		METERS_TO_NM		0.00053999568
#define		FEETS_TO_NM			0.00016457883
#define		FPS_TO_KNOTS		1.68781f
#define		MPS_TO_KNOTS		1.9438
#define		MPS_TO_FPM			196.8505
#endif

#define RWY_POSITION_X		335438.0f
#define RWY_POSITION_Y		3831047.0f

typedef struct {
	float	fX;
	float	fY;
	float	fZ;
	float	fPitchDeg;
	float	fRollDeg;
	float	fYawDeg;
} SIX_DOF;

/////////////////////////////
// ADS_B À» À§ÇØ Á¤ÀÇ
// 2019.03.29
typedef struct {
	float	fX;
	float	fY;
	float	fZ;
	float	fPitchDeg;
	float	fRollDeg;
	float	fYawDeg;
	float	fLatitude;
	float	fLongitude;
	float	fUTMX;
	float	fUTMY;
} SIX_DOF_WGS84_UTM;