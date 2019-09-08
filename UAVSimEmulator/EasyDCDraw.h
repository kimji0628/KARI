#pragma once


typedef struct {
	long	start_vertex_id;
	long	end_vertex_id;
}	SIM_POLYLINE_INFORMATION;

typedef struct {
	float	x;
	float	y;
}	SIM_VORTEX_INFORMATION;

typedef struct {
   long color;
   int vertexNo;
   int polyIndex;
   int layer;
   char	idName[16];
   float	alt;
   float    lalt;
   float    ualt;
} SIM_Polyline;

typedef struct {
   float x;
   float y;
   float z;
} SIM_Vertex;

class CEasyDCDraw
{
	CDC		*m_pDC;
	CPen	m_penRed, m_penGreed,m_penBlue, m_penBlack, m_penCyan;


public:


	int		m_nCenterX;
	int		m_nCenterY;
	int		m_nSpaceX;
	int		m_nSpaceY;
	int		m_nWidth;
	int		m_nHeight;
	
	float	m_fInitMinX;
	float	m_fInitMaxX;
	float	m_fInitMinY;
	float	m_fInitMaxY;
	
	
	float	m_fMinX,m_fMaxX;
	float	m_fMinY,m_fMaxY;
	float	m_fScaleX;
	float	m_fScaleY;
	float	m_fAspectRatio;
	RECT	m_wndRect;
public:
	float	m_fPosUTMX;
	float	m_fPosUTMY;




public:
	CEasyDCDraw(void);
	~CEasyDCDraw(void);

public:
	void	ReadMapData(char	fileName[64]);

public:
	void	SetDC(CDC *pDC) { m_pDC = pDC;}
	void	SetCanvas(RECT *rect);
	void	SetScale(float fScale);
	void	DrawAreaGrid(CDC *pDC, float	fMinLong, float fMaxLat, float fMinLat, float fMaxLong);
	void	DrawRect(CDC *pDC, float x, float y, float w, float h );
	void	DrawLine(CDC *pDC, float sx, float sy, float ex, float ey );
	void	DrawFlightTrack(CDC *pDC);
	void	DrawKoreaMap(CDC *pDC);

	void	DrawGeneralDebug(CDC *pDC);
	void	DrawPickPosition(CDC *pDC);
	void	DrawCircleGrid(CDC *pDC);
	void	DrawCircle(CDC *pDC, float cx, float cy, float r, int n, int option);

	void	DrawAC(CDC *pDC);
	void	DrawServer(CDC *pDC);

};
