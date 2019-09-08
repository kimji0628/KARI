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
	double 			dTime_Measurement_sec ; 		// range : 0 ~ 7200 sec
	                                                                // 0 ���ϸ� �ӹ������� ����
	double			dWindSpeed_KPH ; 			// range : 0 ~ 100 KPH
	double			dWindDirection_deg_0_360 ;		// range : 0 ~ 360 deg
	double			dAirTemp_deg ;				// range : -50 ~ 100 deg
	double 			dAirPressure_mbar ;			// range : 900 ~ 1100 mbar
	double			dPayload_Data[5] ;			// range : 0 ~ 1000
	
}	sUDP_Data_2_IGS_Type ;

extern sUDP_Data_2_IGS_Type sUDP_Data_2_IGS ;

/*-----------------------------------------------------------------------------*/
/* Declare function prototype */
/*-----------------------------------------------------------------------------*/
void AssignNavData_2_IGS_UDP_Packet ( void ) ;
