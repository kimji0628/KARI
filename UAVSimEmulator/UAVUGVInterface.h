#pragma once

//////////////////////////////////////////////////
// UAV, UGV  �ӹ� ��� ������ ���� 
// 1) �ӹ���� ������
//   A. �����ð�: 0~7200��
//   B. ������ġ: ����, �浵, ��
//   C. �ٶ� ����
//     a. ǳ��: 0~100KPH
//     b. ǳ�� 0~360��
//   D. �ӹ���� ����ġ: 3��(���� 0~1000)
//
// 2) �ӹ���� ������ ����
//   A. ���� ������ ����: 
//     a. �ٶ�
//     b. �ӹ���� ����ġ 1~3��
//   B. ���� ���� ����
//     a. �ð�����
//     b. ������
//   C. ���� ����
//     a. �ٶ�: ������ ȭ��ǥ, ������ ǳ�� ����
//     b. �ӹ���� ����: ������ġ�� �������� �ɺ��� ǥ���ϰ�, 
//        ����ġ ���� ���� ���� ����. ����ġ�� ������ �����ϰ� �ɺ� ũ��� �ǽð� ��������
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
	double			dAltitudeMeters;			// UGV�� ���  0.0 ���� ó����.
	
	double			dSteeringAngleDeg;			// UGV �� ��쿡�� ��ȿ�� 
	sUavPropData		Rotor[8];				// UAV �϶��� ��ȿ�� (�ִ� 8 ���� ����)
	
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

// ���õǴ� Dron �� �Ѽ�
#define MAX_DRON	30
// UDP ������� �����ϴ� �������� �Ѽ�
// Dron ����(30) * 1 �� ( 60 ��) * 120 ��
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
	//      ���õ� ��ü ������ ǥ��
	int		m_nAllReange;
	//      ���� ���ŵǴ� ������ ǥ��
	int		m_nCurrentReceiveData;
	//      ������ ��ġ ǥ�� ����
	int		m_nDigitalValueData;
	//      ������� ǥ�� ����
	int		m_nFlightPathLine;
	//      ���� �����׸���
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
	// ������
	int		m_nBackGroundColor;

	//      �ǽð� ���� ������ ǥ�� �Ǵ� ����� ������ ǥ��
	//      �ǽð� 0, ��긮�� 1
	int		m_nInputDataType;
	//      �ٶ� ������ ��ü�� ����
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

	// �� ���� ���� ǥ��
	float	m_fMinX, m_fMaxX;
	float	m_fMinY, m_fMaxY;


	

	// ������ ����
	// ���� �������߿��� ���� �ֱ� �ð� ����
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

