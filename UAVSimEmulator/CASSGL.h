#pragma once
#include "easyopengl.h"

class CCASSGL : public CEasyOpenGL
{
public:
	CCASSGL(void);
	~CCASSGL(void);
public:
	int		nShowType; // 0 RS232 - 충돌회피 , 1 ADS_B 인터페이스
public:



	void	PrintCollisionAvoidanceResponceData(int x, int y, int nSend);
	void	PrintCollisionAvoidanceCommandData( int x, int y, int nSend);

	// Comport #1 => 
	void 	PrintCADP_8Data( int x, int y);
	void 	PrintCADP_12Data(int x, int y);
	void 	PrintCADP_23Data( int x, int y, int nSend);
	//    2019.04.19 일 추가
	void 	PrintCASOperationConfirm( int x, int y);



	// Comport #2 => 
	void 	PrintHearbeatData(int x, int y) ;
	void	PrintADS_B_TrafficData( int x, int y, int nReadWrite);

	// Comport #3 => 
	void	PrintVisualData( int x, int y, int nSend);


	// Comport #4 => 
	void 	PrintCADRData( int x, int y, int nSend);

	// Comport #5 => 
	void	PrintGPS_INSData(int x, int y, int nSend);
	void	PrintGPS_INS_BufferData(int x, int y , int nSend);


	void 	PrintGPS_INS_219Data(int x, int y, int nSend);


	void ShowRS232Message();

////////////////////////////////////////////////////////////////////////
	// ADS_B  => 
	void 	PrintADS_B_RecvData(int x, int y);
	void 	PrintADS_B_RecvBufferData(int x, int y);
	void	ShowADS_B_RecvMsg();

////////////////////////////////////////////////////////////////////////
	void	PrintCat21_FSPEC(int x, int y);
	void	PrintCat21_SendData(int x, int y);
	void	PrintCat21_SendBufferData (int x, int y);
	void	ShowCat21SendMessage();

	void	PrintScenarioData(int x, int y);

	void	PrintUAT_ADS_BSendData(int x, int y);
	void	PrintCat247SendData(int x, int y);
/////////////////////////////////////////////////////////
	void	PrintCat33SendData(int x, int y);



};
