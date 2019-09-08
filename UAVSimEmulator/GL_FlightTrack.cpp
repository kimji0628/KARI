#include "StdAfx.h"
#include "GL_FlightTrack.h"


CGL_FlightTrack::CGL_FlightTrack(void)
{

	m_nDrawType = 0;
	EasyMouse.m_fDistance = 1000.0f;
}

CGL_FlightTrack::~CGL_FlightTrack(void)
{
}

void	CGL_FlightTrack::DrawSphere3D(float x, float y, float z, float fMsnValue, float fSize, float fScale)
{
	float fRadius;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
/*
	if( fMsnValue < 200.0f)
	{
		glColor4f(1.0f, 1.0f - fMsnValue/1000.0f, 1.0f- fMsnValue/1000.0f, 0.1f);
	}
	else if( fMsnValue < 400.0f)
	{
		glColor4f(1.0f - fMsnValue/1000.0f,1.0f , 1.0f- fMsnValue/1000.0f, 0.5f);
	}
	else if( fMsnValue < 600.0f)
	{
		glColor4f(1.0f, 1.0f, 1.0f- fMsnValue/1000.0f, 0.5f);

	}
	else if( fMsnValue < 800.0f)
	{
		glColor4f(1.0f, 1.0f - fMsnValue/1000.0f, 1.0f- fMsnValue/1000.0f, 0.4f);
	}
	else 
	{
		glColor4f(1.0f, 1.0f - fMsnValue/1000.0f, 1.0f- fMsnValue/1000.0f, 0.6f);
	}
*/
	SetTableColor(fMsnValue,1000.0f);

	if(m_nDrawType == 0)
	{
		fRadius = 1000.0f *  fSize / m_fScreenZoomScale;
	}
	else
	{
		fRadius = 0.002f *  fSize * EasyMouse.m_fDistance;
	}

	glPushMatrix();
		glTranslatef(x,y,z);
		glutSolidSphere(fRadius ,16, 16);
	glPopMatrix();




}


void	CGL_FlightTrack::DrawArrow3D(float x, float y, float z, float fDir, float fSize, float fScale)
{


	float fLength, fHeadSize;
	float	fHeadSizeScale;

	// 100 km/h 일때 파란색
	glColor3f(1- fScale/100.0f, 1- fScale/100.0f, 1.0f);

	if(m_nDrawType == 0)
	{
		float fArrowSize = 10000.0f;
		fLength = fArrowSize *  fSize / m_fScreenZoomScale;
		fHeadSize = fArrowSize * 0.2 *  fSize / m_fScreenZoomScale;
	}
	else
	{
		float fArrowSize = 0.01f;

		fLength = fArrowSize *  fSize* EasyMouse.m_fDistance;
		fHeadSize = fArrowSize *  fSize * 0.3 * EasyMouse.m_fDistance;

	}
 
	fLength *= fScale/7.5f;
	glLineWidth(2);
	glPushMatrix();
		glTranslatef(x,y,z);
		glRotatef(fDir, 0.0f,0.0f,1.0f);
		glBegin(GL_LINES);

			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(fLength, 0.0f, 0.0f);
		glEnd();

		if(m_nDrawType == 0)
		{
			fHeadSizeScale = fHeadSize  / fSize ;
		}
		else
		{
			fHeadSizeScale = fHeadSize / fSize ;
		}


		glBegin(GL_LINE_LOOP);
			glVertex3f(fLength, fHeadSizeScale, 0.0f);
			glVertex3f(fLength, -fHeadSizeScale, 0.0f);
			glVertex3f(fLength+fHeadSizeScale, 0.0f, 0.0f);
			glVertex3f(fLength, fHeadSizeScale, 0.0f);
		glEnd();





	glPopMatrix();
	glLineWidth(1);



}


void	CGL_FlightTrack::Draw2DFlightTracks()
{
	int	i;
	int nOption;
	double x0,y0;
	double x1,y1;
	double x2,y2;
	double x3,y3;
	float	fScreenMoveX;
	float	fScreenMoveY;

	//if( g_Interface.m_nBackGroundColor == 0)
	//{
	//	glClearColor(0.0, 0.0, 0.0, 0.0f );

	//}
	//else
	//{
	//	glClearColor(1.0, 1.0, 1.0, 0.0f );
	//}



//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
	
	m_fAspectRatio = (float) m_nWndWidth/(float)(m_nWndHeight);

	m_fScaleX = ( m_VScreenSize.x *m_fAspectRatio) / (m_nWndWidth);
	m_fScaleY = m_VScreenSize.y / (m_nWndHeight);

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	SetOrtho3DView ( -0.5*m_VScreenSize.x*m_fAspectRatio, 0.5*m_VScreenSize.x*m_fAspectRatio, -0.5*m_VScreenSize.y, 0.5*m_VScreenSize.y, -m_VScreenSize.y, m_VScreenSize.y);



//  마우스 휠 값으로 축소확대하는 것을 오른쪽 마우스 동작으로 바꿈
//	SetZoomScale(EasyMouse.m_fWheel,1.0f, 1000.0f); 
	SetZoomScale(EasyMouse.m_fDistance,1.0f, 10000.0f); 



	//nOption = g_CSSSMaster.m_nMapOption;


	
	glPushMatrix();
		glScalef(m_fScreenZoomScale,m_fScreenZoomScale, 1.0f);
		fScreenMoveX =  EasyMouse.m_fPanX*m_fScaleX/m_fScreenZoomScale;
		fScreenMoveY =  EasyMouse.m_fPanY*m_fScaleY/m_fScreenZoomScale;
//		glTranslated(EasyMouse.m_fPanX*m_fScaleX/m_fScreenZoomScale, -EasyMouse.m_fPanY*m_fScaleY/m_fScreenZoomScale, 0.0);
		glTranslated(fScreenMoveX, -fScreenMoveY, 0.0);

		if( g_Interface.m_nMapDisplay == 1)
		{
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glColor3f(1.0f, 1.0f, 1.0f);
			DrawTerrian();
			glDisable(GL_TEXTURE_2D);
		}	
	


		SurfaceGrid(5000.0, 10);
		glLineWidth(2);
		DrawOrigenAxisWithScale(5000.0, 10);
		glLineWidth(1);


		// 현재 수신 데이터 표시

		if( g_Interface.m_nCurrentReceiveData)
		{
			DrawACPosition();
		}

		// 전체 비행 구간 데이터 표시 
//		if( g_Interface.m_nStatus == 1)
		{
		
			DrawFlightPaths();
		}	

	glPopMatrix();
}

void	CGL_FlightTrack::Draw3DFlightTracks()
{
	int	i;
	int nOption = PERSPEC_MODE;
	double x0,y0;
	double x1,y1;
	double x2,y2;
	double x3,y3;
	float	fScreenMoveX;
	float	fScreenMoveY;


	//nOption = g_CSSSMaster.m_nMapOption;


	if(g_Interface.m_nMapDisplay == 0)
	{	
		glClearColor(0.0, 0.0, 0.0, 0.0f );
	}
	else
	{
		glClearColor(178.0/256.0, 209.0/256.0, 1.0, 0.0f );
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
	
	m_fAspectRatio = (float) m_nWndWidth/(float)(m_nWndHeight);



	glViewport(0, 0, m_nWndWidth, m_nWndHeight);


	nOption = PERSPEC_MODE;

	
	glPushMatrix();



	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;

	
	GL_3D_VECTOR  polor;
	SetPerspectiveView();

	polor.x = EasyMouse.m_fDistance * cos(D2R*EasyMouse.m_fIncidence) * cos(D2R*EasyMouse.m_fAzimuth);
	polor.y = EasyMouse.m_fDistance * cos(D2R*EasyMouse.m_fIncidence) * sin(D2R*EasyMouse.m_fAzimuth);
	polor.z = EasyMouse.m_fDistance * sin(D2R*EasyMouse.m_fIncidence);

	float fAz;
	float	fPan3DX, fPan3DY;
	fAz = EasyMouse.m_fAzimuth-90.0f;
	EasyMouse.m_fPan3DXRotate =  -EasyMouse.m_fPan3DX * cos(fAz * D2R) - EasyMouse.m_fPan3DY * sin(fAz * D2R);
	EasyMouse.m_fPan3DYRotate =  -EasyMouse.m_fPan3DX * sin(fAz * D2R) + EasyMouse.m_fPan3DY * cos(fAz * D2R);

	float	m_fIncrement = 10.0f;
	
	if( gGL_FLightPath.EasyMouse.m_nLeftKey )
	{
		EasyMouse.m_fPan3DX-= m_fIncrement* cos(fAz * D2R);
		EasyMouse.m_fPan3DY-= m_fIncrement* sin(fAz * D2R);;
	}
	if( gGL_FLightPath.EasyMouse.m_nRightKey )
	{
		EasyMouse.m_fPan3DX+= m_fIncrement* cos(fAz * D2R);
		EasyMouse.m_fPan3DY+= m_fIncrement* sin(fAz * D2R);;
	}

	if( gGL_FLightPath.EasyMouse.m_nUpKey )
	{
		EasyMouse.m_fPan3DX+= m_fIncrement* cos((fAz+90) * D2R);
		EasyMouse.m_fPan3DY+= m_fIncrement* sin((fAz+90) * D2R);;
	}
	if( gGL_FLightPath.EasyMouse.m_nDownKey )
	{
		EasyMouse.m_fPan3DX-= m_fIncrement* cos((fAz+90) * D2R);
		EasyMouse.m_fPan3DY-= m_fIncrement* sin((fAz+90) * D2R);;
	}

/*

	if( gGL_FLightPath.EasyMouse.m_nLeftKey )
	{
		EasyMouse.m_fPan3DX-= m_fIncrement;
	}
	if( gGL_FLightPath.EasyMouse.m_nRightKey )
	{
		EasyMouse.m_fPan3DX+= m_fIncrement;
	}
		if( gGL_FLightPath.EasyMouse.m_nUpKey )
	{
		EasyMouse.m_fPan3DY+= m_fIncrement;
	}
	if( gGL_FLightPath.EasyMouse.m_nDownKey )
	{
		EasyMouse.m_fPan3DY-= m_fIncrement;
	}

*/



	gluLookAt(polor.x+EasyMouse.m_fPan3DX, polor.y+EasyMouse.m_fPan3DY, polor.z,	EasyMouse.m_fPan3DX, EasyMouse.m_fPan3DY, 0.0, 0.0,0.0, 1.0f);
			

//	gluLookAt(polor.x+1000, polor.y+500, polor.z,	1000 , 500, 0.0, 0.0,0.0, 1.0f);


	if( g_Interface.m_nMapDisplay == 1)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawTerrian();
	}
	glDisable(GL_TEXTURE_2D);


	SurfaceGrid(5000.0, 10);
	glLineWidth(2);
	DrawOrigenAxisWithScale(5000.0, 10);
	glLineWidth(1);

	
	DrawAltRange(g_Interface.m_nAltDown, g_Interface.m_nAltUp);
	

	// 현재 수신 데이터 표시

	if( g_Interface.m_nCurrentReceiveData)
	{
		DrawACPosition();
	}

//	if( g_Interface.m_nStatus == 1)
	{
		DrawFlightPaths();
	}	
	glPopMatrix();

}





void CGL_FlightTrack::SelectDrawType()
{
	char		strTmp[256];
	int			nHSpace = 15;  // 줄간격 
	int			nWSpace = 100; // 폭 
	int			nNo;
	float		x,y;
	SetOrtho3DView (0, m_nWndWidth, 0, m_nWndHeight, -10, 10);
	
	if( m_nDrawType == 0 )
	{

		m_nViewMode = ORTHO_MODE;
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_nViewMode = PERSPEC_MODE;
		glColor3f(0.5f, 0.7f, 0.7f);
	}
	Draw2DBox(10  , m_nWndHeight - 25,  60, 20, 0);
	sprintf(strTmp,"2D" );
	Printf(30, m_nWndHeight - 22,strTmp, MIDDLE_FONT);
	if( m_nDrawType == 1 )
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else
	{
		glColor3f(0.5f, 0.7f, 0.7f);
	}

	Draw2DBox(80  , m_nWndHeight - 25,  60, 20, 0);
	sprintf(strTmp,"3D" );
	Printf(100, m_nWndHeight -22,strTmp, MIDDLE_FONT);

	glColor3f(1.0f, 0.0f, 0.0f);
	sprintf(strTmp,"Recv Cnt %d" , g_Interface.m_nNoRecvCount);
	Printf(145, m_nWndHeight -22,strTmp, MIDDLE_FONT);



	
}


void CGL_FlightTrack::SetACPosition()
{
		//double dx, dy, gridzone;

		//ACPos[AC_GPS_INS_219].wgd84.fX = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLongitude;
		//ACPos[AC_GPS_INS_219].wgd84.fY = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLatitude;

		//// UTM 좌표계산 
		//g_GUI.Gp2Utm(D2R* EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLongitude, D2R*EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLatitude, &gridzone, &dx, &dy);
		//ACPos[AC_GPS_INS_219].utm.fX = dx;
		//ACPos[AC_GPS_INS_219].utm.fY = dy;

		//// 기준점( 원점 )  좌표계산 
		//ACPos[AC_GPS_INS_219].org.fX = (dx - RWY_POSITION_X);
		//ACPos[AC_GPS_INS_219].org.fY = (dy - RWY_POSITION_Y);
		//ACPos[AC_GPS_INS_219].org.fZ = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAltitude_GPS;

		//ACPos[AC_GPS_INS_219].org.fYawDeg = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fYawAngle;
		//ACPos[AC_GPS_INS_219].org.fPitchDeg  = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fPitchAngle;
		//ACPos[AC_GPS_INS_219].org.fRollDeg  = EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fRollAngle;
}


void CGL_FlightTrack::DrawACPosition()
{
	char		strTmp[256];
	int	i;
	float		x, y, z;
	float		fT; // 임시 시각 변수
	double dx, dy, gridzone;



	glColor3f(1.0f, 1.0f, 1.0f);
	if( g_Interface.m_nDigitalValueData )
	{
		for(i=0;i<MAX_DRON;i++)
		{
			z =    g_Interface.arrayUAVUGV[i].dAltitudeMeters;
			fT = g_Interface.arrayUAVUGV[i].dTime_Measurement_sec;
			Gp2Utm(g_Interface.arrayUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.arrayUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
			x =    dx - RWY_POSITION_X ;
			y =    dy - RWY_POSITION_Y;

			sprintf(strTmp,"%d: V%.0f S%.0f, D%.0f",i,g_Interface.arrayUAVUGV[i].dPayload_Data[0], g_Interface.arrayUAVUGV[i].dWindSpeed_KPH,g_Interface.arrayUAVUGV[i].dWindDirection_deg_0_360);
			Printf3D(x,y,z, strTmp, MIDDLE_FONT);
		}
	}

	for(i=0;i<MAX_DRON;i++)
	{
		z =    g_Interface.arrayUAVUGV[i].dAltitudeMeters;
		fT = g_Interface.arrayUAVUGV[i].dTime_Measurement_sec;

		if( g_Interface.arrayUAVUGV[i].dLongitudeWGS84Deg > 120.0f && g_Interface.arrayUAVUGV[i].dLatitudeWGS84Deg > 33.0f)
		{
			Gp2Utm(g_Interface.arrayUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.arrayUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
			x =    dx - RWY_POSITION_X ;
			y =    dy - RWY_POSITION_Y;
			if( x > g_Interface.m_fMaxX)  
			{
				g_Interface.m_fMaxX = x;
			}
			if( x < g_Interface.m_fMinX)
			{
				g_Interface.m_fMinX = x;
			}
			if( y > g_Interface.m_fMaxY)
			{
				g_Interface.m_fMaxY = y;
			}
			if( y < g_Interface.m_fMinY) 
			{
				g_Interface.m_fMinY = y;

			}

			// 선택된 무인기 3 대
			if( i == g_Interface.m_nDron_1 || i == g_Interface.m_nDron_2 ||  i == g_Interface.m_nDron_3)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			if( g_Interface.m_nOnSphereSymbol)
			{
				DrawSphere3D(x,y,z, g_Interface.arrayUAVUGV[i].dPayload_Data[0], (float) g_Interface.m_nSphereSymbolSize,0.0);
			}
			if( g_Interface.m_nOnArrowSymbol)
			{
				DrawArrow3D(x,y,z, 90.0 - g_Interface.arrayUAVUGV[i].dWindDirection_deg_0_360, (float) g_Interface.m_fSymbolSize,g_Interface.arrayUAVUGV[i].dWindSpeed_KPH);
			}
		}
	}
}


/// 도시 고도 구간 표시하기
void	CGL_FlightTrack::DrawAltRange(float	 btm, float top)
{

	if( g_Interface.m_nDisplayAltRange)
	{
		glEnable(GL_BLEND);
		glColor4f(0.0, 1.0f, 0.0f, 0.2f);
		glBegin(GL_POLYGON);
			glVertex3f(g_Interface.m_fMinX, g_Interface.m_fMinY, btm);
			glVertex3f(g_Interface.m_fMaxX, g_Interface.m_fMinY, btm);
			glVertex3f(g_Interface.m_fMaxX, g_Interface.m_fMaxY, btm);
			glVertex3f(g_Interface.m_fMinX, g_Interface.m_fMaxY, btm);
		glEnd();

		glColor4f(1.0, 1.0f, 0.0f, 0.2f);
		glBegin(GL_POLYGON);
			glVertex3f(g_Interface.m_fMinX, g_Interface.m_fMinY, top);
			glVertex3f(g_Interface.m_fMaxX, g_Interface.m_fMinY, top);
			glVertex3f(g_Interface.m_fMaxX, g_Interface.m_fMaxY, top);
			glVertex3f(g_Interface.m_fMinX, g_Interface.m_fMaxY, top);
		glEnd();
	}

	


	glDisable(GL_BLEND);
	glLineWidth(3.0f);
	glColor3f(0.0, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, btm);
		glVertex3f(0.0f, 0.0f, top);
	glEnd();
	glLineWidth(1.0f);


}

void CGL_FlightTrack::SurfaceGrid(float	axis_size, int noScale)
{
	float	origin[3];
	float	v_line[3];
	float	fSize;
	float	f;
	int		i,j;
	fSize = axis_size / noScale;

	//  x 축

	glRGB(30,30,30);
	for(f=-axis_size ;f < axis_size; f+= fSize)
	{
		glBegin(GL_LINES);
			glVertex3f(f,-axis_size, 0.0f);	
			glVertex3f(f, axis_size, 0.0f);	
		glEnd();
	}
	for(f=-axis_size ;f < axis_size; f+= fSize)
	{
		glBegin(GL_LINES);
			glVertex3f(-axis_size, f, 0.0f);	
			glVertex3f(axis_size ,f, 0.0f);	
		glEnd();
	}

	





}

// 비행궤적에 심볼 그리기
// 선택된 시간 구간만 그리며, 디지털 값은 읽을 수 없음으로 그리지 않음

void CGL_FlightTrack::DrawFlightPaths(void)
{
	char		strTmp[256];
	int			i, j;
	int			nID;
	double dx, dy, gridzone;
	int			nFlagDronActive[MAX_DRON];
	float		x, y, z;

	// 전구간 비행궤적 그리기 여부 확인
	if( g_Interface.m_nAllReange )
	{ 
		// 부분 구간 비행궤적 그리기 
		
		glPushMatrix();
		// 전체 드론 비행체에 대해서
		for(j=0; j<MAX_DRON;j++)
		{

			if( j < 2)
			{
				switch(j)
				{
					case 0 : SetColor(RED); break;
					case 1 : glColor3f(1.0f, 0.5f, 0.0f); break;
					default : break;
				}
			}
			else
			{
				SetColor(j);
			}


			// 비행궤적을 그리기
			if( g_Interface.m_nFlightPathLine)
			{
				glBegin(GL_LINE_STRIP);
				for(i= (g_Interface.RingBufUDP_IGS[j].nFront-1); i >= 0; i--)
				{
					float	 fT;
					fT = g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dTime_Measurement_sec;
					z =    g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dAltitudeMeters;
					// ucUavUgvID  를 Dron ID 로 가정하고 해당 배열 순서와 일치시킴
					Gp2Utm(g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
					x =    dx - RWY_POSITION_X ;
					y =    dy - RWY_POSITION_Y;
					
					glVertex3f(x,y,z);			
				}
				glEnd();
			}
			// 비행체 심볼그리기
			// 바람, 임무 데이터
			for(i= (g_Interface.RingBufUDP_IGS[j].nFront-1); i >= 0; i--)
			{
				float	 fT;
				fT = g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dTime_Measurement_sec;
				z =    g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dAltitudeMeters;
				// ucUavUgvID  를 Dron ID 로 가정하고 해당 배열 순서와 일치시킴
				Gp2Utm(g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
				x =    dx - RWY_POSITION_X ;
				y =    dy - RWY_POSITION_Y;
				
				if( g_Interface.m_nOnSphereSymbol)
				{
					DrawSphere3D(x,y,z, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dPayload_Data[0], (float) g_Interface.m_nSphereSymbolSize,0.0);
				}
				if( g_Interface.m_nOnArrowSymbol)
				{
					DrawArrow3D(x,y,z, 90.0 - g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dWindDirection_deg_0_360, (float) g_Interface.m_fSymbolSize,g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dWindSpeed_KPH);
				}
			}
		}
		glPopMatrix();		
	}
	else
	{

		// 부분 구간 비행궤적 그리기 
		
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		// 전체 드론 비행체에 대해서
		for(j=0; j<MAX_DRON;j++)
		{
			// 비행궤적을 그리기
			if( j < 2)
			{
				switch(j)
				{
					case 0 : SetColor(RED); break;
					case 1 : glColor3f(1.0f, 0.5f, 0.0f); break;
					default : break;
				}
			}
			else
			{
				SetColor(j);
			}

			if( g_Interface.m_nFlightPathLine)
			{
				glBegin(GL_LINE_STRIP);
				for(i= (g_Interface.RingBufUDP_IGS[j].nFront-1); i >= 0; i--)
				{
					float	 fT;
					// 모니터링 모드일때
					if(g_Interface.m_nOperationMode == 0)
					{
						fT = g_Interface.RingBufUDP_IGS[j].fRecvTime[i];
					}
					else
					{
						fT = g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dTime_Measurement_sec;
					}

					z =    g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dAltitudeMeters;

					if( ((g_Interface.m_nAltDown - 1.0) <= z && z < g_Interface.m_nAltUp ) && (g_Interface.m_fStartTime < fT && fT < g_Interface.m_fEndTime ) )
					{
						// ucUavUgvID  를 Dron ID 로 가정하고 해당 배열 순서와 일치시킴
						Gp2Utm(g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
						x =    dx - RWY_POSITION_X ;
						y =    dy - RWY_POSITION_Y;
						
						glVertex3f(x,y,z);

					}
				}
				glEnd();
			}
			// 비행체 심볼그리기
			// 바람, 임무 데이터
			for(i= (g_Interface.RingBufUDP_IGS[j].nFront-1); i >= 0; i--)
			{
				float	 fT;
			
				// 모니터링 모드일때
				if(g_Interface.m_nOperationMode == 0)
				{
					fT = g_Interface.RingBufUDP_IGS[j].fRecvTime[i];
				}
				else
				{
					fT = g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dTime_Measurement_sec;
				}


				z =    g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dAltitudeMeters;
				if( (g_Interface.m_nAltDown <= z && z < g_Interface.m_nAltUp ) && (g_Interface.m_fStartTime < fT && fT < g_Interface.m_fEndTime ) )
				{
					// ucUavUgvID  를 Dron ID 로 가정하고 해당 배열 순서와 일치시킴
					Gp2Utm(g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLongitudeWGS84Deg * D2R, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dLatitudeWGS84Deg *D2R, &gridzone, &dx, &dy);
					x =    dx - RWY_POSITION_X ;
					y =    dy - RWY_POSITION_Y;
					
					if( g_Interface.m_nOnSphereSymbol)
					{
						DrawSphere3D(x,y,z, g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dPayload_Data[0], (float) g_Interface.m_nSphereSymbolSize,0.0);
					}
					if( g_Interface.m_nOnArrowSymbol)
					{
						DrawArrow3D(x,y,z, 90.0 - g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dWindDirection_deg_0_360, (float) g_Interface.m_fSymbolSize,g_Interface.RingBufUDP_IGS[j].BufUAVUGV[i].dWindSpeed_KPH);
					}

				}
			}
		}
		glPopMatrix();
	}
}


void	CGL_FlightTrack::DrawTerrian()
{
	int	i;
	int nOption;
	double x0,y0;
	double x1,y1;
	double x2,y2;
	double x3,y3;
	float	fScreenMoveX;
	float	fScreenMoveY;

	nOption = 0;
	if( nOption == 0)
	{
		glPushMatrix();
//		glScalef(0.6f, 0.6f, 1.0f);
//		glTranslated( -10000.0, -4000.0, 0.0);

		for(i=0;i<m_nNoDynMapTex;i++)
		{ 
			if( m_dynMapTex[i].nType == 0)
			{
				x0 = m_dynMapTex[i].dUTMVertex[0][0];
				y0 = m_dynMapTex[i].dUTMVertex[0][1];

				x1 = m_dynMapTex[i].dUTMVertex[1][0];
				y1 = m_dynMapTex[i].dUTMVertex[1][1];

				x2 = m_dynMapTex[i].dUTMVertex[2][0];
				y2 = m_dynMapTex[i].dUTMVertex[2][1];

				x3 = m_dynMapTex[i].dUTMVertex[3][0];
				y3 = m_dynMapTex[i].dUTMVertex[3][1];		

				glBindTexture(GL_TEXTURE_2D, m_dynMapTexID[i] ); 
				glBegin(GL_POLYGON);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(x0, y0, 0.0f);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(x1, y1, 0.0f);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(x2, y2, 0.0f);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(x3,y3, 0.0f);
				glEnd();
			}
		}
		glPopMatrix();

	}
	else if(nOption == 1)
	{
		glPushMatrix();
//		glScalef(0.6f, 0.6f, 1.0f);
//		glTranslated( -10000.0, -4000.0, 0.0);

		for(i=0;i<m_nNoDynMapTex;i++)
		{ 
			if( m_dynMapTex[i].nType == 1)
			{
				x0 = m_dynMapTex[i].dUTMVertex[0][0];
				y0 = m_dynMapTex[i].dUTMVertex[0][1];

				x1 = m_dynMapTex[i].dUTMVertex[1][0];
				y1 = m_dynMapTex[i].dUTMVertex[1][1];

				x2 = m_dynMapTex[i].dUTMVertex[2][0];
				y2 = m_dynMapTex[i].dUTMVertex[2][1];

				x3 = m_dynMapTex[i].dUTMVertex[3][0];
				y3 = m_dynMapTex[i].dUTMVertex[3][1];		

				glBindTexture(GL_TEXTURE_2D, m_dynMapTexID[i] ); 
				glBegin(GL_POLYGON);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(x0, y0, 0.0f);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(x1, y1, 0.0f);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(x2, y2, 0.0f);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(x3,y3, 0.0f);
				glEnd();
			}
		}
		glPopMatrix();
		
	}
	else if(nOption == 2)
	{
		for(i=0;i<m_nNoDDSPatch;i++)
		{ 
			x0 = (m_DDSPatch[i].fLonMin-128.30)*100.0f;
			y0 = (m_DDSPatch[i].fLatMin-35.225)*100.0f;

			x1 = (m_DDSPatch[i].fLonMax-128.30)*100.0f;
			y1 = (m_DDSPatch[i].fLatMin-35.225)*100.0f;

			x2 = (m_DDSPatch[i].fLonMax-128.30)*100.0f;
			y2 = (m_DDSPatch[i].fLatMax-35.225)*100.0f;

			x3 = (m_DDSPatch[i].fLonMin-128.30)*100.0f;
			y3 = (m_DDSPatch[i].fLatMax-35.225)*100.0f;		
			glBindTexture(GL_TEXTURE_2D, m_DDSTexBoundID[i] );			
			glBegin(GL_POLYGON);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(x0, y0, 0.0f);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(x1, y1, 0.0f);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(x2, y2, 0.0f);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(x3,y3, 0.0f);
			glEnd();
		}
	}

}

void CGL_FlightTrack::DrawDisplayTimeRange(void)
{

	float	fLeftX, fStartX, fEndX, fRightX;
	float   fRangeWidth;
	float   fWidth;
	float	fScale;
	

	SetOrtho3DView (0, m_nWndWidth, 0, m_nWndHeight, -10, 10);
	
	fLeftX = 280.0f;
	fRightX =  m_nWndWidth - 20;


	fWidth = m_nWndWidth - 300;
	fScale = fWidth/g_UAVTimer.GetElapseTime();
	fStartX =fLeftX + (g_UAVTimer.GetElapseTime() - g_Interface.m_fTimeSpan -  g_Interface.m_fOffsetTime)*fScale;
	if( fStartX < fLeftX )
	{
		fStartX = fLeftX ;
	}
	fEndX = fLeftX + (g_UAVTimer.GetElapseTime() - g_Interface.m_fOffsetTime)*fScale; 
	if( fEndX < fLeftX )
	{
		fEndX = fLeftX ;
	}
	fRangeWidth = g_Interface.m_fOffsetTime*fScale;


 


	glColor4f(1.0f, 1.0f, 0.0f, 0.2f);
	Draw2DBox(280   , m_nWndHeight - 25, m_nWndWidth - 300, 20, 1);
	glColor4f(1.0f, 0.0f, 0.0f, 0.6f);

	Draw2DRect(fStartX , m_nWndHeight - 25, fEndX , m_nWndHeight - 5, 1);
	glColor3f(1.0f, 1.0f, 1.0f);


	char	strTmp[64];

	sprintf(strTmp,"S : %.0f",g_Interface.m_fStartTime  );
	Printf(fStartX , m_nWndHeight -22,strTmp, MIDDLE_FONT);

	sprintf(strTmp,"E : %.0f",g_Interface.m_fEndTime  );
	Printf(fEndX - 60.0f , m_nWndHeight -22,strTmp, MIDDLE_FONT);

	sprintf(strTmp,"Run : %.0f",g_UAVTimer.GetElapseTime()  );
	Printf(m_nWndWidth - 70 , m_nWndHeight -42,strTmp, MIDDLE_FONT);


}

extern int						g_nRecvByte;

void	CGL_FlightTrack::ShowDebugInformation()
{
	char	strTmp[64];
	float	fLeftX, fStartX, fEndX, fRightX;
	fStartX = 20;


//	sprintf(strTmp,"g_nRecvByte %d ",g_nRecvByte );
//	Printf(10 , m_nWndHeight -50,strTmp, MIDDLE_FONT);

	//sprintf(strTmp,"3D PrePan X %.0f Y %.0f",EasyMouse.m_fPrePan3DX, EasyMouse.m_fPrePan3DY  );
	//Printf(fStartX+200 , m_nWndHeight -50,strTmp, MIDDLE_FONT);

	//sprintf(strTmp,"3D RotPan X %.0f Y %.0f",EasyMouse.m_fPan3DXRotate, EasyMouse.m_fPan3DXRotate  );
	//Printf(fStartX+380 , m_nWndHeight -70,strTmp, MIDDLE_FONT);

	
}
void CGL_FlightTrack::Server(void)
{
	char		strTmp[256];
	
	int			nX, nY,  nGap;;
	int			nXStart = 10;
	int			nYStart = 20;


	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fScreenX = 1920, ScreenY = 1080;
	float		fScaleX, fScaleY;




	float	 fStartTime =0.0f;
	g_Interface.m_fEndTime = g_UAVTimer.GetElapseTime() - g_Interface.m_fOffsetTime;

	if( g_Interface.m_fEndTime <= 0.0f)
	{
		g_Interface.m_fEndTime = 0.0f;
		g_Interface.m_fStartTime = 0.0f;

	}
	else
	{
		fStartTime  = g_Interface.m_fEndTime - g_Interface.m_fTimeSpan;
		
		if( fStartTime > 0.0f)
		{
			g_Interface.m_fStartTime = fStartTime;
		}
		else
		{
			g_Interface.m_fStartTime = 0.0f;
		}
	}



	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);




	if(m_nDrawType == 0)
	{
		Draw2DFlightTracks();

	}
	else
	{
		Draw3DFlightTracks();
	}

	
	glColor3f(1.0f, 1.0f, 0.0f);


	// 2D, 3D 도시 형태를 화면에서 마우스로 선택
	SelectDrawType();

	DrawDisplayTimeRange();
	ShowDebugInformation();
	DrawColorTable(m_nWndWidth - 50,  m_nWndHeight - 70,  50, 200 , 10);
	
	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));

}

