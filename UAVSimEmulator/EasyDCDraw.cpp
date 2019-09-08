#include "StdAfx.h"
#include "UAVGUI.h"
#include "EasyDCDraw.h"



// 지도 그리기 
SIM_Polyline		KPolyline[700];
long				polygonNo, polylineNo, vertexNo;
SIM_Vertex			KVertex[230000];
// 미리 좌표를 계산해 놓는다. 
float				KoreaMap[230000][3];
// 미리 좌표를 계산해 놓는다. 
float				KoreaMapLatLong[230000][3];





CEasyDCDraw		EasyDraw;
extern	CUAVGUI	g_GUI;

CEasyDCDraw::CEasyDCDraw(void)
{
	m_penRed.CreatePen(PS_SOLID,2,RGB(255,0,0));
	m_penGreed.CreatePen(PS_SOLID,2,RGB(0,255,0));
	m_penBlue.CreatePen(PS_SOLID,2,RGB(0,0,255));
	m_penBlack.CreatePen(PS_SOLID,2,RGB(0,0,0));
	m_penCyan.CreatePen(PS_SOLID,2,RGB(255,255,0));



	m_fInitMinX = -1000.0f;
	m_fInitMaxX = 1000.0f;
	m_fInitMinY = -1000.0f;
	m_fInitMaxY = 1000.0f;
	ReadMapData("terrian");

	int	i,j,k;
	double dx, dy, gridzone;
	for(i= 0;i<polylineNo;i++)
	{
		k = KPolyline[i].polyIndex;
		for (j = KPolyline[i].polyIndex;j< (KPolyline[i].polyIndex +  KPolyline[i].vertexNo ); j++)
		{
			g_GUI.Gp2Utm(D2R*(KVertex[j].x), D2R*(KVertex[j].y), &gridzone, &dx, &dy);

			KoreaMapLatLong[j][0] = dx - RWY_POSITION_X;
			KoreaMapLatLong[j][1] = dy - RWY_POSITION_Y;
			KoreaMapLatLong[j][2] = 0.0f;

		}
	}
}

CEasyDCDraw::~CEasyDCDraw(void)
{
	m_penRed.DeleteObject();
	m_penGreed.DeleteObject();
	m_penBlue.DeleteObject();
	m_penBlack.DeleteObject();
	m_penCyan.DeleteObject();
}

////////////////////////////////////////////////////////////////
// 한국 지형 해안선 읽기  
void	CEasyDCDraw::ReadMapData(char	fileName[64])
{
	FILE	*in_binary;
	SIM_POLYLINE_INFORMATION tp, *polyline_data=&tp;
	SIM_VORTEX_INFORMATION tv, *vortex_data=&tv;
	int i;
	char	fname[32];
	strcpy(fname, fileName);
	strcat(fname,".map");
	if( (in_binary = fopen(fname,"r+b")) == NULL) 
	{
		printf("can not open %s\n",fname);
		exit(1);
	}
	fread(&polylineNo, sizeof( long ), 1, in_binary);
	for(i=0;i<polylineNo;i++) 
	{
		fread(polyline_data, sizeof( SIM_POLYLINE_INFORMATION ), 1, in_binary);
		KPolyline[i].polyIndex = polyline_data->start_vertex_id;
		KPolyline[i].vertexNo = 	polyline_data->end_vertex_id ;
	}
	fread(&vertexNo, sizeof( long ), 1, in_binary);
	for(i=0;i<vertexNo;i++) 
	{
		fread(vortex_data, sizeof( SIM_VORTEX_INFORMATION ), 1, in_binary);
		KVertex[i].x = vortex_data->x;
		KVertex[i].y = vortex_data->y;
	}
	fclose(in_binary);
}

void	CEasyDCDraw::DrawKoreaMap(CDC *pDC)
{
	char	strTmp[256];
	int		nX, nY;
	int		i, j, k;
	
	float	fX, fY;
	float	fHeight;

	float	fStartLong, fEndLong;
	float	fStartLat, fEndLat;
	float	fPanLong, fPanLat;
	float	fLongScale, fLatScale;
	float	fOrgLat, fOrgLong;

	double	x,y, z;
	double  fXNM, fYNM;

	fStartLong = 126.5f;
	fEndLong   = 128.0f;
	fStartLat = 33.0f;
	fEndLat = 35.0f;

	for(i= 0;i<polylineNo;i++)
	{
		k = KPolyline[i].polyIndex;
		x = KoreaMapLatLong[KPolyline[i].polyIndex][0];//  335438.0f
		y = KoreaMapLatLong[KPolyline[i].polyIndex][1];// 3831047.0f
		z = 0.0f;
		pDC->MoveTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);

		for (j = (KPolyline[i].polyIndex+1) ;j< (KPolyline[i].polyIndex +  KPolyline[i].vertexNo ); j+=2)
		{
			if( KVertex[j].y > fStartLat && KVertex[j].y < fEndLat )
			{
				if( KVertex[j].x > fStartLong && KVertex[j].x  < fEndLong )
				{
					x = KoreaMapLatLong[j][0];
	//				if( x < -300000.0f) x = 110000.0f;

					y = KoreaMapLatLong[j][1];
					z = 0.0f;
					pDC->LineTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);;
				}
			}
		}
	}

	//	pDC->MoveTo(m_nCenterX-100.0f*m_fScaleX, m_nCenterY+100.0f*m_fScaleY);
	//	pDC->LineTo(m_nCenterX+100.0f*m_fScaleX, m_nCenterY+100.0f*m_fScaleY);;
	//	pDC->LineTo(m_nCenterX+100.0f*m_fScaleX, m_nCenterY-100.0f*m_fScaleY);;
	//	pDC->LineTo(m_nCenterX-100.0f*m_fScaleX, m_nCenterY-100.0f*m_fScaleY);;
	//	pDC->LineTo(m_nCenterX-100.0f*m_fScaleX, m_nCenterY+100.0f*m_fScaleY);;




}




void	CEasyDCDraw::DrawAreaGrid(CDC *pDC, float	fMinLong, float fMaxLat, float fMinLat, float fMaxLong)
{
	char		strTmp[256];
	int			nX, nY;

	static double pre_dSystemTime = 0.0f;
	double		dSystemTime;

	static float	fTime = 0.0f;
	int		i;
	float x,y;

	float	leftBtmX, leftBtmY;
	float	rightTopX, rightTopY;
	float	height;
	float	fSpace = 15.0f;
	int		nNoCollum = 6;
	float	fCollumSpace;
	float	fYCenter[6];

	leftBtmX = m_wndRect.left + fSpace*3;
	leftBtmY = m_wndRect.bottom - fSpace;
	rightTopX =  m_wndRect.right - fSpace;
	rightTopY = m_wndRect.top+fSpace*2;


	fCollumSpace = (leftBtmY - rightTopY)/ nNoCollum;

	CPen	penBox;
	penBox.CreatePen(PS_SOLID,3,RGB(125,0,255));
	CPen *oldPen = pDC->SelectObject(&penBox);
//  box
	pDC->MoveTo(leftBtmX, leftBtmY);
	pDC->LineTo(rightTopX ,leftBtmY);
	pDC->LineTo(rightTopX ,rightTopY);
	pDC->LineTo(leftBtmX,rightTopY);
	pDC->LineTo(leftBtmX,leftBtmY);

}


void	CEasyDCDraw::DrawRect(CDC *pDC, float x, float y, float w, float h )
{

	pDC->MoveTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);
	pDC->LineTo(m_nCenterX+(x+w)*m_fScaleX, m_nCenterY-y*m_fScaleY );
	pDC->LineTo(m_nCenterX+(x+w)*m_fScaleX, m_nCenterY-(y+h)*m_fScaleY);
	pDC->LineTo(m_nCenterX+x*m_fScaleX, m_nCenterY-(y+h)*m_fScaleY);
	pDC->LineTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);

}



void	CEasyDCDraw::DrawLine(CDC *pDC, float sx, float sy, float ex, float ey )
{

	pDC->MoveTo(m_nCenterX+sx*m_fScaleX, m_nCenterY-sy*m_fScaleY);
	pDC->LineTo(m_nCenterX+ex*m_fScaleX, m_nCenterY-ey*m_fScaleY );
}


void	CEasyDCDraw::DrawCircle(CDC *pDC, float cx, float cy, float r , int n, int option)
{
	if( option == 1)
	{
		float	sx,sy,ex,ey;
		sx = m_nCenterX + (cx-r)*m_fScaleX;
		sy = m_nCenterY - (cy-r)*m_fScaleY;
		ex = m_nCenterX + (cx+r)*m_fScaleX;
		ey = m_nCenterY - (cy+r)*m_fScaleY;
		pDC->Ellipse(sx,sy,ex,ey);
	}
	else
	{
		int i;
		float	t_x,t_y;
		float	x,y;
		
		t_x = r * cos(0.0f);
		t_y = r * sin((0.0f));
		x = (cx+t_x);
		y = (cy-t_y);
	
		pDC->MoveTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);

		for (i=0;i<360;i+=n)
		{
			t_x = r * cos(i*D2R);
			t_y = r * sin((i*D2R));
			x = (cx+t_x);
			y = (cy-t_y);
			pDC->LineTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);
		}
		t_x = r * cos(0.0f);
		t_y = r * sin((0.0f));
		x = (cx+t_x);
		y = (cy-t_y);
	
		pDC->LineTo(m_nCenterX+x*m_fScaleX, m_nCenterY-y*m_fScaleY);

	}
}




void	CEasyDCDraw::DrawFlightTrack(CDC *pDC)
{
	int		i,j,k;
	float	x, y;


	char		strTmp[256];

	
	pDC->SelectObject(&m_penBlack);

	if( pUAVGUIInterface->nNoWayPoint>0)
	{
		x = m_nCenterX+ (pUAVGUIInterface->wayPoint[0].x-RWY_POSITION_X)*m_fScaleX;
		y = m_nCenterY- (pUAVGUIInterface->wayPoint[0].y-RWY_POSITION_Y)*m_fScaleY;

		pDC->MoveTo(x, y);
		pDC->LineTo(x, y);

		sprintf(strTmp,"SP");
		TextOut(pDC->m_hDC, x, y ,strTmp, strlen(strTmp));

		for(i=1;i<pUAVGUIInterface->nNoWayPoint;i++)
		{
			float	x, y;
			x = m_nCenterX+(pUAVGUIInterface->wayPoint[i].x-RWY_POSITION_X)*m_fScaleX;
			y = m_nCenterY-(pUAVGUIInterface->wayPoint[i].y-RWY_POSITION_Y)*m_fScaleY;

			pDC->LineTo(x, y );

			sprintf(strTmp,"%d",i);
			TextOut(pDC->m_hDC, x, y ,strTmp, strlen(strTmp));
		}
	}



	CPen *oldPen = pDC->SelectObject(&m_penRed);
	for(j=0;j<4;j++)
	{
		if(j==0) pDC->SelectObject(&m_penCyan);
		else if(j==1) pDC->SelectObject(&m_penRed);
		else if(j==2) pDC->SelectObject(&m_penGreed);
		else if(j==3) pDC->SelectObject(&m_penBlue);

		if( pUAVGUIInterface->nNoCSSSWayPoint[j]>0)
		{
			x = m_nCenterX+ (pUAVGUIInterface->CSSSwayPoint[j][0].x-RWY_POSITION_X)*m_fScaleX;
			y = m_nCenterY- (pUAVGUIInterface->CSSSwayPoint[j][0].y-RWY_POSITION_Y)*m_fScaleY;

			pDC->MoveTo(x, y);
			pDC->LineTo(x, y);

			sprintf(strTmp,"SP");
			TextOut(pDC->m_hDC, x, y ,strTmp, strlen(strTmp));

			for(i=1;i<pUAVGUIInterface->nNoCSSSWayPoint[j] ;i++)
			{
				float	x, y;
				x = m_nCenterX+(pUAVGUIInterface->CSSSwayPoint[j][i].x-RWY_POSITION_X)*m_fScaleX;
				y = m_nCenterY-(pUAVGUIInterface->CSSSwayPoint[j][i].y-RWY_POSITION_Y)*m_fScaleY;

				pDC->LineTo(x, y );

				sprintf(strTmp,"%d",i);
				TextOut(pDC->m_hDC, x, y ,strTmp, strlen(strTmp));
			}
		}
	}
	pDC->SelectObject(oldPen);

}

void	CEasyDCDraw::SetCanvas(RECT *rect)
{



	m_wndRect.bottom = rect->bottom;
	m_wndRect.top	= rect->top;
	m_wndRect.right	= rect->right;
	m_wndRect.left	= rect->left;


	m_nWidth = (m_wndRect.right - m_wndRect.left);
	m_nHeight =  (m_wndRect.bottom - m_wndRect.top);

	m_fAspectRatio = (float) m_nWidth / (float) m_nHeight;

	m_nCenterX = m_nWidth/2;
	m_nCenterY = m_nHeight/2;

	m_nSpaceX = 10;
	m_nSpaceY = 10;

	m_fScaleX =float( m_nWidth / ((m_fMaxX - m_fMinX) * m_fAspectRatio));
	m_fScaleY =float( m_nHeight / (m_fMaxY - m_fMinY));


}

void	CEasyDCDraw::SetScale(float fScale)
{



	if( fScale < 1.0f) fScale = 1.0f;
	
	m_fMinX = m_fInitMinX*fScale;
	m_fMaxX = m_fInitMaxX*fScale;
	m_fMinY = m_fInitMinY*fScale;
	m_fMaxY = m_fInitMaxY*fScale;



	m_fScaleX =float( m_nWidth / ((m_fMaxX - m_fMinX) * m_fAspectRatio));
	m_fScaleY =float( m_nHeight / (m_fMaxY - m_fMinY));


}






void	CEasyDCDraw::DrawPickPosition(CDC *pDC)
{
	char		strTmp[256];
	int			nX = 10, nY = 10;
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fOffsetPointX, fOffsetPointY;
	float		fOffsetX, fOffsetY;
	float		fUTMX, fUTMY;
	float		fLong, fLat;

	nY = EasyMouse.m_fPosY;

	sprintf(strTmp,"%.0f,%.0f ", EasyMouse.m_fPosX, EasyMouse.m_fPosY);
	TextOut(pDC->m_hDC, EasyMouse.m_fPosX, nY ,strTmp, strlen(strTmp));

	fOffsetPointX = (EasyMouse.m_fPosX - m_nCenterX);
	fOffsetPointY = -(EasyMouse.m_fPosY - m_nCenterY); // 상하가 바뀜
	nY+=nHSpace;

	sprintf(strTmp,"%.2f,%.2f ", fOffsetPointX, fOffsetPointY);
	TextOut(pDC->m_hDC, EasyMouse.m_fPosX, nY ,strTmp, strlen(strTmp));
	nY+=nHSpace;

	fOffsetX = fOffsetPointX/m_fScaleX;
	fOffsetY = fOffsetPointY/m_fScaleY;
	
	sprintf(strTmp,"%.2f,%.2f ", fOffsetX, fOffsetY);
	TextOut(pDC->m_hDC, EasyMouse.m_fPosX, nY ,strTmp, strlen(strTmp));
	nY+=nHSpace;

	char		strLong[64], strLat[64];
	double		utmPos[3];
	double		llhPos[3];

	fUTMX = utmPos[0] = fOffsetX + RWY_POSITION_X;
	fUTMY = utmPos[1] = fOffsetY + RWY_POSITION_Y;

	g_GUI.utm2llh( llhPos, utmPos[0], utmPos[1], 52, 'S');	//  int zone, char zone_char  );
	fLat =  llhPos[0]*R2D;
	fLong = llhPos[1]*R2D;	

	g_GUI.ConvertDegToString60(fLong, strLong);
	g_GUI.ConvertDegToString60(fLat, strLat);
	sprintf(strTmp,"%s, %s",	strLat, strLong);
	TextOut(pDC->m_hDC, EasyMouse.m_fPosX, nY ,strTmp, strlen(strTmp));
	nY+=nHSpace;

	m_fPosUTMX = fUTMX;
	m_fPosUTMY = fUTMY;


}

void	CEasyDCDraw::DrawCircleGrid(CDC *pDC)
{
	DrawCircle(pDC, 0.0f, 100.0f, 200.0f, 16, 0 );
	DrawCircle(pDC, 0.0f, 0.0f, 400.0f, 16, 0 );
	DrawCircle(pDC, 0.0f, 0.0f, 600.0f, 16, 0 );
	DrawCircle(pDC, 0.0f, 0.0f, 800.0f, 16, 0 );
	DrawCircle(pDC, 0.0f, 0.0f, 1000.0f, 16, 0 );

}


void	CEasyDCDraw::DrawAC(CDC *pDC)
{
	pDC->SelectObject(&m_penCyan);
	DrawCircle(pDC, HILS_AC.m_fX, HILS_AC.m_fY, 10.0f, 16, 1 );
	pDC->SelectObject(&m_penRed);
	DrawCircle(pDC, OtherAC_01.m_fX, OtherAC_01.m_fY, 10.0f, 16, 1 );
	pDC->SelectObject(&m_penGreed);
	DrawCircle(pDC, OtherAC_02.m_fX, OtherAC_02.m_fY, 10.0f, 16, 1 );
	pDC->SelectObject(&m_penBlue);
	DrawCircle(pDC, OtherAC_03.m_fX, OtherAC_03.m_fY, 10.0f, 16, 1 );






}

void	CEasyDCDraw::DrawGeneralDebug(CDC *pDC)
{
	char		strTmp[256];
	int			nX = 10, nY = 10;

	static double pre_dSystemTime = 0.0f;
	double		dSystemTime;

	static float	fTime = 0.0f;
	int		i;
	float	x,y;

	float	leftBtmX, leftBtmY;
	float	rightTopX, rightTopY;
	float	height;
	int		nNoCollum = 6;
	float	fCollumSpace;
	float	fYCenter[6];

	
	int		nHSpace = 15;  // 줄간격 

	sprintf(strTmp,"%.3f", g_CSSSMaster.m_UAVTimer.m_fSystemTime);
	TextOut(pDC->m_hDC, nX, nY ,strTmp, strlen(strTmp)); nY+=nHSpace;



	sprintf(strTmp,"%.3f", EasyMouse.m_fWheel);
	TextOut(pDC->m_hDC, nX, nY ,strTmp, strlen(strTmp)); nY+=nHSpace;


	sprintf(strTmp,"%d  %d ", OtherAC_01.nNextPoint,OtherAC_01.nPassedPoint );
	TextOut(pDC->m_hDC, nX, nY ,strTmp, strlen(strTmp)); nY+=nHSpace;

	



}


void	CEasyDCDraw::DrawServer(CDC *pDC)
{
///  화면 축소 확대
	float	fZoomeScale = 1.0f;
	fZoomeScale =  EasyMouse.m_fWheel;
	if( fZoomeScale < 1.0f ) fZoomeScale = 1.0f;
	SetScale(fZoomeScale);


	float fCenterX = (m_wndRect.right + m_wndRect.left)/2.0f;
	float fCenterY = (m_wndRect.bottom + m_wndRect.top)/2.0f;




	DrawAreaGrid(pDC, 0.0f,0.0f,0.0f,0.0f);
	DrawCircleGrid(pDC);

	pDC->MoveTo(fCenterX, m_wndRect.bottom);
	pDC->LineTo(fCenterX ,m_wndRect.top);

	pDC->MoveTo(m_wndRect.right, fCenterY);
	pDC->LineTo(m_wndRect.left ,fCenterY);


	DrawFlightTrack(pDC);

	DrawKoreaMap(pDC);

	DrawPickPosition(pDC);
	
	
	DrawAC(pDC);	
	
	
	DrawGeneralDebug(pDC);

}
