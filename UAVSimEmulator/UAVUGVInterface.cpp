#include "StdAfx.h"


#include "UDPCom.h"

CUDPCom					g_UDPCom;
CUAVUGVInterface		g_Interface;
CMyTimer				g_UAVTimer;
sUDP_Data_2_IGS_Type	g_RecvMsg;

int						g_nRecvByte = 0;


/////////////////////////////////////////////
// UAV-UGV 영상엔진에 테스트 데이터 보내기
// 써버 및 클라이언트 병용

void run_master_module(void *dummy)
{
	unsigned char	buf[246];
	int				i, 	nSize, nResult;

	float    pTime = 0.0f;

	g_Interface.ReadConfigFile("config.txt");
	

	// 서버
	if(g_Interface.m_nOperationMode == 0)
	{
		if(g_UDPCom.InitUDPServer(g_Interface.m_nPortNo, 0,  1))
		{
			AfxMessageBox("UDP Comm Server Open 오류");
			exit(0);
		}

	}
	// 클라이언트(Test Mode)
	else
	{
		if(g_UDPCom.InitUDPClient(g_Interface.m_nPortNo, g_Interface.m_strIPAddress, 0, 1))
		{
			AfxMessageBox("UDP Comm Client Open   오류");
			exit(0);
		}
	}

	g_UAVTimer.SetStartTime(0.0);

	g_Interface.m_nNoRecvCount = 0;
	while(1)
	{
		Sleep(3);
		g_UAVTimer.PassTime(0.0f);

		g_UAVTimer.m_fSystemTime = g_UAVTimer.GetTimeMilisecond()/1000.0f;
		nSize = sizeof(sUDP_Data_2_IGS_Type);
		// 전체 30 개 무인기 
		if( g_Interface.m_nStatus == 1)
		{
			if(g_Interface.m_nOperationMode == 0)
			{
				int						nRecvByte;
				nRecvByte = g_Interface.RecvDataFromUAVUGV( (BYTE *) &g_RecvMsg, nSize, 0);
				if(nRecvByte == nSize)
				{
					int nID=0;
					g_Interface.m_nNoRecvCount++;
					// 현재 무인기 ID
					nID = g_RecvMsg.ucUavUgvID;
					// 해당 무인기 링 버퍼에 데이터 저장
					memcpy((char *) &g_Interface.RingBufUDP_IGS[nID].BufUAVUGV[g_Interface.RingBufUDP_IGS[nID].nFront], (char *)  & g_RecvMsg, sizeof(sUDP_Data_2_IGS_Type));
					// 현재 수신 데이터는 별도로 저장
					memcpy((char *) &g_Interface.arrayUAVUGV[nID], (char *)  & g_RecvMsg, sizeof(sUDP_Data_2_IGS_Type));










					g_Interface.RingBufUDP_IGS[nID].fRecvTime[g_Interface.RingBufUDP_IGS[nID].nFront] = g_UAVTimer.GetElapseTime();
					// 가장 최근 시간 저장
					if( g_Interface.m_fFinalRecvTime <  g_RecvMsg.dTime_Measurement_sec )
					{
						g_Interface.m_fFinalRecvTime = g_RecvMsg.dTime_Measurement_sec ;
					}


					// 링 버퍼 인덱스 관리
					g_Interface.RingBufUDP_IGS[nID].nFront ++;
					if(g_Interface.RingBufUDP_IGS[nID].nFront >= MAX_BUFFER ) 
					{
						g_Interface.RingBufUDP_IGS[nID].nFront = 0;
						g_Interface.RingBufUDP_IGS[nID].nFirstRound ++;
					}
				}
				// 유효한 데이터 가 수신되고 , 반송 명령 조건일때
	
			}
			else
			{
				if( g_Interface.m_nStatus == 1)
				{
					if( fabs(g_UAVTimer.m_fSystemTime - pTime) > 0.98f)
					{
						g_Interface.SimulationDronFlight();


						for(i=0; i< MAX_DRON;i++)
						{
							nResult = g_UDPCom.SendData((unsigned char*)& g_Interface.arrayUAVUGV[i], nSize, 0);
							// 데이터 송신후에 해당 데이터를 내부 시험용 버퍼에 저장함

							// Dron ID;
							// 해당 Dron ID 에저장
							int		nID = 0;

							sUDP_Data_2_IGS_Type a;

							nID = g_Interface.arrayUAVUGV[i].ucUavUgvID;
							memcpy((char *) &g_Interface.RingBufUDP_IGS[nID].BufUAVUGV[g_Interface.RingBufUDP_IGS[nID].nFront], (char *)  & g_Interface.arrayUAVUGV[i], sizeof(sUDP_Data_2_IGS_Type));

							memcpy((char *) &a, (char *)  & g_Interface.arrayUAVUGV[i], sizeof(sUDP_Data_2_IGS_Type));


							g_Interface.RingBufUDP_IGS[nID].nFront ++;
							if(g_Interface.RingBufUDP_IGS[nID].nFront >= MAX_BUFFER ) 
							{
								g_Interface.RingBufUDP_IGS[nID].nFront = 0;
								g_Interface.RingBufUDP_IGS[nID].nFirstRound ++;
							}
						}
						pTime = g_UAVTimer.m_fSystemTime;
					}
				}
			}
		}
	}
}



CUAVUGVInterface::CUAVUGVInterface(void)
{
	int			i;
	unsigned long thread_id;
	char	*ch=NULL;


	if ( (thread_id = _beginthread(run_master_module, 0,  (void *) ch ) ) < 0)
	{
	
		exit(0);
	}
	else
	{
	

	}

	// 제어 시작, 정지
	m_nStatus  = 0;
	// 도시 형식
	m_nSymbolType = 0;
	// 입력 데이터
	m_nInputDataType = 0;
	// 바람 정보 전체 적용
	m_nAllWIndChange = 0;
	
	// UAV IGS  데이터를 저장할 링버퍼 초기화
	for(i=0;i<MAX_DRON;i++)
	{
		RingBufUDP_IGS[i].nFirstRound = 0;
		RingBufUDP_IGS[i].nFront = 0;
		RingBufUDP_IGS[i].nRear = 0;
	}

	g_Interface.m_nAllReange = 0;
		//      현재 수신되는 데이터 표시
	g_Interface.m_nCurrentReceiveData = 1;
		//      디지털 수치 표시 여부
	g_Interface.m_nDigitalValueData = 0;
		//      비행궤적 표시 여부
	g_Interface.m_nFlightPathLine = 0;

	m_fFinalRecvTime = 0.0f;

	m_nSphereSymbolSize = 10.0f;
	m_fSymbolSize = 10.0f;

	m_nAltDown = 0;
	m_nAltUp = 5000;

	m_nOnSphereSymbol = 1;


	m_fMinX = 100000.0;
	m_fMaxX = -100000.0f;
	m_fMinY = 100000.0f;
	m_fMaxY = -100000.0f;


}

CUAVUGVInterface::~CUAVUGVInterface(void)
{

}




// 111215 UTM=>위경도 변환 추가 - 항우연 제공 skh
// llh : radian
// utmzone_char: 'C' <=  <= 'X'
void CUAVUGVInterface::utm2llh( double *llh, double x, double y, int zone, char zone_char)
{
	double sa, sb;
	double e2, e2cuadrada, c;
	double X, Y;
	double s, lat, v, a, a1, a2, j2, j4, j6, alfa, beta, gama, Bm, b;
	double Epsi, Eps, nab, senoheps, Delt, TaO;
	double longitude, latitude;
	double cosLat, cosLat2;

	sa = 6378137.000000 ; sb = 6356752.314245;

	e2 = sqrt( sa*sa - sb*sb ) / sb;
	e2cuadrada = e2 * e2;
	c = ( sa*sa ) / sb;

	X = x - 500000.;
	if( zone_char > 'M' )	// northern hemisphere, 
		Y = y;
	else						// southern hemisphere, 
		Y = y - 10000000.;

	s = ( ( zone * 6. ) - 183. ); 
	lat =  Y / ( 6366197.724 * 0.9996 );           
	cosLat = cos(lat);
	cosLat2 = cosLat*cosLat;
	v = ( c / sqrt( 1 + e2cuadrada * cosLat2 ) ) * 0.9996;
	a = X / v;
	a1 = sin( 2. * lat );
	a2 = a1 * cosLat2;
	j2 = lat + ( a1 / 2. );
	j4 = ( ( 3. * j2 ) + a2 ) / 4.;
	j6 = ( ( 5. * j4 ) + ( a2 * cosLat2) ) / 3.;
	alfa = ( 3. / 4. ) * e2cuadrada;
	beta = ( 5. / 3. ) * alfa*alfa;
	gama = ( 35. / 27. ) * alfa*alfa*alfa;
	Bm = 0.9996 * c * ( lat - alfa * j2 + beta * j4 - gama * j6 );
	b = ( Y - Bm ) / v;
	Epsi = ( e2cuadrada*a*a/2. ) *cosLat2;
	Eps = a * ( 1. - Epsi/3. );
	nab = ( b * ( 1. - Epsi ) ) + lat;
	senoheps = ( exp(Eps) - exp(-Eps) ) / 2.;
	Delt = atan(senoheps / cos(nab) );
	TaO = atan(cos(Delt) * tan(nab));
	longitude = Delt + s*0.0174532925199433;
	latitude = lat + ( 1. + e2cuadrada*cosLat2 - 3./2.*e2cuadrada*sin(lat)*cosLat*(TaO - lat) ) * ( TaO - lat );

	llh[0] = latitude;
	llh[1] = longitude;
}



void CUAVUGVInterface::Gp2Utm(const double lon_rad, const double lat_rad, 
					 double *gridzone, double *east_mtr, double *north_mtr)
{
	double base_lon, base_lat;
	double gzone;
	double e1s, e2s;
	double sin_lat, cos_lat, tan_lat;
	double n;
	double t, t2;
	double c, c2;
	double a, a2, a3, a4, a5, a6;
	double array[4];
	double e4, e6;
	double m, m0;
	double tmp1, tmp2, tmp3;
	
	gzone = (unsigned int)(lon_rad*R2D*(1.0/6.0) + 31.0);
	
	base_lon = (6 * gzone - 183.0)*D2R;
	base_lat = 0.0;  
	
	e1s = ( 2.0 / 298.257223563 - 1.0 / (298.257223563 * 298.257223563) );
	e2s = e1s / (1.0 - e1s);
	
	sin_lat = sin(lat_rad);
	cos_lat = cos(lat_rad);
	tan_lat = tan(lat_rad);
	
	n = 6378137 / sqrt(1 - e1s * sin_lat * sin_lat);
	
	t  = tan_lat * tan_lat;
	t2 = t * t;
	
	c  = e2s * cos_lat * cos_lat;
	c2 = c * c;
	
	a  = (lon_rad - base_lon) * cos_lat;
	a2 = a * a;
	a3 = a * a2;
	a4 = a * a3;
	a5 = a * a4;
	a6 = a * a5;
	
	e4 = e1s * e1s;
	e6 = e4 * e1s;
	
	array[0] = 1.0 - e1s*(1.0/4.0) - e4*(3.0/64.0) - e6*(5.0/256.0);
	array[1] = e1s*(3.0/8.0) + e4*(3.0/32.0) + e6*(45.0/1024.0);
	array[2] = e4*(15.0/256.0) + e6*(45.0/1024.0);
	array[3] = e6*(35.0/3072.0);
	
	if (lat_rad == 0.0) 
	{
		m = 0.0;
	} 
	else 
	{
		m = 6378137 * ( array[0]*lat_rad - array[1]*sin(2*lat_rad) + 
			array[2]*sin(4*lat_rad) - array[3]*sin(6*lat_rad) );
	}

	if (base_lat == 0.0) 
	{
		m0 = 0.0;
	} 
	else 
	{
		m0 = 6378137 * ( array[0]*base_lat - array[1]*sin(2*base_lat) + 
			array[2]*sin(4*base_lat) - array[3]*sin(6*base_lat) );
	}
	
	*gridzone  = gzone;
	
	
	tmp1 = a + (1-t+c)*a3*(1.0/6.0);
	tmp2 = (5 - 18*t + t2 + 72*c - 58*e2s)*a5*(1.0/120.0);

	if( (lon_rad *R2D) >= 126.0f)
	{
		*east_mtr = 0.9996*n*(tmp1+tmp2) + 500000;
	}
	else
	{
		*east_mtr = 0.9996*n*(tmp1+tmp2)-155000;
	}  
	
	tmp1 =  m - m0;
	tmp2 = a2*(1.0/2.0) + (5 - t + 9*c + 4*c2)*a4*(1.0/24.0);
	tmp3 = (61 - 58*t + t2 + 600*c - 330*e2s)*a6*(1.0/720.0);
	*north_mtr = 0.9996*( tmp1 + n*tan_lat*(tmp2+tmp3) );
	
}

///////////////////////////////////////
//
// UAV, UGV 비행 시뮬레이션
// 원형으로 30 대의 무인기가 비행
// 비행은 콘 형식으로 고도 10 m 간격, 반지를 10 m 간격으로 시계 반대방향으로 회전 비행


void	CUAVUGVInterface::SimulationDronFlight(void)
{
	int	i,j;
	float	x,y,z, p , r , h;
	float	fDelRidus = 20.0f;
	float	fDelAlt = 20.0f;
	float	fLong, fLat;
	static float	fTurnAngle = 0.0f;
	double		utmPos[3];
	double		llhPos[3];

	fTurnAngle+=1.0f;
	if( fTurnAngle > 360.0f ) fTurnAngle -= 360.0f;


	for(i = 0;i < MAX_DRON;i++)
	{


		x= cos(fTurnAngle/(i+1)) *  (i+1)*fDelRidus;
		y= sin(fTurnAngle/(i+1)) *  (i+1)*fDelRidus;
		if( i == 5 ||  i ==  6|| i == 7 )
		{
			z =  0.0f;
		}
		else
		{
			z = i * fDelAlt;
		}

		utmPos[0] = x +  RWY_POSITION_X;
		utmPos[1] = y +  RWY_POSITION_Y;
		utm2llh( llhPos, utmPos[0], utmPos[1], 52, 'S');
		fLat = 	llhPos[0]*R2D;
		fLong = llhPos[1]*R2D;



		arrayUAVUGV[i].ucUavUgvID = i ; //  IGS Output : 0 ~  4  = UAV, 10 ~ 12 = UGV
								//  DLS Input  : 1 ~ 10  = UGV, 11 ~ 50 = UAV 
		arrayUAVUGV[i].ucEffective0_otUsed255 = 0;	// ?
		arrayUAVUGV[i].dSpeedMPS = 0.0f;					//	m/s

		arrayUAVUGV[i].dHeadingDeg = 0.0;				// degree
		arrayUAVUGV[i].dPitchDeg = 0.0;					// degree
		arrayUAVUGV[i].dRollDeg = 0.0;					// degree
		
		arrayUAVUGV[i].dLatitudeWGS84Deg = fLat;			// degree
		arrayUAVUGV[i].dLongitudeWGS84Deg = fLong;			// degree
		arrayUAVUGV[i].dAltitudeMeters = z;			// UGV의 경우  0.0 으로 처리함.
		
		arrayUAVUGV[i].dSteeringAngleDeg = 0.0;			// UGV 일 경우에만 유효함 
		for(j=0;j<8;j++)
		{
			arrayUAVUGV[i].Rotor[j].dDirection = 0.0;				// UAV 일때만 유효함 (최대 8 개의 로터)
			arrayUAVUGV[i].Rotor[j].dRPM = 0.0;				// UAV 일때만 유효함 (최대 8 개의 로터)
		}	
		//=== 19-0618 Update
		arrayUAVUGV[i].dTime_Measurement_sec = g_UAVTimer.GetElapseTime(); 	// range : 0 ~ 7200 sec

	
		if( m_nAllWIndChange == 1)
		{
			arrayUAVUGV[i].dWindSpeed_KPH = g_Interface.m_fAllWindSpeed; 			// range : 0 ~ 100 KPH
			arrayUAVUGV[i].dWindDirection_deg_0_360 = g_Interface.m_fAllWindDir;	// range : 0 ~ 360 deg
		}
		else
		{
			if( i == g_Interface.m_nDron_1 )
			{
				arrayUAVUGV[i].dWindSpeed_KPH = g_Interface.m_nWindSpeed_1; 			// range : 0 ~ 100 KPH
				arrayUAVUGV[i].dWindDirection_deg_0_360 = g_Interface.m_nWindDir_1;	// range : 0 ~ 360 deg


			}
			if(  i == g_Interface.m_nDron_2 )
			{
				arrayUAVUGV[i].dWindSpeed_KPH = g_Interface.m_nWindSpeed_2; 			// range : 0 ~ 100 KPH
				arrayUAVUGV[i].dWindDirection_deg_0_360 = g_Interface.m_nWindDir_2;	// range : 0 ~ 360 deg


			}
			if(  i == g_Interface.m_nDron_3)
			{
				arrayUAVUGV[i].dWindSpeed_KPH = g_Interface.m_nWindSpeed_3; 			// range : 0 ~ 100 KPH
				arrayUAVUGV[i].dWindDirection_deg_0_360 = g_Interface.m_nWindDir_3;	// range : 0 ~ 360 deg
			}

		}
		
		
		
		
		arrayUAVUGV[i].dAirTemp_deg = 0.0;				// range : -50 ~ 100 deg
		arrayUAVUGV[i].dAirPressure_mbar = 0.0;			// range : 900 ~ 1100 mbar


		if( m_nAllMissionDataChange == 1 || m_nAllWIndChange == 1)
		{
			arrayUAVUGV[i].dPayload_Data[0] = g_Interface.m_fAllMissionData;
		}
		else
		{
			if( i == g_Interface.m_nDron_1 )
			{
				for(j=0; j<5;j++)
				{
					arrayUAVUGV[i].dPayload_Data[j] = 0.0f ;			// range : 0 ~ 1000
				}

				// 첫번쨰만 값 대치
				arrayUAVUGV[i].dPayload_Data[0] = g_Interface.m_nMsnValue_1;
			
			}
			if(  i == g_Interface.m_nDron_2 )
			{
				for(j=0; j<5;j++)
				{
					arrayUAVUGV[i].dPayload_Data[j] = 0.0f ;			// range : 0 ~ 1000
				}

				// 첫번쨰만 값 대치
				arrayUAVUGV[i].dPayload_Data[0] = g_Interface.m_nMsnValue_2;
			}
			if(  i == g_Interface.m_nDron_3)
			{
				for(j=0; j<5;j++)
				{
					arrayUAVUGV[i].dPayload_Data[j] = 0.0f ;			// range : 0 ~ 1000
				}
				// 첫번쨰만 값 대치
				arrayUAVUGV[i].dPayload_Data[0] = g_Interface.m_nMsnValue_3;
			}
		}



	}
}

///////////////////////////////////////////////////////////
/// GBT 로 보내는 ADS_B 데이터 유효성 확인을 위함
int CUAVUGVInterface::RecvDataFromUAVUGV(BYTE * commMsg, int nSize, int nIndex)
{
	int	result;
	int	noByte;
	u_long	keybytes;
    int     sockSize;
	
	sockSize = sizeof(struct sockaddr_in);
	
	if((result = ioctlsocket(g_UDPCom.m_UDPSock_Server[nIndex].socket_id,
		FIONREAD,(u_long *) &keybytes)) == 0)
	{
		if(keybytes > 0)
		{
			//			AfxMessageBox("test");
			if ((noByte = recvfrom(g_UDPCom.m_UDPSock_Server[nIndex].socket_id,
				(char *)commMsg,nSize ,0,
				(struct sockaddr *) &g_UDPCom.m_UDPSock_Server[nIndex].sock_data,
				&sockSize)) > 0)
			{
				
				//	AfxMessageBox("test");
				g_nRecvByte = noByte+ nIndex*1000;

				return noByte;
			}
			else
			{
				return 1;
			}
		}
	}
	
	return 0;
}

void	CUAVUGVInterface::ReadConfigFile(char *sFileName)
{
	char			*startBuf;
	char			*endBuf;
	char			*tmpBuf;
	int				file_size;
	char			lineBuf[2048];
	char			copyLineBuf[2048];
	int				columnNumber=0;
	int				ii;
	CFileMan *m_File = new CFileMan;

	m_File->read_file(sFileName,&startBuf, &file_size);
	endBuf   = startBuf + file_size;
	tmpBuf =   startBuf;
	while(tmpBuf < endBuf)
	{	
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		columnNumber++;
	}
	tmpBuf =   startBuf;
	
	for ( ii = 0; ii < columnNumber -1; ii++)
	{
		tmpBuf += m_File->get_line(tmpBuf, lineBuf);
		char	*torken = NULL;
		strcpy(copyLineBuf, lineBuf);
		torken = (char *) strtok(copyLineBuf," ,;\t\n\r");
		if (torken[0] == '!')
		{
			continue;
		}
		else if (torken[0] == '#')
		{
			break;
		}
		else if (strcmp(torken,"OPERATION_MODE") == 0)
		{
			torken = (char *) strtok(NULL," ,;\t\n"); // 
			m_nOperationMode = atoi(torken);
		}
		else if (strcmp(torken,"IP_ADDR") == 0)
		{
			torken = (char *) strtok(NULL," ,;\t\n\r");
			strcpy(m_strIPAddress,torken);		
			torken = (char *) strtok(NULL," ,;\t\n\r");
			m_nPortNo = atoi(torken);
		}
		else if (strcmp(torken,"RUN_TIME") == 0)
		{
			torken = (char *) strtok(NULL,",;\t\n"); // 
			m_fTotalRunTime = atof(torken);
		}
		else if (strcmp(torken,"BACKGROUND_COLOR") == 0)
		{
			torken = (char *) strtok(NULL,",;\t\n"); // 
			m_nBackGroundColor = atof(torken);
		}

	}

}
