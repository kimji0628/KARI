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
	double 			dTime_Measurement_sec ; 		// range : 0 ~ 7200 sec
	                                                                // 0 이하면 임무데이터 무시
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
