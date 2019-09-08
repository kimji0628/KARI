#pragma once

//////////////////////////////////////////////////
// UAV, UGV  임무 장비 데이터 도시 
// 1) 임무장비 데이터
//   A. 측정시간: 0~7200초
//   B. 측정위치: 위도, 경도, 고도
//   C. 바람 정보
//     a. 풍속: 0~100KPH
//     b. 풍향 0~360도
//   D. 임무장비 측정치: 3개(범위 0~1000)
//
// 2) 임무장비 데이터 도시
//   A. 도시 데이터 선택: 
//     a. 바람
//     b. 임무장비 측정치 1~3번
//   B. 도시 범위 선택
//     a. 시간범위
//     b. 고도범위
//   C. 도시 형태
//     a. 바람: 방향은 화살표, 색으로 풍속 지정
//     b. 임무장비 정보: 측정위치에 구형태의 심볼로 표시하고, 
//        측정치 값에 따라 색을 변경. 측정치를 선으로 연결하고 심볼 크기는 실시간 조정가능
///////////////////////////////////////////////////////

/** 
	@file 
		Udp2IGS.h
	@brief
		Data type to send UGV/UAV state data for 3D Image Generation Program  
	@author 
		Jooil Kim
	@date 
		2017. 10. 17 16:30
	@comments

*/

/*-----------------------------------------------------------------------------*/
/* Define global variables */
/*-----------------------------------------------------------------------------*/
typedef struct 
{
	double	dRPM;
	double  dDirection;
}	sUavPropData;

typedef struct 
{
	unsigned char	ucUavUgvID ;
	   				//  IGS Output : 0 ~  4  = UAV, 10 ~ 12 = UGV
					//  DLS Input  : 1 ~ 10  = UGV, 11 ~ 50 = UAV 
	unsigned char	ucEffective0_otUsed255 ;	// ?
	double			dSpeedMPS;					//	m/s

	double			dHeadingDeg;				// degree
	double			dPitchDeg;					// degree
	double			dRollDeg;					// degree
	
	double			dLatitudeWGS84Deg;			// degree
	double			dLongitudeWGS84Deg;			// degree
	double			dAltitudeMeters;			// UGV의 경우  0.0 으로 처리함.
	
	double			dSteeringAngleDeg;			// UGV 일 경우에만 유효함 
	sUavPropData		Rotor[8];				// UAV 일때만 유효함 (최대 8 개의 로터)
	
	//=== 19-0618 Update
	double 			dTime_Measurement_sec ; 	// range : 0 ~ 7200 sec
	double			dWindSpeed_KPH ; 			// range : 0 ~ 100 KPH
	double			dWindDirection_deg_0_360 ;	// range : 0 ~ 360 deg
	double			dAirTemp_deg ;				// range : -50 ~ 100 deg
	double 			dAirPressure_mbar ;			// range : 900 ~ 1100 mbar
	double			dPayload_Data[5] ;			// range : 0 ~ 1000
	
}	sUDP_Data_2_IGS_Type ;

extern sUDP_Data_2_IGS_Type sUDP_Data_2_IGS ;

/*-----------------------------------------------------------------------------*/
/* Declare function prototype */
/*-----------------------------------------------------------------------------*/
void AssignNavData_2_IGS_UDP_Packet ( void ) ;

// 도시되는 Dron 의 총수
#define MAX_DRON	30
// UDP 통신으로 수신하는 데이터의 총수
// Dron 갯수(30) * 1 분 ( 60 초) * 120 분
#define MAX_BUFFER  (30 * 60 * 20)





typedef struct
{
	int		nFront;
	int		nRear;
	int		nFirstRound;
	sUDP_Data_2_IGS_Type	BufUAVUGV[MAX_BUFFER];
	float	fRecvTime[MAX_BUFFER];
}	RING_BUF_UDP_IGS_DATA;



class CUAVUGVInterface
{
	void	Gp2Utm(const double lon_rad, const double lat_rad, 
						 double *gridzone, double *east_mtr, double *north_mtr);

	void	utm2llh( double *llh, double x, double y, int zone, char zone_char);

public:

	int		m_nOperationMode;
	int		m_nStatus;
	int		m_nSymbolType;
	int		m_nOnArrowSymbol;
	int		m_nOnSphereSymbol;
	int		m_nArrowSymbolSize;
	int		m_nSphereSymbolSize;
	

	/////////////////////////////
	//      선택된 전체 구간에 표시
	int		m_nAllReange;
	//      현재 수신되는 데이터 표시
	int		m_nCurrentReceiveData;
	//      디지털 수치 표시 여부
	int		m_nDigitalValueData;
	//      비행궤적 표시 여부
	int		m_nFlightPathLine;
	//      고흥 지형그리기
	int		m_nMapDisplay;
	int		m_nDisplayAltRange;

	float	m_fTimeSpan;
	float	m_fOffsetTime;
	float	m_fOffset100Digit;  // 0 ~ 72
	float	m_fOffsetDigit;     // 0 ~ 99	
	float	m_fTotalRunTime;
	int		m_nPortNo;
	char	m_strIPAddress[64];


	float	m_fSymbolSize;
	// 바탕색
	int		m_nBackGroundColor;

	//      실시간 수신 데이터 표시 또는 저장된 데이터 표시
	//      실시간 0, 디브리핑 1
	int		m_nInputDataType;
	//      바람 정보를 전체에 적용
	int		m_nAllWIndChange;
	int		m_nAllMissionDataChange;

	int		m_nDron_1;
	int		m_nDron_2;
	int		m_nDron_3;
	int		m_nMsnValue_1;
	int		m_nMsnValue_2;
	int		m_nMsnValue_3;
	int		m_nWindDir_1;
	int		m_nWindDir_2;
	int		m_nWindDir_3;
	int		m_nWindSpeed_1;
	int		m_nWindSpeed_2;
	int		m_nWindSpeed_3;
	int		m_nAltUp;
	int		m_nAltDown;
	float	m_fStartTime;
	float	m_fEndTime;

	float	m_fAllWindDir;
	float	m_fAllWindSpeed;
	float	m_fAllMissionData;

	// 고도 제한 공역 표시
	float	m_fMinX, m_fMaxX;
	float	m_fMinY, m_fMaxY;


	

	// 서버용 변수
	// 수신 데이터중에서 가장 최근 시간 저장
	float	m_fFinalRecvTime;
	unsigned long  m_nNoRecvCount;



	sUDP_Data_2_IGS_Type	arrayUAVUGV[MAX_DRON];
	RING_BUF_UDP_IGS_DATA	RingBufUDP_IGS[MAX_DRON];

public:
	CUAVUGVInterface(void);
	~CUAVUGVInterface(void);
	void	SimulationDronFlight(void);
	void	ReadConfigFile(char *sFileName);
	int		RecvDataFromUAVUGV(BYTE * commMsVg, int nSize, int nIndex);
};

