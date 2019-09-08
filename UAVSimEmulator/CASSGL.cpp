#include "StdAfx.h"
#include "CASSGL.h"



extern	unsigned char ucCAS_Traffic[45];
extern	unsigned char ucADS_BSetUp[21];
extern	unsigned char ucCollisionAvoid[15];
extern	unsigned char ucOperationConfirm[10];
extern	unsigned char ucGPS_INS[49];

extern	int		gLoopCount;
extern	float	gfThreadTime;

//unsigned char ucLong[4]= {0x00, 0xB6, 0x0A, 0x98};
//unsigned char ucLat[4]  = {0x01, 0x6C, 0x15, 0x31};


unsigned char ucLong[14]= {0x5A, 0x75, 0x7C, 0x53, 0x18, 0x9C, 0x73,  0xDF, };
unsigned char ucLat[4]  = {0x18, 0x9C, 0x73,  0xDF};





//  0  1 2  3  4  5   6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 49
// 55 55 4E 31 2A 00 B6 01 6C 02 22 00 34 00 68 00 9C 0C CC 0C CC 0C CC 00 80 01 00 01 80 5A 75 7C 53 18 9C 73 DF 01 90 01 47 00 00 00 00 00 00 3F 51 

//                                                                                          LAT         LONG
// 55 55 4E 31 2A 00 B6 01 6C 02 22 00 34 00 68 00 9C 0C CC 0C CC 0C CC 00 80 01 00 01 80 5A 75 7C 53 18 9C 73 DF 01 90 01 47 00 00 00 00 00 00 3F 51

CCASSGL::CCASSGL(void)
{
	memcpy(EnDeCoder.m_CCADP_23.Recv.Value.uc, ucCAS_Traffic,45);
	memcpy(EnDeCoder.m_CCADP_12.Recv.Value.uc, ucADS_BSetUp,21);
	memcpy(EnDeCoder.m_CCADP_8.Recv.Value.uc, ucCollisionAvoid,15);
	memcpy(EnDeCoder.m_COperConfirm.Recv.Value.uc, ucOperationConfirm,10);
	memcpy(EnDeCoder.m_CGPS_INS_219.Recv.Value.uc, ucGPS_INS, 49);
	
//	int u32;
	UINT32 u32;
	float	f32;

	f32 = EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), &ucLong[0], 0)* R2D;

	f32 = EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0], 29 ) * R2D;


	f32 = EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), &ucLong[0])* R2D;


	f32 = EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), &ucLong[4])* R2D;


	memcpy(&u32,ucLong, 4);

	f32 = u32 / 2.0*PHI/pow(2.0,32.0);

	u32 = EnDeCoder.SwapUINT32(u32);

	f32 = u32 * ( 2.0*PHI/pow(2.0,32.0)) * R2D;




	double dV;
	dV = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 0,	2.0*PHI/pow(2.0,32.0), &ucLong[0] );
	dV = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 0,	2.0*PHI/pow(2.0,32.0), &ucLat[0] );






}

CCASSGL::~CCASSGL(void)
{
}



void 	CCASSGL::PrintHearbeatData(int x, int y) 
{
	int i;
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = 20;

    // 
	// CADAM -> KUCAS
	

	if(EnDeCoder.m_CHearBeat.nSendReceive == 0)
	{
		sprintf(strTmp,"Hearbeat Recv Cnt : %d ",EnDeCoder.m_CHearBeat.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;
		
		for(i=0;i<7;i++)
		{
			sprintf(strTmp,":%x",EnDeCoder.m_CHearBeat.Recv.Value.uc[i] & 0xff);
			Printf( (int) nX+i*20, (int) nY ,strTmp, MIDDLE_FONT); 
		}
		nY+=nGap;
		

		sprintf(strTmp,"MessageID");								// 1
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   0X%x",	EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.MessageID & 0xff);								// 1
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;

		sprintf(strTmp,"GPSPosValid");			// 2
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);

		sprintf(strTmp,":   %x",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.GPSPosValid	& 0xff);			// 2
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"MaintReqd");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.MaintReqd);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"IDENT");							// 3 - 5
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",			EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.IDENT);							// 3 - 5
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AddrType");						// 6 - 8
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.AddrType);						// 6 - 8
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"GPSBattLow");						// 9 - 11
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.GPSBattLow);						// 9 - 11
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;




		sprintf(strTmp,"ATCServices");							// 12
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.ATCServices	);							// 12
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Reserved1");		    
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.Reserved1);		    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UATInitialized");	       
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.UATInitialized);	       
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;				
		sprintf(strTmp,"TimeStampMSB");			// 3
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.TimeStampMSB);			// 3
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CSARequested");		// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.CSARequested);		// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CSANotAvailable");			// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.CSANotAvailable);			// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved2");		// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.Reserved2);		// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UTC_OK");			// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",			EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.UTC_OK);			// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;				
		sprintf(strTmp,"TimeStampLSB");// 4
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   0X%x%x",	EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.TimeStampLSB[0]& 0xff, EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.TimeStampLSB[1]& 0xff);// 4
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;
		sprintf(strTmp,"MessageCounts");				// 6
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  0X%x%x",EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.MessageCounts[0]& 0xff,EnDeCoder.m_CHearBeat.Recv.Value.hearbeat.MessageCounts[1]& 0xff);				// 6
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Hearbeat Send Cnt : %d ",EnDeCoder.m_CHearBeat.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;
		
		for(i=0;i<7;i++)
		{
			sprintf(strTmp,":%x",EnDeCoder.m_CHearBeat.Send.Value.uc[i] & 0xff);
			Printf( (int) nX+i*20, (int) nY ,strTmp, MIDDLE_FONT); 
		}
		nY+=nGap;
		

		sprintf(strTmp,"MessageID");								// 1
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   0X%x",	EnDeCoder.m_CHearBeat.Send.Value.hearbeat.MessageID & 0xff);								// 1
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;

		sprintf(strTmp,"GPSPosValid");			// 2
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);

		sprintf(strTmp,":   %x",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.GPSPosValid	& 0xff);			// 2
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"MaintReqd");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.MaintReqd);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"IDENT");							// 3 - 5
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",			EnDeCoder.m_CHearBeat.Send.Value.hearbeat.IDENT);							// 3 - 5
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AddrType");						// 6 - 8
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.AddrType);						// 6 - 8
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"GPSBattLow");						// 9 - 11
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.GPSBattLow);						// 9 - 11
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;




		sprintf(strTmp,"ATCServices");							// 12
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.ATCServices	);							// 12
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Reserved1");		    
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.Reserved1);		    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UATInitialized");	       
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Send.Value.hearbeat.UATInitialized);	       
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;				
		sprintf(strTmp,"TimeStampMSB");			// 3
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.TimeStampMSB);			// 3
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CSARequested");		// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Send.Value.hearbeat.CSARequested);		// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CSANotAvailable");			// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",	EnDeCoder.m_CHearBeat.Send.Value.hearbeat.CSANotAvailable);			// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved2");		// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",		EnDeCoder.m_CHearBeat.Send.Value.hearbeat.Reserved2);		// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UTC_OK");			// 
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",			EnDeCoder.m_CHearBeat.Send.Value.hearbeat.UTC_OK);			// 
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;				
		sprintf(strTmp,"TimeStampLSB");// 4
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   0X%x%x",	EnDeCoder.m_CHearBeat.Send.Value.hearbeat.TimeStampLSB[0]& 0xff, EnDeCoder.m_CHearBeat.Send.Value.hearbeat.TimeStampLSB[1]& 0xff);// 4
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		nY+=nGap;
		sprintf(strTmp,"MessageCounts");				// 6
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  0X%x%x",EnDeCoder.m_CHearBeat.Send.Value.hearbeat.MessageCounts[0]& 0xff,EnDeCoder.m_CHearBeat.Send.Value.hearbeat.MessageCounts[1]& 0xff);				// 6
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
}






void CCASSGL::PrintADS_B_TrafficData( int x, int y, int nReadWrite)
{
	char			strTmp[256];
	unsigned char ch[2];
	int			nX, nY,nXV, nGap;
	int			i,j,k;
	float		fDeg;
	float		fValue;
	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if( nReadWrite == 0 )
	{
	  
		sprintf(strTmp,"Recv Traffic Data ( Cnt %d )", EnDeCoder.m_CTraffic.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		nY+=nGap;


		for(i=0;i<4;i++)
		{
			sprintf(strTmp,"%d ~ %d : ",i*7,(i*7)+7);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			for(j=0;j< 7;j++)
			{
				sprintf(strTmp,":%x",EnDeCoder.m_CTraffic.Recv.Value.uc[i*7+j] & 0xff);
				Printf( (int) nX+80 +j*20, (int) nY ,strTmp, MIDDLE_FONT); 
			}
			nY+=nGap;
		}
/*
		sprintf(strTmp,"Que Header %d Taile %d  No %d ", g_ComuPort[1].m_QueueRead.m_iHead, g_ComuPort[1].m_QueueRead.m_iTail, g_ComuPort[1].m_QueueRead.m_iHead - g_ComuPort[1].m_QueueRead.m_iTail);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		nY+=nGap;
	
		for(i=0; i< 28;i++)
		{
			sprintf(strTmp,":%x",m_CTraffic.bufReceive[i] & 0xff);
			Printf( (int) nX+80 +i*20, (int) nY ,strTmp, MIDDLE_FONT); 
		}
		nY+=nGap;
*/		
	
		//nY+=nGap;
		//for(i = g_ComuPort[1].m_QueueRead.m_iHead, k=0 ; i > g_ComuPort[1].m_QueueRead.m_iHead - 7, i > 0;i--, k++)
		//{
		//		BYTE buf;
		//		g_ComuPort[1].m_QueueRead.GetByte(&buf);
		//		sprintf(strTmp,":%x",buf & 0xff);
		//		Printf( (int) nX+80 +k*20, (int) nY ,strTmp, MIDDLE_FONT); 
		//	
		//}
		nY+=nGap;



		sprintf(strTmp,"AddressType"); 			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",EnDeCoder.m_CTraffic.Recv.Value.traffic.AddressType); 			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		//
		sprintf(strTmp,"ParticipantAddress");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d - %x%x",EnDeCoder.m_CTraffic.Recv.Value.traffic.ParticipantAddress[0],EnDeCoder.m_CTraffic.Recv.Value.traffic.ParticipantAddress[1],EnDeCoder.m_CTraffic.Recv.Value.traffic.ParticipantAddress[2]);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		//
		sprintf(strTmp,"Latitude");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x%x",EnDeCoder.m_CTraffic.Recv.Value.traffic.Latitude[0], EnDeCoder.m_CTraffic.Recv.Value.traffic.Latitude[1],EnDeCoder.m_CTraffic.Recv.Value.traffic.Latitude[2]);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,":   %.8",HILS_AC.m_fLatitude);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		//
		sprintf(strTmp,"Longitude");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x%x",EnDeCoder.m_CTraffic.Recv.Value.traffic.Longitude[0],EnDeCoder.m_CTraffic.Recv.Value.traffic.Longitude[1],EnDeCoder.m_CTraffic.Recv.Value.traffic.Longitude[2]);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,":   %.8",HILS_AC.m_fLongitude);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Altitude_MSB");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.Altitude_MSB);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Altitude_LSB");				    
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.Altitude_LSB & 0xff);				    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;





		sprintf(strTmp,"Miscell  Indicators");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.MiscellaneousIndicators & 0xff);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"NIC");						
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.NIC & 0xff);						
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"NACp");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Recv.Value.traffic.NACp & 0xff);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HorizVelocityMSB");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Recv.Value.traffic.HorizontalVelocityMSB & 0xff);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HorizVelocityLSB");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.HorizontalVelocityLSB & 0xff);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"VertVelocityMSB");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.VerticalVelocityMSB & 0xff);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"VertVelocityLSB");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Recv.Value.traffic.VerticalVelocityLSB & 0xff);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TrackHeading");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",		EnDeCoder.m_CTraffic.Recv.Value.traffic.TrackHeading);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"EmitterCategory");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Recv.Value.traffic.EmitterCategory);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		/////////////////////////////////////////////
		sprintf(strTmp,"CallSign");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %c%c%c%c%c%c%c%c",	EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[0],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[1],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[2],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[3],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[4],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[5],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[6],
			EnDeCoder.m_CTraffic.Recv.Value.traffic.CallSign[7]);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"EmergPriorityCode");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Recv.Value.traffic.EmergencyPriorityCode);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Reserved");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Recv.Value.traffic.Reserved);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
	  
		sprintf(strTmp,"Send  Traffic Data (Cnt %d)", EnDeCoder.m_CTraffic.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		nY+=nGap;

		for(i=0;i<4;i++)
		{
			sprintf(strTmp,"%d ~ %d : ",i*7,(i*7)+7);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			for(j=0;j< 7;j++)
			{
				sprintf(strTmp,":%x",EnDeCoder.m_CTraffic.Send.Value.uc[i*7+j] & 0xff);
				Printf( (int) nX+80 +j*20, (int) nY ,strTmp, MIDDLE_FONT); 
			}
			nY+=nGap;
		}

		sprintf(strTmp,"AddressType"); 			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",EnDeCoder.m_CTraffic.Send.Value.traffic.AddressType); 			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		//
		sprintf(strTmp,"ParticipantAddress");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d - %x%x",EnDeCoder.m_CTraffic.Send.Value.traffic.ParticipantAddress[0],
			EnDeCoder.m_CTraffic.Send.Value.traffic.ParticipantAddress[1],
			EnDeCoder.m_CTraffic.Send.Value.traffic.ParticipantAddress[2]);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		//
		sprintf(strTmp,"Latitude");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x%x",EnDeCoder.m_CTraffic.Send.Value.traffic.Latitude[0], 
			EnDeCoder.m_CTraffic.Send.Value.traffic.Latitude[1],
			EnDeCoder.m_CTraffic.Send.Value.traffic.Latitude[2]);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		fDeg = EnDeCoder.GetByteToFloatForWGS84(&EnDeCoder.m_CTraffic.Send.Value.traffic.Latitude[0], 3);

		sprintf(strTmp,":   %.8f",fDeg);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		//
		sprintf(strTmp,"Longitude");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x%x",EnDeCoder.m_CTraffic.Send.Value.traffic.Longitude[0],
			EnDeCoder.m_CTraffic.Send.Value.traffic.Longitude[1],
			EnDeCoder.m_CTraffic.Send.Value.traffic.Longitude[2]);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		fDeg = EnDeCoder.GetByteToFloatForWGS84(&EnDeCoder.m_CTraffic.Send.Value.traffic.Longitude[0], 3);

		sprintf(strTmp,":   %.8f",fDeg);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Altitude MSB : LSB");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x : %x",EnDeCoder.m_CTraffic.Send.Value.traffic.Altitude_MSB & 0xff, 
			EnDeCoder.m_CTraffic.Send.Value.traffic.Altitude_LSB & 0xff);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		ch[0] = EnDeCoder.m_CTraffic.Send.Value.traffic.Altitude_MSB;
		ch[1] = EnDeCoder.m_CTraffic.Send.Value.traffic.Altitude_LSB << 4;
		fValue =  EnDeCoder.GetByteToFloatForAltitude((char *) &ch[0]);

		sprintf(strTmp,":   %.2f",fValue);				    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;





		sprintf(strTmp,"Miscell  Indicators");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Send.Value.traffic.MiscellaneousIndicators & 0xff);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"NIC");						
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Send.Value.traffic.NIC & 0xff );						
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"NACp");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Send.Value.traffic.NACp & 0xff);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
/////// 
		sprintf(strTmp,"HorizVel MSB : LSB");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x : %x",	EnDeCoder.m_CTraffic.Send.Value.traffic.HorizontalVelocityMSB & 0xff, 
			EnDeCoder.m_CTraffic.Send.Value.traffic.HorizontalVelocityLSB & 0xff);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		ch[0] = EnDeCoder.m_CTraffic.Send.Value.traffic.HorizontalVelocityMSB;
		ch[1] = EnDeCoder.m_CTraffic.Send.Value.traffic.HorizontalVelocityLSB << 4;
		fValue =  EnDeCoder.GetByteToFloatForHorizontalVelocity((char *) &ch[0]);
		sprintf(strTmp,":   %.2f(KONTS)",fValue);				    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;
		sprintf(strTmp,":   %.2f(MPS)",fValue/MPS_TO_KNOTS);				    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;
		sprintf(strTmp,":   %.2f(KPH)",fValue*3.6/MPS_TO_KNOTS);				    
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;


///////	

		sprintf(strTmp,"VertVel MSB : LSB");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x : %x ",EnDeCoder.m_CTraffic.Send.Value.traffic.VerticalVelocityMSB, EnDeCoder.m_CTraffic.Send.Value.traffic.VerticalVelocityLSB & 0xff);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		ch[0] = EnDeCoder.m_CTraffic.Send.Value.traffic.VerticalVelocityMSB;
		ch[1] = EnDeCoder.m_CTraffic.Send.Value.traffic.VerticalVelocityLSB;
		fValue =  EnDeCoder.GetByteToFloatForVerticalVelocity((char *) &ch[0]);
		sprintf(strTmp,":   %.2f",	fValue);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
///////////////////////////////////////////////////
		sprintf(strTmp,"TrackHeading");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",		EnDeCoder.m_CTraffic.Send.Value.traffic.TrackHeading & 0xff );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,":   %.1f",		EnDeCoder.m_CTraffic.Send.Value.traffic.TrackHeading * 1.4 );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



////////////////////////////////////
		sprintf(strTmp,"EmitterCategory");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Send.Value.traffic.EmitterCategory);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;




		/////////////////////////////////////////////
		sprintf(strTmp,"CallSign");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %c%c%c%c%c%c%c%c",	EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[0],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[1],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[2],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[3],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[4],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[5],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[6],
			EnDeCoder.m_CTraffic.Send.Value.traffic.CallSign[7]);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"EmergPriorityCode");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",EnDeCoder.m_CTraffic.Send.Value.traffic.EmergencyPriorityCode);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Reserved");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Send.Value.traffic.Reserved);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CRC16 ");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",	EnDeCoder.m_CTraffic.Send.Value.traffic.CRC16);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


	}
}


void CCASSGL::PrintVisualData( int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

// m_CIntruderVisualData.Recv.Value
	if( nSend == 0)
	{
		sprintf(strTmp,"Recv Visual Data (Cnt %d)", EnDeCoder.m_CIntruderVisualData.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		nY+=nGap;

		sprintf(strTmp,"Header");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.Header[0],
			EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.Header[1]);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"No Of Intru AC");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.NoOfIntruAC);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		for(int i=0; i< EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.NoOfIntruAC;i++)
		{
			sprintf(strTmp,"ID");
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %d",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].ID);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosX",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosX);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosX);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosY", 	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosY); 
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f", 	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosY); 
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosZ",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosZ);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",	EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fPosZ);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityX",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityX);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityX);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityY",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityY);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityY);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityZ",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityZ);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Recv.Value.visual.ac[i].fVelocityZ);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		}
	}
	else
	{
		sprintf(strTmp,"Vis Data (Cnt %d,Send %d, %d Hz) ",EnDeCoder.m_CIntruderVisualData.nSendCnt, EnDeCoder.m_nVisualSendCnt, (int) (1.0/EnDeCoder.m_fSendPeriodTime) );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		nY+=nGap;

		sprintf(strTmp,"Header");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.Header[0],EnDeCoder.m_CIntruderVisualData.Send.Value.visual.Header[1]);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"No Of Intru AC");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %d",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.NoOfIntruAC);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		for(int i=0; i< EnDeCoder.m_CIntruderVisualData.Send.Value.visual.NoOfIntruAC;i++)
		{
			sprintf(strTmp,"ID");
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %d",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].ID);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosX",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosX);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosX);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosY", 	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosY); 
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f", 	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosY); 
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fPosZ",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosZ);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",	EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fPosZ);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityX",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityX);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityX);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityY",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityY);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityY);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"fVelocityZ",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityZ);
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,":   %.2f",EnDeCoder.m_CIntruderVisualData.Send.Value.visual.ac[i].fVelocityZ);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		}




		sprintf(strTmp,"CRC Check");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 

		int nCrcCheckNo;
		nCrcCheckNo = 3+ 25*EnDeCoder.m_CIntruderVisualData.Send.Value.visual.NoOfIntruAC;
		sprintf(strTmp,":   %x",EnDeCoder.m_CIntruderVisualData.Send.Value.uc[nCrcCheckNo]);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
}



void CCASSGL::PrintCollisionAvoidanceCommandData( int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if( nSend == 0) // Recv
	{

		sprintf(strTmp,"Recv Coll Avoid Cmd (Cnt %d)", EnDeCoder.m_CCAC.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		 nY+=nGap;

		sprintf(strTmp,"Header");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x",  EnDeCoder.m_CCAC.Recv.Value.cac.Header[0], EnDeCoder.m_CCAC.Recv.Value.cac.Header[1]);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"State");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %d",				EnDeCoder.m_CCAC.Recv.Value.cac.State);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandLevel");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp ,":   %d",			EnDeCoder.m_CCAC.Recv.Value.cac.CommandLevel);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AltitudeChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %.2f",	EnDeCoder.m_CCAC.Recv.Value.cac.AltitudeChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"BankChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAC.Recv.Value.cac.BankChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HeadingChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",	EnDeCoder.m_CCAC.Recv.Value.cac.HeadingChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CheckSum");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":   %x",			EnDeCoder.m_CCAC.Recv.Value.cac.CheckSum);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send Coll Avoid Cmd (Cnt %d)", EnDeCoder.m_CCAC.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		 nY+=nGap;

		sprintf(strTmp,"Header");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x%x", EnDeCoder.m_CCAC.Send.Value.cac.Header[0], EnDeCoder.m_CCAC.Send.Value.cac.Header[1]);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"State");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",				 EnDeCoder.m_CCAC.Send.Value.cac.State);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandLevel");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp ,":  %d",			 EnDeCoder.m_CCAC.Send.Value.cac.CommandLevel);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AltitudeChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %.2f",	 EnDeCoder.m_CCAC.Send.Value.cac.AltitudeChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"BankChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %.2f",		 EnDeCoder.m_CCAC.Send.Value.cac.BankChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HeadingChangeCmd");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %.2f",	 EnDeCoder.m_CCAC.Send.Value.cac.HeadingChangeCmd);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CheckSum");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",			 EnDeCoder.m_CCAC.Send.Value.cac.CheckSum);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	}
}



void CCASSGL::PrintCollisionAvoidanceResponceData(int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if( nSend == 0) // Recv
	{

		sprintf(strTmp,"Recv Colli Avoid. Resp.(Cnd %d)", EnDeCoder.m_CCAR.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;
		nY+=nGap;

		sprintf(strTmp,"Header");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x",EnDeCoder.m_CCAR.Recv.Value.car.Header[0], EnDeCoder.m_CCAR.Recv.Value.car.Header[1]				);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"State");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",				EnDeCoder.m_CCAR.Recv.Value.car.State);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandLevel");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",			EnDeCoder.m_CCAR.Recv.Value.car.CommandLevel);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AltitudeChangeCmd");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Recv.Value.car.AltitudeChangeCmd);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"BankChangeCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Recv.Value.car.BankChangeCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HeadingChangeCmd");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Recv.Value.car.HeadingChangeCmd);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandAccep");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",		EnDeCoder.m_CCAR.Recv.Value.car.CommandAccept);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVAltitudeCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Recv.Value.car.UAVAltitudeCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVBankCmd");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Recv.Value.car.UAVBankCmd);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVHeadingCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Recv.Value.car.UAVHeadingCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CheckSum");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",				EnDeCoder.m_CCAR.Recv.Value.car.CheckSum);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send Colli Avoid. Resp.(Cnd %d)", EnDeCoder.m_CCAR.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;
		nY+=nGap;

		sprintf(strTmp,"Header");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x%x",EnDeCoder.m_CCAR.Send.Value.car.Header[0], EnDeCoder.m_CCAR.Send.Value.car.Header[1]				);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"State");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",				EnDeCoder.m_CCAR.Send.Value.car.State);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandLevel");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",			EnDeCoder.m_CCAR.Send.Value.car.CommandLevel);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AltitudeChangeCmd");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Send.Value.car.AltitudeChangeCmd);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"BankChangeCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Send.Value.car.BankChangeCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"HeadingChangeCmd");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",		EnDeCoder.m_CCAR.Send.Value.car.HeadingChangeCmd);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CommandAccep");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %x",		EnDeCoder.m_CCAR.Send.Value.car.CommandAccept);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVAltitudeCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Send.Value.car.UAVAltitudeCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVBankCmd");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Send.Value.car.UAVBankCmd);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"UAVHeadingCmd");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   %.2f",			EnDeCoder.m_CCAR.Send.Value.car.UAVHeadingCmd);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CheckSum");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":   0X%x",				EnDeCoder.m_CCAR.Send.Value.car.CheckSum);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



	}


}


void 	CCASSGL::PrintCADP_23Data( int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	float		fV;
	UINT16		u16;

	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;


	

	if( nSend == 0 )
	{
		sprintf(strTmp,"CAS Traffic (Cnt %d)", EnDeCoder.m_CCADP_23.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x%x",EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.Header[0],EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.Header[1] );				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PayloadLength");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,": %x",EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.PaloadLength);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketSequence");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.PacketSequence );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.SendingSystemID);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.TargetSystemID);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.MessageID);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TrafficID");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.TrafficID);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		float fDeg;
		UINT32 u32;

		sprintf(strTmp,"Latitude" );		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 

		u32 = EnDeCoder.SwapUINT32(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.PositionLatitude);
		fDeg = (u32 *0.0000001) -180.0f;

		sprintf(strTmp," :  %.6f",	fDeg );		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Longitude");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
	
		u32 = EnDeCoder.SwapUINT32(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.PositionLongitude);
		fDeg = (u32 *0.0000001) -180.0f;
		sprintf(strTmp,":   %.6f",	fDeg);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PositionAltitude");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 

		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.PositionAltitude);
		fV =  u16*0.1-500.0f;
		sprintf(strTmp,":  %.2f", fV);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SpeedNorth");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.SpeedNorth);		
		fV =  u16*0.1-250.0f;
		sprintf(strTmp,":  %.2f", fV);			

		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"SpeedEas");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.SpeedEast);	
		fV =  u16*0.1-250.0f;
		sprintf(strTmp,":  %.2f", fV);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SpeedDown");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.SpeedDown);
		fV =  u16*0.1-250.0f;
		sprintf(strTmp,":  %.2f", fV);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"GroundSpeed");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.GroundSpd);		
		fV =  u16*0.1;
		sprintf(strTmp,":  %.2f", fV);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"AttitudeHeadingAngle");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.AttitudeHeadingAngle);	

		fV =  u16*0.1;
		sprintf(strTmp,":  %.2f", fV);			

		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"DataFusion");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.DataFusion);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CollisionRisk");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.CollisionRisk);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CollisionEstimatedTime");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 


		u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.CollisionEstimatedTime);	
		fV =  u16*0.1 - 1800.0;
		sprintf(strTmp,":  %.2f", fV);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;




//	UINT8			ID_Heading;								// 32
//	UINT8			CollisionStatus;							// 33
//	UINT8			CAM_CBIT;								// 34
//	UINT8			CallSign[8];

		sprintf(strTmp,"CallSign");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %s",						EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.CallSign);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CRC16");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",						EnDeCoder.m_CCADP_23.Recv.Value.cadp_23.CRC16);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send CADP_23 (Cnt %d)", EnDeCoder.m_CCADP_23.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x%x",EnDeCoder.m_CCADP_23.Send.Value.cadp_23.Header[0],EnDeCoder.m_CCADP_23.Send.Value.cadp_23.Header[1] );				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PaloadLength");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",EnDeCoder.m_CCADP_23.Send.Value.cadp_23.PaloadLength);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketSequence");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_23.Send.Value.cadp_23.PacketSequence );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",EnDeCoder.m_CCADP_23.Send.Value.cadp_23.SendingSystemID);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_23.Send.Value.cadp_23.TargetSystemID);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,": %d",				EnDeCoder.m_CCADP_23.Send.Value.cadp_23.MessageID);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TrafficID");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Send.Value.cadp_23.TrafficID);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
// 위도 
		sprintf(strTmp,"PositionLatitude" );		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		UINT32 u32;
		u32 =  EnDeCoder.SwapUINT32(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.PositionLatitude); 
		sprintf(strTmp," :  %.6f",u32/1000000.0f);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
// 경도 
		sprintf(strTmp,"xxx PositionLongitude");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		u32 =  EnDeCoder.SwapUINT32(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.PositionLongitude); 
		sprintf(strTmp," :  %.6f",u32/1000000.0f);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PositionAltitude");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.PositionAltitude));			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SpeedNorth");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",					EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.SpeedNorth));					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"SpeedEas");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.SpeedEast));				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SpeedDown");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",				EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.SpeedDown));				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"GroundSpeed");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",				EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.GroundSpd));				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"HeadingAngle");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_23.Send.Value.cadp_23.AttitudeHeadingAngle));	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"DataFusion");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Send.Value.cadp_23.DataFusion);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CollisionRisk");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",					EnDeCoder.m_CCADP_23.Send.Value.cadp_23.CollisionRisk);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CollisionEstimatedTime");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_23.Send.Value.cadp_23.CollisionEstimatedTime);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CRC16");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",						EnDeCoder.m_CCADP_23.Send.Value.cadp_23.CRC16);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;




	}


}



void 	CCASSGL::PrintCADP_12Data(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
	

	if( EnDeCoder.m_CCADP_12.nSendReceive == 0 )
	{
		sprintf(strTmp,"ADS-B Setup (Cnt %d)", EnDeCoder.m_CCADP_12.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x %x",					EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Header[0], EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Header[1] );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		
		sprintf(strTmp,"PaloadLength ");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %d",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.PaloadLength );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketSequence");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.PacketSequence );		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");	;	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",		EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.SendingSystemID );	;	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.TargetSystemID);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",				EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.MessageID );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"IDENT");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",						EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.IDENT);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Trans Alt Inhibit");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",	EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.TransmitAltitudeInhibit);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TransmitStandby");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",				EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.TransmitStandby);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved1");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",				EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Reserved1);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SetCallSign");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",				EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.SetCallSign);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved2");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Reserved2		);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved3");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Reserved3	);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitFISBOutput");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",		EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InhibitFISBOutput	);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitTrafficReport");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",	EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InhibitTrafficReport);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved4");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,": %x",			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.Reserved4	);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputSquawkCod");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,": %x",		EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputSquawkCode);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputCallSign");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
	
		sprintf(strTmp,":  %c%c%c%c%c%c%c%c",
			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[0],EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[1],
			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[2],EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[3],
			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[4],EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[5],
			EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[6],EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InputCallSign[7]);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT);nY+=nGap;
	

		sprintf(strTmp,"CRC16");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",					EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.CRC16 );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send C CADP_12 (Cnt %d)", EnDeCoder.m_CCADP_12.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x %x",					EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Header[0], EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Header[1] );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		
		sprintf(strTmp,"PaloadLength ");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"PaloadLength  : %d",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.PaloadLength );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketSequence");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"PacketSequence : %x",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.PacketSequence );		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");	;	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"SendingSystemID : %x",		EnDeCoder.m_CCADP_12.Send.Value.cadp_12.SendingSystemID );	;	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"TargetSystemID: %x",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.TargetSystemID);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"MessageID : %x",				EnDeCoder.m_CCADP_12.Send.Value.cadp_12.MessageID );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"IDENT");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"IDENT : %x",						EnDeCoder.m_CCADP_12.Send.Value.cadp_12.IDENT);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TransmitAltitudeInhibit");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"TransmitAltitudeInhibit	: %x",	EnDeCoder.m_CCADP_12.Send.Value.cadp_12.TransmitAltitudeInhibit);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TransmitStandby");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"TransmitStandby: %x",				EnDeCoder.m_CCADP_12.Send.Value.cadp_12.TransmitStandby);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved1");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"Reserved1: %x",				EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Reserved1);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SetCallSign");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"SetCallSign	: %x",				EnDeCoder.m_CCADP_12.Send.Value.cadp_12.SetCallSign);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved2");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"Reserved2: %x",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Reserved2		);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved3");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"Reserved3	: %x",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Reserved3	);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitFISBOutput");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"InhibitFISBOutput	: %x",		EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InhibitFISBOutput	);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitTrafficReport");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"InhibitTrafficReport: %x",	EnDeCoder.m_CCADP_12.Recv.Value.cadp_12.InhibitTrafficReport);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved4");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,"Reserved4		: %x",			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.Reserved4	);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputSquawkCod");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,": %x",		EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputSquawkCode);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputCallSign");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
	
		sprintf(strTmp,":  %c %c %c %c %c %c %c %c",
			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[0],EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[1],
			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[2],EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[3],
			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[4],EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[5],
			EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[6],EnDeCoder.m_CCADP_12.Send.Value.cadp_12.InputCallSign[7]);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT);
	

		sprintf(strTmp,"CRC16");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,":  %x",					EnDeCoder.m_CCADP_12.Send.Value.cadp_12.CRC16 );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	}
}


void 	CCASSGL::PrintCADP_8Data( int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if( EnDeCoder.m_CCADP_8.nSendReceive == 0 )
	{
		sprintf(strTmp,"Recv PayLoad %d (Cnt %d)",EnDeCoder.m_nPayLoadCheck, EnDeCoder.m_nPayLoadCheckCount);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Coll. Avoid Cmd (Cnt %d)",EnDeCoder.m_CCADP_8.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header	: 0X%x%x",			EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.Header[0],EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.Header[1] );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"PaloadLength");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.PaloadLength );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PacketSequence");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.PacketSequence );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",	EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.SendingSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.TargetSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID" );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.MessageID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDHeadingAngle");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %.1f",	EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.CMDHeadingAngle)*0.1f);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDAltitude");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %.1f",		EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.CMDAltitude) *0.1f);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDSpeed");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %.1f",			EnDeCoder.SwapUINT16(EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.CMDSpeed) *0.1f);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CRC16");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.CRC16 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send CADP_8 (Cnt %d)",EnDeCoder.m_CCADP_8.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header	: 0X%x%x",			EnDeCoder.m_CCADP_8.Send.Value.cadp_8.Header[0],EnDeCoder.m_CCADP_8.Send.Value.cadp_8.Header[1] );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"PaloadLength");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Send.Value.cadp_8.PaloadLength );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PacketSequence");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Send.Value.cadp_8.PacketSequence );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",	EnDeCoder.m_CCADP_8.Send.Value.cadp_8.SendingSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Send.Value.cadp_8.TargetSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID" );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_8.Send.Value.cadp_8.MessageID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDHeadingAngle");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",	EnDeCoder.m_CCADP_8.Send.Value.cadp_8.CMDHeadingAngle );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDAltitude");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_CCADP_8.Send.Value.cadp_8.CMDAltitude );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CMDSpeed");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADP_8.Send.Value.cadp_8.CMDSpeed );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"CRC16");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADP_8.Send.Value.cadp_8.CRC16 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	}
}



void 	CCASSGL::PrintCASOperationConfirm( int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if( EnDeCoder.m_COperConfirm.nSendReceive == 0 )
	{
		sprintf(strTmp,"Recv PayLoad %d (Cnt %d)",EnDeCoder.m_nPayLoadCheck, EnDeCoder.m_nPayLoadCheckCount);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CAS Oper. Confirm (Cnt %d)",EnDeCoder.m_COperConfirm.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header	: 0X%x%x",			EnDeCoder.m_COperConfirm.Recv.Value.Oper.Header[0],EnDeCoder.m_COperConfirm.Recv.Value.Oper.Header[1] );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"PaloadLength" );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Recv.Value.Oper.PaloadLength );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PacketSequence");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Recv.Value.Oper.PacketSequence );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",	EnDeCoder.m_COperConfirm.Recv.Value.Oper.SendingSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Recv.Value.Oper.TargetSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID" );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_COperConfirm.Recv.Value.Oper.MessageID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Data Save Reserved");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",	EnDeCoder.m_COperConfirm.Recv.Value.Oper.Reserved3 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Data Save ");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Recv.Value.Oper.DataSave);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CRC16");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADP_8.Recv.Value.cadp_8.CRC16 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Recv PayLoad %d (Cnt %d)",EnDeCoder.m_nPayLoadCheck, EnDeCoder.m_nPayLoadCheckCount);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CAS Oper. Confirm (Cnt %d)",EnDeCoder.m_COperConfirm.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header	: 0X%x%x",			EnDeCoder.m_COperConfirm.Send.Value.Oper.Header[0],EnDeCoder.m_COperConfirm.Send.Value.Oper.Header[1] );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"PaloadLength");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Send.Value.Oper.PaloadLength );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"PacketSequence");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Send.Value.Oper.PacketSequence );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",	EnDeCoder.m_COperConfirm.Send.Value.Oper.SendingSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Send.Value.Oper.TargetSystemID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID" );
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_COperConfirm.Send.Value.Oper.MessageID );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Data Save Reserved");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",	EnDeCoder.m_COperConfirm.Send.Value.Oper.Reserved3 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Data Save ");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",		EnDeCoder.m_COperConfirm.Send.Value.Oper.DataSave);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"CRC16");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_COperConfirm.Send.Value.Oper.CRC16 );
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	}
}


void 	CCASSGL::PrintCADRData( int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	if(nSend == 0)
	{
		sprintf(strTmp,"Recv CADR (Cnt %d)",EnDeCoder.m_CCADR.nRecvCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x%x",	EnDeCoder.m_CCADR.Recv.Value.cadr.Header[0],	EnDeCoder.m_CCADR.Recv.Value.cadr.Header[1] );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PayloadLength" );	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADR.Recv.Value.cadr.PaloadLength );	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketSequence" );		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %d",			EnDeCoder.m_CCADR.Recv.Value.cadr.PacketSequence );		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SendingSystemID");	;			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",		EnDeCoder.m_CCADR.Recv.Value.cadr.SendingSystemID );	;			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TargetSystemID");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",			EnDeCoder.m_CCADR.Recv.Value.cadr.TargetSystemID);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"MessageID ");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADR.Recv.Value.cadr.MessageID );				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"IDENT");					
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",						EnDeCoder.m_CCADR.Recv.Value.cadr.IDENT);					
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TransAltInhibit");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",	EnDeCoder.m_CCADR.Recv.Value.cadr.TransmitAltitudeInhibit);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"TransmitStandby");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADR.Recv.Value.cadr.TransmitStandby);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved1");				
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADR.Recv.Value.cadr.Reserved1);				
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"SetCallSign");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",				EnDeCoder.m_CCADR.Recv.Value.cadr.SetCallSign);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved2");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",			EnDeCoder.m_CCADR.Recv.Value.cadr.Reserved2		);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved3");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",			EnDeCoder.m_CCADR.Recv.Value.cadr.Reserved3	);			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitFISBOutput");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,": %x",		EnDeCoder.m_CCADR.Recv.Value.cadr.InhibitFISBOutput	);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InhibitTrafficReport");
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",	EnDeCoder.m_CCADR.Recv.Value.cadr.InhibitTrafficReport);
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Reserved4");	
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",			EnDeCoder.m_CCADR.Recv.Value.cadr.Reserved4	);	
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputSquawkCode");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %x",		EnDeCoder.m_CCADR.Recv.Value.cadr.InputSquawkCode);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"InputCallSign");		
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
		sprintf(strTmp,":  %c%c%c%c%c%c%c%c",EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[0],EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[1],
			EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[2],EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[3],
			EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[4],EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[5],
			EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[6],EnDeCoder.m_CCADR.Recv.Value.cadr.InputCallSign[7]
		);		
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	
		sprintf(strTmp,"CRC16");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",					EnDeCoder.m_CCADR.Recv.Value.cadr.CRC16 );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send CADR (Cnt %d)",EnDeCoder.m_CCADR.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Header");			


		if(g_CADR_RS232.Value.cadr.PaloadLength  == 8)
		{

			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x%x",	EnDeCoder.m_CAS_8.Header[0],	EnDeCoder.m_CAS_8.Header[1] );	
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"PayloadLength" );	
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp," : %d",			EnDeCoder.m_CAS_8.PaloadLength );	
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"PacketSequence" );		
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",			EnDeCoder.m_CAS_8.PacketSequence );		
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"SendingSystemID");	;			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",		EnDeCoder.m_CAS_8.SendingSystemID );	;			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"TargetSystemID");			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",			EnDeCoder.m_CAS_8.TargetSystemID);			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"MessageID ");				
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",				EnDeCoder.m_CAS_8.MessageID );				
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"Data Save");					
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",						EnDeCoder.m_CAS_8.DataSave);					
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
		}
		else
		{
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x%x",	EnDeCoder.m_CCADR.Send.Value.cadr.Header[0],	EnDeCoder.m_CCADR.Send.Value.cadr.Header[1] );	
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"PayloadLength" );	
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp," : %d",			EnDeCoder.m_CCADR.Send.Value.cadr.PaloadLength );	
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"PacketSequence" );		
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",			EnDeCoder.m_CCADR.Send.Value.cadr.PacketSequence );		
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"SendingSystemID");	;			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",		EnDeCoder.m_CCADR.Send.Value.cadr.SendingSystemID );	;			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"TargetSystemID");			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",			EnDeCoder.m_CCADR.Send.Value.cadr.TargetSystemID);			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"MessageID ");				
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",				EnDeCoder.m_CCADR.Send.Value.cadr.MessageID );				
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;
			sprintf(strTmp,"IDENT");					
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",						EnDeCoder.m_CCADR.Send.Value.cadr.IDENT);					
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"TransmitAltitudeInhibit");
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",	EnDeCoder.m_CCADR.Send.Value.cadr.TransmitAltitudeInhibit);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"TransmitStandby");		
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",				EnDeCoder.m_CCADR.Send.Value.cadr.TransmitStandby);		
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"Reserved1");				
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",				EnDeCoder.m_CCADR.Send.Value.cadr.Reserved1);				
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"SetCallSign");			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",				EnDeCoder.m_CCADR.Send.Value.cadr.SetCallSign);			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"Reserved2");			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",			EnDeCoder.m_CCADR.Send.Value.cadr.Reserved2		);			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"Reserved3");			
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",			EnDeCoder.m_CCADR.Send.Value.cadr.Reserved3	);			
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"InhibitFISBOutput");
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
			sprintf(strTmp,": %x",		EnDeCoder.m_CCADR.Send.Value.cadr.InhibitFISBOutput	);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"InhibitTrafficReport");
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",	EnDeCoder.m_CCADR.Send.Value.cadr.InhibitTrafficReport);
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"Reserved4");	
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",			EnDeCoder.m_CCADR.Send.Value.cadr.Reserved4	);	
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"InputSquawkCode");		
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %x",		EnDeCoder.m_CCADR.Send.Value.cadr.InputSquawkCode);		
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

			sprintf(strTmp,"InputCallSign");		
			Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT);
			sprintf(strTmp,": %c%c %c%c %c%c %c%c",			EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[0], EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[1],
				EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[2], EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[3],
				EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[4], EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[5],
				EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[6], EnDeCoder.m_CCADR.Send.Value.cadr.InputCallSign[7]
			);		
			Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;






		}
		
		sprintf(strTmp,"CRC16");			
		Printf( (int) nX, (int) nY ,strTmp, MIDDLE_FONT); 
		sprintf(strTmp,":  %x",					EnDeCoder.m_CCADR.Send.Value.cadr.CRC16 );			
		Printf( (int) nXV, (int) nY ,strTmp, MIDDLE_FONT); nY+=nGap;

	}
	

}

void 	CCASSGL::PrintGPS_INSData(int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;


	if( nSend  == 0 )
	{
		sprintf(strTmp,"Recv GPS_INS (cnt %d)",EnDeCoder.m_CGPS_INS.nRecvCnt );
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Header : %x%x",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Header[0], EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Header[1]) ;								// 0
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Yaw") ;		 		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Yaw) ;		 		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Pitch") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Pitch) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Roll") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Roll) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_P") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_P) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_Q") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_Q) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_R") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_R) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																		
		sprintf(strTmp,"GPSAltitude") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.GPSAltitude) ;	
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vn") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Vn) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Ve") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Ve) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vd") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Vd) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"AccX") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccX) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccY") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccY) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccZ") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccZ) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Longitude ") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Longitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Latitude") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Latitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Time") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":  Y%dM%d%D%dH%dM%dS%d",EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[0],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[1],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[2],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[3],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[4],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[5],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[6],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[7]
		) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"GPSFixMode") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %d",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.GPSFixMode) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.CheckSum) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send GPS_INS (Cnt %d)",EnDeCoder.m_CGPS_INS.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Header") ;								// 0
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %x%x",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Header[0], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Header[1]) ;								// 0
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Yaw") ;		 		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					EnDeCoder. m_CGPS_INS.Send.Value.gpsIns.Yaw) ;		 		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Pitch") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Pitch) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Roll") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Roll) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_P") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_P) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_Q") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_Q) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_R") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_R) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																		
		sprintf(strTmp,"GPSAltitude") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.GPSAltitude) ;	
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vn(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Vn) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Ve(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Ve) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vd(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Vd) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"AccX") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccX) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccY") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccY) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccZ") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccZ) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Longitude ") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Longitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Latitude  : %f") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Latitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"TimeY ") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":  20%d:%d:%d:%d:%d:%d",	
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[0], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[1],
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[2], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[3],
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[4], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[5]
			) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



		sprintf(strTmp,"GPSFixMode") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %d",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.GPSFixMode) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.CheckSum) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
}


void 	CCASSGL::PrintGPS_INS_BufferData(int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;


	if( nSend  == 0 )
	{
		sprintf(strTmp,"Recv GPS_INS (cnt %d)",EnDeCoder.m_CGPS_INS.nRecvCnt );
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	



		sprintf(strTmp,"Header : %x%x",			 EnDeCoder.m_CGPS_INS_BUFFER.Recv.Value.gpsInsBuf.Header[0], EnDeCoder.m_CGPS_INS_BUFFER.Recv.Value.gpsInsBuf.Header[1]) ;								// 0
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Yaw") ;		 		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Yaw) ;		 		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Pitch") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Pitch) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Roll") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Roll) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_P") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_P) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_Q") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_Q) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_R") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AngularRate_R) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																		
		sprintf(strTmp,"GPSAltitude") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.GPSAltitude) ;	
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vn(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Vn) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Ve(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Ve) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vd(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Vd) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"AccX") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccX) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccY") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccY) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccZ") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.AccZ) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Longitude ") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Longitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Latitude  : %f") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.Latitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Time") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":  Y%dM%d%D%dH%dM%dS%d",EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[0],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[1],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[2],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[3],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[4],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[5],
			EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[6],EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.TimeYMDHMS[7]
		) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"GPSFixMode") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %d",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.GPSFixMode) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS.Recv.Value.gpsIns.CheckSum) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
	else
	{
		sprintf(strTmp,"Send GPS_INS (Cnt %d)",EnDeCoder.m_CGPS_INS_BUFFER.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		//unsigned long uMiliSecond = 0;
		//uMiliSecond =  clock()*1000/CLOCKS_PER_SEC;
		//if( gfThreadTime > 0.01)
		//{
		//	sprintf(strTmp,"Count %d, Hz %.0f , %d ",gLoopCount, 1.0f/ gfThreadTime, uMiliSecond % 1000);
		//	Printf( (int) nX, (int)  nY ,strTmp,MIDDLE_FONT); nY+=nGap;
		//}

		sprintf(strTmp,"Header") ;								// 0
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %x%x",			 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.Header[0], EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.Header[1]) ;								// 0
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Yaw") ;		 		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					EnDeCoder. m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fYaw_rad) ;		 		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Pitch") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fPitch_rad) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Roll") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fRoll_rad) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_P") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fBodyAngularRate_P_rps) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_Q") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fBodyAngularRate_Q_rps) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_R") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fBodyAngularRate_R_rps) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																		
		sprintf(strTmp,"GPSAltitude") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fGPSAltitude_m) ;	
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vn") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fVn_mps) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Ve") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fVe_mps) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vd") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fVd_mps) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"AccX") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fAccX_g) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccY") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fAccY_g) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccZ") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.fAccZ_g) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Longitude ") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.dLongitude_deg) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Latitude  : %f") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.dLattitude_deg) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"TimeY ") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":  20%d:%d:%d:%d:%d:%d",	
			EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nYear, EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nMonth,
			EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nDay, EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nHour,
			EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nMinute, EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nSecond
			) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Send Time ms") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 

		sprintf(strTmp,":  %d",	EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.u16MiliSecond) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;




		sprintf(strTmp,"GPSFixMode") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %d",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.m_nFixMode) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.gpsInsBuf.CRC16) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,": %x%x",		 EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.uc[109],EnDeCoder.m_CGPS_INS_BUFFER.Send.Value.uc[110]) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Size Of Data") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %d",		 sizeof(GPS_INS_RS232_BUFFER)) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
}





void CCASSGL::ShowRS232Message()
{

	int			nX, nY;
	int			nXStart = 10;
	int			nYStart = 40;

	char		strTmp[256];
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fScreenX = 1920, ScreenY = 1080;
//	float		fScreenX = 1920, ScreenY = 1080;
	float		fScaleX, fScaleY;
	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	int		w = GetCanvasWidth()	;
	int		h = GetCanvasHeight()	;

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, m_nWndWidth, 0.0 ,  m_nWndHeight);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);



	nX = nXStart;
	nY = nYStart;



	nXStart = ScreenY;

	

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);

///	DrawRectangle(10.0, 10.0, m_nWndWidth-10 , m_nWndHeight-10 );

	nY = m_nWndHeight - nYStart;

	if(EnDeCoder.m_nKUCAS_Mode == 0 )
	{

		glColor3f(1.0f, 0.0f, 0.0f);
	// 송신 정보 보기	

	//  Comport #1 => 
	//	PrintHearbeatData(nX , inY, 1) ;
		PrintADS_B_TrafficData( nX , nY, 1); nX+=250;

	//  Comport #2 => 
		PrintVisualData( nX , nY, 1);nX+=250;


	//  Comport #3 => 수신 메시지에 대한 응답신호를 송신한다.
		// 송신 
 		PrintCollisionAvoidanceResponceData( nX , nY, 1);
		// 수신 
		glColor3f(0.0f, 1.0f, 0.0f);
		nY = m_nWndHeight - 300;
		PrintCollisionAvoidanceCommandData(nX, nY,0); nX+=250;


	// Comport #4 =>
		nY = m_nWndHeight - nYStart;
		glColor3f(1.0f, 0.0f, 0.0f);

	//	PrintGPS_INSData(nX , nY, 1);nX+=250;
		PrintGPS_INS_BufferData(nX , nY, 1);nX+=250;
		// Comport #5 => 
		PrintCADRData(nX , nY, 1);nX+=250;
		// 수신데이터 보기
		glColor3f(1.0f, 1.0f, 0.0f);
		nY = m_nWndHeight - 620;
		nX -= 1250;
		PrintCASOperationConfirm(nX,  nY);nX+=250;
		PrintCADP_8Data(nX,  nY);nX+=250;

		nY = m_nWndHeight - 490;
		PrintCADP_12Data(nX, nY);nX+=250;
		PrintCADP_23Data(nX, nY, 0); nX+=250;
		///////////////////////////////////////////
		nY = m_nWndHeight - 440;
		PrintGPS_INS_219Data(nX, nY, 0); 
	}
	else // FCC
	{
		// 수신 정보 보기
		glColor3f(0.0f, 1.0f, 0.0f);
		// Comport #1 => 
	//	PrintCADP_8Data( int x, int y);nX+=280;
	//	PrintCADP_12Data(int x, int y);nX+=280;
		PrintCADP_23Data( nX , nY, 0);nX+=280;

		// Comport #2 => 
	//	PrintHearbeatData(nX , inY, 1) ;
		PrintADS_B_TrafficData( nX , nY, 0); nX+=280;

		// Comport #3 => 
		PrintVisualData( nX , nY, 0);nX+=280;
		// Comport #4 => 
		PrintCADRData(nX , nY, 0);nX+=280;

		// Comport #5 => 
		PrintGPS_INSData(nX , nY, 0);nX+=280;
		// 송신데이터 보기
		glColor3f(1.0f, 0.0f, 0.0f);
		PrintCollisionAvoidanceCommandData(nX, nY, 1);nX+=280;
		PrintCADP_23Data( nX, nY, 1);
		///////////////////////////////////////////
		PrintGPS_INS_219Data(nX, nY, 0); 

	}















	glPopMatrix();
	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));

}

/////////////////////////////////////////////////////////////////////////////////////

void 	CCASSGL::PrintADS_B_RecvData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int		i;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	glColor3f(1.0f, 1.0f, 0.0f);
	sprintf(strTmp,"ADS_B Message Recv" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"PayloadType : %d", g_CSSSMaster.m_ADS_B_RecvMsg.m_nPayloadTypeADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// Address Qualify 
	sprintf(strTmp,"AddressQuility : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nAddressQuilityADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// Address

	sprintf(strTmp,"Address : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nAddressADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	// latitude

	sprintf(strTmp,"Latitude : %f",g_CSSSMaster.m_ADS_B_RecvMsg.m_fLatitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// longitude

	sprintf(strTmp,"Longitude : %f",g_CSSSMaster.m_ADS_B_RecvMsg.m_fLongitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// AltType
	sprintf(strTmp,"AltTypeADS_B : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nAltTypeADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
    // Altitude

	sprintf(strTmp,"Altitude : %f",g_CSSSMaster.m_ADS_B_RecvMsg.m_fAltitude );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// NIC
	sprintf(strTmp,"NIC : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nNICADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// NS 
	sprintf(strTmp,"NS : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nNSADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// North velocity

	sprintf(strTmp,"NorthVelocity : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nNorthVelocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// EW 
	sprintf(strTmp,"EW : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nEWADS_B);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// East velocity

	sprintf(strTmp,"EastVelocity : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nEastVelocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// Ground speed 

	sprintf(strTmp,"GrounSpeed : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nGrounSpeed );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// Track Angle

	sprintf(strTmp,"ndHeading : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_nGndHeading);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



	
}

void 	CCASSGL::PrintADS_B_RecvBufferData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int		i;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	glColor3f(1.0f, 1.0f, 0.0f);
	sprintf(strTmp,"ADS_B Message Recv" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"STX : 0x%x",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.STX & 0xff);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Data Length  : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.DataLengh & 0xff);							// 1
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"TOMR : %d",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.TOMR);								// 4
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	glColor3f(1.0f, 0.0f, 0.0f);
	sprintf(strTmp,"Buffer[34]",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.TOMR);								// 4
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	for(i=0;i<34;i++)
	{
		sprintf(strTmp,"[%d]: 0x%x",i, g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.m_ADS_PayLoad[i] & 0xff);					// 34
		Printf( (int) nX+20, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
	glColor3f(1.0f, 1.0f, 0.0f);
	sprintf(strTmp,"ETX : 0x%x",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.ETX);								// 1
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;	
	sprintf(strTmp,"CheckSum : 0x%x",g_CSSSMaster.m_ADS_B_RecvMsg.m_ADS_B_MSG.CheckSum & 0xff);							// 2
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


}


void CCASSGL::ShowADS_B_RecvMsg()
{

	int			nX, nY;
	int			nXStart = 10;
	int			nYStart = 10;

	char		strTmp[256];
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fScreenX = 1920, ScreenY = 1080;
//	float		fScreenX = 1920, ScreenY = 1080;
	float		fScaleX, fScaleY;
	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	int		w = GetCanvasWidth()	;
	int		h = GetCanvasHeight()	;

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, m_nWndWidth, 0.0 ,  m_nWndHeight);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);



	nX = nXStart;
	nY = nYStart;



	nXStart = ScreenY;

	

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);

	DrawRectangle(10.0, 10.0, m_nWndWidth-10 , m_nWndHeight-10 );
	nY = m_nWndHeight - 20;


	PrintADS_B_RecvData(nX, nY); nX+=200;

	PrintADS_B_RecvBufferData (nX, nY); nX+=200;

	PrintUAT_ADS_BSendData(nX, nY);


	glPopMatrix();
	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));

}



void CCASSGL::PrintCat21_FSPEC(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;
	float		fLat, fLong;
	float		fValue;
	float		fAlt, fSpeed, fHeading;



	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
	

	SetColor(RED);
	sprintf(strTmp,"ADS_B Cat 21 FSPEC State" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
	// FSPEC #1
	SetColor(RED);
	sprintf(strTmp,"FSPEC #1");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"Data_Source_Identification  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Data_Source_Identification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Target_Report_Descriptor  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Target_Report_Descriptor);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Track_Number  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Track_Number);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Service_Identification  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Service_Identification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Time_of_Applicability_for_Position  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Applicability_for_Position);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Position_in_WGS_84_co_ordinates  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Position_in_WGS_84_co_ordinates);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Position_in_WGS_84_co_ordinates_high_res  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Position_in_WGS_84_co_ordinates_high_res);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_1  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_1);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// FSPEC #2

	SetColor(RED);
	sprintf(strTmp,"FSPEC #2");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"Time_of_Applicability_for_Velocity  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Applicability_for_Velocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Air_Speed  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Air_Speed);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"True_Air_Speed  : %d",SI.Cat21.m_FSPEC.MSG.Layout.True_Air_Speed);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Target_Address  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Target_Address);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"TMR Position  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Message_Reception_of_Position);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"TMRe Position_High  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Message_Reception_of_Position_High_Precision);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"TMR Velocity  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Message_Reception_of_Velocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_2  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_2);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// FSPEC #3
	SetColor(RED);
	sprintf(strTmp,"FSPEC #3");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"TMReception_of_Velocity_High : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Message_Reception_of_Velocity_High_Precision);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Geometric_Height  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Geometric_Height);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Quality_Indicators  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Quality_Indicators);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"MOPS_Version  : %d",SI.Cat21.m_FSPEC.MSG.Layout.MOPS_Version);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Mode_3_A_Code  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Mode_3_A_Code);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"N230_Roll_Angle  : %d",SI.Cat21.m_FSPEC.MSG.Layout.N230_Roll_Angle);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Flight_Level  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Flight_Level);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_3  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_3);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
// FSPEC #4
	SetColor(RED);
	sprintf(strTmp,"FSPEC #4");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"Magnetic_Heading  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Magnetic_Heading);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Target_Status  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Target_Status);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Barometric_Vertical_Rate  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Barometric_Vertical_Rate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Geometric_Vertical_Rate  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Geometric_Vertical_Rate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Airborne_Ground_Vector  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Airborne_Ground_Vector);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Track_Angle_Rate  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Track_Angle_Rate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Time_of_Report_Transmission  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Time_of_Report_Transmission);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_4  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_4);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
// FSPEC #5
	nX += 350;
	nY = y+nGap;

	SetColor(RED);
	sprintf(strTmp,"FSPEC #5");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"TargetIdentification  : %d",SI.Cat21.m_FSPEC.MSG.Layout.TargetIdentification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"EmitterCategory  : %d",SI.Cat21.m_FSPEC.MSG.Layout.EmitterCategory);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"MetInformation  : %d",SI.Cat21.m_FSPEC.MSG.Layout.MetInformation);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"SelectedAltitude  : %d",SI.Cat21.m_FSPEC.MSG.Layout.SelectedAltitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"FinalStateSelectedAltitude  : %d",SI.Cat21.m_FSPEC.MSG.Layout.FinalStateSelectedAltitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"TrajectoryIntent  : %d",SI.Cat21.m_FSPEC.MSG.Layout.TrajectoryIntent);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"ServiceManagement  : %d",SI.Cat21.m_FSPEC.MSG.Layout.ServiceManagement);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_5  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_5);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

// FSPEC #6
	SetColor(RED);
	sprintf(strTmp,"FSPEC #6");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"AircraftOperationSatus  : %d",SI.Cat21.m_FSPEC.MSG.Layout.AircraftOperationSatus);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"SurfaceCapabilitiesCharacteristic  : %d",SI.Cat21.m_FSPEC.MSG.Layout.SurfaceCapabilitiesCharacteristic);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"MessageAmplitude  : %d",SI.Cat21.m_FSPEC.MSG.Layout.MessageAmplitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Mode_S_MB_Data  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Mode_S_MB_Data);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"ACAC_Resolution_Advisory_Report  : %d",SI.Cat21.m_FSPEC.MSG.Layout.ACAC_Resolution_Advisory_Report);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Receiver_ID  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Receiver_ID);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Data_Ages  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Data_Ages);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_6  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_6);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

// FSPEC #7

	SetColor(RED);
	sprintf(strTmp,"FSPEC #7");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"Not_Used_1  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Not_Used_1);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Not_Used_2  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Not_Used_2);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Not_Used_3  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Not_Used_3);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Not_Used_4  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Not_Used_4);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Not_Used_5  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Not_Used_5);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Reserved_Expansion_Field  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Reserved_Expansion_Field);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Special_Purpose_Field  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Special_Purpose_Field);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Field_extension_indicator_7  : %d",SI.Cat21.m_FSPEC.MSG.Layout.Field_extension_indicator_7);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

}



void CCASSGL::PrintCat21_SendData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			nXSpace = 30;
	int			i,j,k;
	float		fLat, fLong;
	float		fValue;
	float		fAlt, fSpeed, fHeading;



	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
	

	SetColor(RED);
	sprintf(strTmp,"Send ADS_B Cat 21 Message Value To GBT" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// FSPEC #1
	int	nFrnNo=1;

	SetColor(RED);
	sprintf(strTmp,"FSPEC #1");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"No %d [010] DataSourceIdentification  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nDataSourceIdentification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

//  SAC, SIC
	SetColor(RED);
	sprintf(strTmp,"SAC = 0x%2x,  SIC = 0x%2x ", 
		SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nDataSourceIdentification],
		SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nDataSourceIdentification+1]);
	Printf( (int) nX+20, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);




	sprintf(strTmp,"No %d [040]  TargetReportDescriptor  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTargetReportDescriptor);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	TARGET_REPORT_DESCRIPTOR	trd;

	SetColor(RED);

	trd.data.ch  = SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nTargetReportDescriptor];

	sprintf(strTmp,"TRD0 %d,ATP %d,ARC %d RC %d RAB %d FX %d ", 
		trd.data.ch,
		trd.data.bitsPS.ATP,  trd.data.bitsPS.ARC,trd.data.bitsPS.RC , trd.data.bitsPS.RAB, trd.data.bitsPS.FX );
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);



///////////////////////////////////////////////////////////////////////////////////////////////////////////
	sprintf(strTmp,"No %d [161] TrackNumber  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTrackNumber);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	SetColor(RED);

	
	unsigned short nTN;
	char		   tCh[2];

//	unsigned short xx;
//	xx =12345;
	memcpy((char *) &tCh, (char *) &SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nTrackNumber],2);
//	memcpy((char *) &tCh, (char *) &xx,2);
	tCh[0] = (tCh[0] & 0x0f);
	memcpy((char *)&nTN, (char *) &tCh,2);
	sprintf(strTmp," %d ", nTN);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sprintf(strTmp,"No %d [015] ServiceIdentication  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nServiceIdentication);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [071] TimeOfApplicationPosition  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTimeOfApplicationPosition);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [130]nWGS84Coord  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nWGS84Coord);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	SetColor(RED);
	sprintf(strTmp,"Latitude : %.8f", SI.Cat21.m_fLatitude);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Longtitude : %.8f", SI.Cat21.m_fLongitude);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);


	sprintf(strTmp,"No %d [131] WGS84Coord High [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nWGS84CoordHigh);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
	

	// FSPEC #2

	SetColor(RED);
	sprintf(strTmp,"FSPEC #2");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"No %d [072] TimeApplicableVelocity  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTimeApplicableVelocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

/// Air Speed 
	sprintf(strTmp,"No %d [150] AirSpeed  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nAirSpeed);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
	sprintf(strTmp," %.2f IAS(Knots)",SI.Cat21.m_fSpeed);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	//float	fIASScale = 1.0f/(2^14);
	//float	fMachScale = 0.001f;
	//
	//char chIM = SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nAirSpeed];
	//char IM = 0x80 & chIM;

	//SetColor(RED);
	//if( IM == 0x00) // IAS
	//{
	//	fSpeed = SI.ConvertShortToFloatWithFirstBitOut((char *)&SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nAirSpeed],1,fIASScale );
	//	sprintf(strTmp," %.2f IAS",fSpeed);
	//}
	//else // Mach 
	//{
	//	fSpeed = SI.ConvertShortToFloatWithFirstBitOut((char *)&SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nAirSpeed],1, fMachScale );
	//	sprintf(strTmp," %.2f Mach",fSpeed);

	//}
	//
	//Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	//SetColor(YELLOW);

/// Air True Speed 				
	sprintf(strTmp,"No %d [151] TrueAirSpeed  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTrueAirSpeed);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
	SetColor(RED);
	sprintf(strTmp," %.2f IAS(Knots)",SI.Cat21.m_fSpeed);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);
////////////////////////////////////




	sprintf(strTmp,"No %d [080] TargetAddress  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTargetAddress);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(RED);

	sprintf(strTmp,"%x%x%x", SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nTargetAddress],SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nTargetAddress+1],SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nTargetAddress+2] );
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	SetColor(YELLOW);



	sprintf(strTmp,"No %d [073] TMRP  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTMRP);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [074] TMRPHigh  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTMRPHigh);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [075] TMRVelocity  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTMRVelocity);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	int			nFX_2;
	// FSPEC #3

	SetColor(RED);
	sprintf(strTmp,"FSPEC #3");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"No %d [076] TMRVelocityHigh  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTMRVelocityHigh);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"No %d [140]GeometricHeight  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nGeometricHeight);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(RED);

	fAlt = SI.ConvertByteToFloat((char *)&SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nGeometricHeight], 2,6.25f);
	sprintf(strTmp," %.2f ft", fAlt);
	Printf( (int) nX +nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);




	sprintf(strTmp,"No %d [090] QualityIndicators  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nQualityIndicators);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [210] MOPSVersion  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nMOPSVersion);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [070] Mode3ACode  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nMode3ACode);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [230] RollAngle  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nRollAngle);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [145] FlightLevel  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nFlightLevel);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	// FSPEC #4
	SetColor(RED);
	sprintf(strTmp,"FSPEC #4");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);


	sprintf(strTmp,"No %d [152] MagneticHeading  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nMagneticHeading);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(RED);

	fHeading = SI.ConvertByteToFloat((char *)&SI.Cat21.m_bufCat21Template[SI.Cat21.m_CatFRN.nMagneticHeading], 2,0.0055f);
	sprintf(strTmp,"%.2f Deg", fHeading);
	Printf( (int) nX+nXSpace, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);


	sprintf(strTmp,"No %d [200] TargetStatus  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTargetStatus);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [155] BarometricVerticalRate  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nBarometricVerticalRate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [157] GeometricVerticalRate  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nGeometricVerticalRate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [160] AirbornGroundVector  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nAirbornGroundVector);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [165] TrackAngleRate  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTrackAngleRate);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		
	sprintf(strTmp,"No %d [077] TimeReportTransmission  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTimeReportTransmission);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



	nX = x + 300;
	nY = y + nGap;

	// FSPEC #5

	// FSPEC #4
	SetColor(RED);
	sprintf(strTmp,"FSPEC #5");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"No %d [170] Target Identification  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTargetIdentification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [020] Emitter Category  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nEmitterCategory);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [220] Met Information  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nMetInformation);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [146] SelectedAltitude  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nSelectedAltitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [148] Final StateSelectedAltitude  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nFinalStateSelectedAltitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [110] Trajectory Intent  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nTrajectoryIntent);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [016] Service Management  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nServiceManagement);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	// FSPEC #6
	SetColor(RED);
	sprintf(strTmp,"FSPEC #6");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"No %d [008] Aircraft OperationalStatus  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nAircraftOperationalStatus);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [271] SurfaceCapabilitiesChar  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nSurfaceCapabilitiesChar);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [132] MessageAmplitude  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nMessageAmplitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [250] ModeSMBData  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nModeSMBData);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [260] ACASResolutionAdvisoryReport  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nACASResolutionAdvisoryReport);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [400] ReceiverID  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nReceiverID);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"No %d [295] DataAges  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nDataAges);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(RED);
	sprintf(strTmp,"FSPEC #7");
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(YELLOW);

	sprintf(strTmp,"FRN No %d nReservedExpansionField  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nReservedExpansionField);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"FRN No %d nSpecialPurposeField  [%d]", nFrnNo++,SI.Cat21.m_CatFRN.nSpecialPurposeField);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;








}

void CCASSGL::PrintCat21_SendBufferData (int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
	


	SetColor(RED);
	sprintf(strTmp,"Send ADS_B Cat 21 Message As Buffer To GBT" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(GREEN);

	nY = y+nGap;
	k = 0;
	for(i=0;i<20;i++)
	{
		for(j=0;j<5;j++)
		{
			if( k<10)
			{
				sprintf(strTmp,"[0%d]: 0x%2x", k, SI.Cat21.m_bufCat21Template [k] & 0xff);
				Printf( (int) nX+j*70, (int) nY - i*20 ,strTmp,MIDDLE_FONT); 
			}
			else
			{
				sprintf(strTmp,"[%d]: 0x%2x", k, SI.Cat21.m_bufCat21Template [k] & 0xff);
				Printf( (int) nX+j*70, (int) nY - i*20 ,strTmp,MIDDLE_FONT); 
			}
			k++;
		}
	}
}


void CCASSGL::PrintScenarioData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
	


	SetColor(CYAN);
	sprintf(strTmp,"Scenario(HILS AC) Data Check" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(GREEN);

	sprintf(strTmp,"NoTrack %d", HILS_AC.m_nNoTrack);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"NextPoint %d", HILS_AC.nNextPoint);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"PassedPoint %d", HILS_AC.nPassedPoint);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
	sprintf(strTmp,"Distance From Current Waypoint %.2f", HILS_AC.m_fDistanceFromCurrentWaypoint);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Distance From Next Waypoint %.2f", HILS_AC.m_fDistanceFromNextWaypoint);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Radius To Change  %.2f", HILS_AC.m_fRadiusToChange);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



}


void CCASSGL::ShowCat21SendMessage()
{

	int			nX, nY;
	int			nXStart = 10;
	int			nYStart = 10;

	char		strTmp[256];
	int			nHSpace = 15;  // 줄간격 
	float		x,y;
	float		fScreenX = 1920, ScreenY = 1080;
//	float		fScreenX = 1920, ScreenY = 1080;
	float		fScaleX, fScaleY;
	VERIFY(wglMakeCurrent(m_hGLDC,m_hGLRC));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	int		w = GetCanvasWidth()	;
	int		h = GetCanvasHeight()	;

	glViewport(0, 0, m_nWndWidth, m_nWndHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, m_nWndWidth, 0.0 ,  m_nWndHeight);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);



	nX = nXStart;
	nY = nYStart;



//	nXStart = ScreenY;

	

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);

	DrawRectangle(10.0, 10.0, m_nWndWidth-10 , m_nWndHeight-10 );
	nY = m_nWndHeight - 20;


	PrintCat21_SendData(nX, nY); nX+=700;

	PrintCat21_SendBufferData (nX, nY); nX+=400;

	PrintCat21_FSPEC(nX, nY);

	nX = nXStart+300;
	nY =m_nWndHeight - 500;

	PrintCat247SendData(nX, nY);

nX+=400;
	PrintCat33SendData(nX, nY);


//	PrintScenarioData(nX, nY);



	glPopMatrix();
	glFlush();
	SwapBuffers(m_hGLDC);	
	VERIFY(wglMakeCurrent(m_hGLDC,NULL));

}


void CCASSGL::PrintUAT_ADS_BSendData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;

	CUAT_ADS_B	uat;

	switch (g_CSSSMaster.m_nADS_BSelectedAC)
	{
		case 0 : 
		memcpy((char *) &uat, (char *) & HILS_AC.m_CUAT_ADS_B,sizeof(CUAT_ADS_B));
		break;
		case 1 : 
		memcpy((char *) &uat, (char *) & OtherAC_01.m_CUAT_ADS_B,sizeof(CUAT_ADS_B));
		break;
		case 2 :
		memcpy((char *) &uat, (char *) & OtherAC_02.m_CUAT_ADS_B,sizeof(CUAT_ADS_B));
		 break;
		case 3 : 
		memcpy((char *) &uat, (char *) & OtherAC_03.m_CUAT_ADS_B,sizeof(CUAT_ADS_B));
		break;
		default:
		memcpy((char *) &uat, (char *) & HILS_AC.m_CUAT_ADS_B,sizeof(CUAT_ADS_B));
		break;
	}
	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;
/*	
	//// SV
	// PayLoadType
	m_nPayloadTypeADS_B = (m_ADS_PayLoad[0] >> 3) & 0x1f;
	// Address Qualify 
	m_nAddressQuilityADS_B =  m_ADS_PayLoad[0] & 0x03;
	// Address

	m_nAddressADS_B = SwapUINT32(u32);

	// latitude

	uat.m_fLatitude = u32 / 46603.38;
	// longitude
	m_fLongitude = u32 / 46603.38;
	// AltType
	m_nAltTypeADS_B = 
    // Altitude
	m_fAltitude = (u16 - 41) / 0.04f;
	// NIC
	m_nNICADS_B =  m_ADS_B_MSG.m_ADS_PayLoad[11] & 0xf;
	// NS 
	m_nNSADS_B =  (m_ADS_B_MSG.m_ADS_PayLoad[12] >> 4) & 0x01;
	// North velocity

	m_nNorthVelocity = * (UINT16 *) ap >> 2;
	// EW 
	m_nEWADS_B =  (m_ADS_B_MSG.m_ADS_PayLoad[13] >> 1) & 0x01;
	// East velocity

	m_nEastVelocity = * (UINT32 *) ap >> 7;

	m_nGrounSpeed = * (UINT16 *) ap >> 2;

	m_nGndHeading = * (UINT16 *) ap >> 7;
*/
	SetColor(RED);
	sprintf(strTmp,"UAT MSG Payload SEND DATA" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(GREEN);

	sprintf(strTmp,"SV - State Vector" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Latitude[4, 5, 6] - %.6f   - 0x%2x, 0x%2x, 0x%2x",uat.m_fLatitude , t_ADS_B_MSG.m_ADS_PayLoad[4] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[5] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[6] & 0xff);
	Printf( (int) nX +30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



	sprintf(strTmp,"Longitude[7, 8, 9] - %.6f - 0x%2x, 0x%2x, 0x%2x",uat.m_fLongitude, t_ADS_B_MSG.m_ADS_PayLoad[7] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[8] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[9] & 0xff);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT);nY+=nGap; 

	sprintf(strTmp,"Alt Type [9] - %d - 0X%2x",uat.m_nAltTypeADS_B, t_ADS_B_MSG.m_ADS_PayLoad[9] & 0x01);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Altitude[10,11] - %.2f - 0x%2x, 0x%2x",uat.m_fAltitude, t_ADS_B_MSG.m_ADS_PayLoad[10] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[11] & 0xf0);
	Printf( (int) nX+30 , (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"NIC [11] - %d - 0X%2x",uat.m_nNICADS_B, t_ADS_B_MSG.m_ADS_PayLoad[11] & 0x0f);
	Printf( (int) nX +30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"A/G State [12] - %d - 0X%2x",uat.m_nAGState, t_ADS_B_MSG.m_ADS_PayLoad[12] & 0xc0);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Horizon Vel [12, 13, 14, 15] - 0x%2x, 0x%2x, 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[12] & 0x1f,t_ADS_B_MSG.m_ADS_PayLoad[13] & 0xff,
		t_ADS_B_MSG.m_ADS_PayLoad[14] & 0xff,t_ADS_B_MSG.m_ADS_PayLoad[15] & 0x80);
	Printf( (int) nX +30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"NS %d, Vel %d, EW %d Vel %d", uat.m_nNSADS_B, uat.m_nNorthVelocity, uat.m_nEWADS_B, uat.m_nEastVelocity);
	Printf( (int) nX +60, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Gnd Spd %.2f, Heading %.2f", uat.m_nGrounSpeed, uat.m_nGndHeading);
	Printf( (int) nX +60, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;




	sprintf(strTmp,"Vertical  Vel [15,16] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[15] & 0x7f,t_ADS_B_MSG.m_ADS_PayLoad[16] & 0xf0);
	Printf( (int) nX +30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"UTC  [16] - 0X%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[16] & 0x04);
	Printf( (int) nX+30 , (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Uplink Feed Back [16] - 0X%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[16] & 0x07);
	Printf( (int) nX +30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	SetColor(YELLOW);
	nY+=nGap;
	sprintf(strTmp,"MS  - Mode Status" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Call Sign [17,18] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[17] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[18] & 0xff);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Call Sign [19,20] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[19] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[20] & 0xff);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Call Sign [21,22] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[21] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[22] & 0xff);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	SetColor(RED);
	nY+=nGap;
	sprintf(strTmp,"TS  - Trajectory State" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Select Altitude [23,24] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[23] & 0x7f, t_ADS_B_MSG.m_ADS_PayLoad[24] & 0xf0);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	SetColor(BLUE);
	nY+=nGap;
	sprintf(strTmp,"AS  - Auxiliary State" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Select Altitude [23,24] - 0x%2x, 0x%2x",
		t_ADS_B_MSG.m_ADS_PayLoad[23] & 0xff, t_ADS_B_MSG.m_ADS_PayLoad[24] & 0xf0);
	Printf( (int) nX+30, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

}



void CCASSGL::PrintCat247SendData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;

	CUAT_ADS_B	uat;

	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	SetColor(RED);
	sprintf(strTmp,"Cat 247 :  Send Mesg" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(GREEN);

	sprintf(strTmp,"SendOptionbyUDP         : %d Count [%d]", SI.Cat247.m_nSendOptionbyUDP,SI.Cat247.m_nCountOfSend );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Cat ID                         : %x : %d", SI.Cat247.m_Cat247.nCat & 0xff, SI.Cat247.m_Cat247.nCat);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	
	sprintf(strTmp,"Length                        : %d", SI.Cat247.m_Cat247.nLength);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"FSPEC                        : %X", SI.Cat247.m_Cat247.FSPEC.ch & 0xff);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Data Source ID SAC   : %d", SI.Cat247.m_Cat247.Data.UAP.cDataSourceIdentifer_SAC); // 1
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Data Source ID SIC    : %d", SI.Cat247.m_Cat247.Data.UAP.cDataSourceIdentifer_SIC); // 2
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Service ID                  : %d", SI.Cat247.m_Cat247.Data.UAP.cServiceIdentification);	// 3
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Time Of Day                : %d %d %d", SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[0], SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[1],SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[2]);			// 4 ~ 6
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Ver. No Report_REP    : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_REP);	// 7
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Ver. NoReport_CAT     : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_CAT); // 8 
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Main Ver. No                : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_MainVersion); // 9 
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Sub. Ver. No                : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_SubVersion); // 10
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Buf[ 0 ~ 9 ]                     : %X %X %X %X %X %X %X %X %X %X ",
		SI.Cat247.m_Cat247.Data.buf[0] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[1] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[2] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[3] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[4] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[5] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[6] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[7] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[8] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[9] & 0xFF);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

}



void CCASSGL::PrintCat33SendData(int x, int y)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;
	int			i,j,k;

	CUAT_ADS_B	uat;

	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;

	SetColor(RED);
	sprintf(strTmp,"Cat 33 :  Send Mesg" );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	SetColor(GREEN);




	// FSPEC
	sprintf(strTmp,"Cat 33 :  FSPEC [1] 0x%X, [2]0xX [3]0x%X [4]0x%X",SI.Cat33.m_FSPEC.MSG.ch[0],SI.Cat33.m_FSPEC.MSG.ch[1],SI.Cat33.m_FSPEC.MSG.ch[2],SI.Cat33.m_FSPEC.MSG.ch[3]);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	float			m_fLongitude, m_fLatitude; // 9	
	float			m_fAltitude, m_fSpeed, m_fHeading; // 9	


	sprintf(strTmp,"Long :  %.6f Deg, Lat : %.6f Deg",SI.Cat33.m_fLongitude, SI.Cat33.m_fLatitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Altitude :  %.6f ft, Speed : %.6f KNots",SI.Cat33.m_fAltitude, SI.Cat33.m_fSpeed);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



	// FSPEC #1
	sprintf(strTmp,"[FRN 1][FSPEC %d ]Service_Volume_Identifier         : %d",SI.Cat33.m_FSPEC.MSG.Layout.bService_Volume_Identifier, SI.Cat33.m_FrameNo.nService_Volume_Identifier);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 2][FSPEC %d ]Version_Number          :  %d",SI.Cat33.m_FSPEC.MSG.Layout.bVersion_Number, SI.Cat33.m_FrameNo.nVersion_Number);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 3][FSPEC %d ]Link_Technology_Indicator          : %d",SI.Cat33.m_FSPEC.MSG.Layout.bLink_Technology_Indicator, SI.Cat33.m_FrameNo.nLink_Technology_Indicator);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 4][FSPEC %d ]Time_of_Applicability         : %d",SI.Cat33.m_FSPEC.MSG.Layout.bTime_of_Applicability, SI.Cat33.m_FrameNo.nTime_of_Applicability);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 5][FSPEC %d ]Target_Address         : %d",SI.Cat33.m_FSPEC.MSG.Layout.bTarget_Address, SI.Cat33.m_FrameNo.nTarget_Address);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 6][FSPEC %d ]Integrity_Accuracy_Parameters         : %d",SI.Cat33.m_FSPEC.MSG.Layout.bIntegrity_Accuracy_Parameters, SI.Cat33.m_FrameNo.nIntegrity_Accuracy_Parameters);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 7][FSPEC %d ]Latitude_Longitude          : %d",SI.Cat33.m_FSPEC.MSG.Layout.bLatitude_Longitude, SI.Cat33.m_FrameNo.nLatitude_Longitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
//
//	// FSPEC #2
//
	sprintf(strTmp,"[FRN 8][FSPEC %d ]Pressure_Altitude         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bPressure_Altitude, SI.Cat33.m_FrameNo.nPressure_Altitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 9][FSPEC %d ]Velocity_Airborne         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bVelocity_Airborne, SI.Cat33.m_FrameNo.nVelocity_Airborne);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 10][FSPEC %d ]Velocity_Surface         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bVelocity_Surface, SI.Cat33.m_FrameNo.nVelocity_Surface);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 11][FSPEC %d ]Mode_3A_Code         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bMode_3A_Code, SI.Cat33.m_FrameNo.nMode_3A_Code);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 12][FSPEC %d ]Target_Identification         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTarget_Identification, SI.Cat33.m_FrameNo.nTarget_Identification);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 13][FSPEC %d ]Emitter_Category         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bEmitter_Category, SI.Cat33.m_FrameNo.nEmitter_Category);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 14][FSPEC %d ]Target_Status         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTarget_Status, SI.Cat33.m_FrameNo.nTarget_Status);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
//
//
//	// FSPEC #3
	sprintf(strTmp,"[FRN 15][FSPEC %d ]Geometric_Altitude         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bGeometric_Altitude, SI.Cat33.m_FrameNo.nGeometric_Altitude);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 16][FSPEC %d ]Modes_Codes         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bModes_Codes, SI.Cat33.m_FrameNo.nModes_Codes);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 17][FSPEC %d ]TCAS_RA_Messages         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTCAS_RA_Messages, SI.Cat33.m_FrameNo.nTCAS_RA_Messages);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 18][FSPEC %d ]Time_of_Message_Reception         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTime_of_Message_Reception, SI.Cat33.m_FrameNo.nTime_of_Message_Reception);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 19][FSPEC %d ]GPS_Antenna_Offset         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bGPS_Antenna_Offset, SI.Cat33.m_FrameNo.nGPS_Antenna_Offset);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 20][FSPEC %d ]Target_State_Data         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTarget_State_Data, SI.Cat33.m_FrameNo.nTarget_State_Data);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 21][FSPEC %d ]ADS_B_Data_Quality_Parameters         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bADS_B_Data_Quality_Parameters, SI.Cat33.m_FrameNo.nADS_B_Data_Quality_Parameters);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
//
//
//
//// FSPEC #4

	sprintf(strTmp,"[FRN 22][FSPEC %d ]Data_Source_Qualifie         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bData_Source_Qualifier, SI.Cat33.m_FrameNo.nData_Source_Qualifie);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 23][FSPEC %d ]Report_Identifier         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bReport_Identifier, SI.Cat33.m_FrameNo.nReport_Identifier);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"[FRN 24][FSPEC %d ]Time_Origination         : %d ",SI.Cat33.m_FSPEC.MSG.Layout.bTime_Origination, SI.Cat33.m_FrameNo.nTime_Origination);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

/*

	sprintf(strTmp,"SendOptionbyUDP         : %d Count [%d]", SI.Cat247.m_nSendOptionbyUDP,SI.Cat247.m_nCountOfSend );
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Cat ID                         : %x : %d", SI.Cat247.m_Cat247.nCat & 0xff, SI.Cat247.m_Cat247.nCat);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	
	sprintf(strTmp,"Length                        : %d", SI.Cat247.m_Cat247.nLength);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"FSPEC                        : %X", SI.Cat247.m_Cat247.FSPEC.ch & 0xff);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Data Source ID SAC   : %d", SI.Cat247.m_Cat247.Data.UAP.cDataSourceIdentifer_SAC); // 1
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Data Source ID SIC    : %d", SI.Cat247.m_Cat247.Data.UAP.cDataSourceIdentifer_SIC); // 2
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Service ID                  : %d", SI.Cat247.m_Cat247.Data.UAP.cServiceIdentification);	// 3
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Time Of Day                : %d %d %d", SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[0], SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[1],SI.Cat247.m_Cat247.Data.UAP.cTimeOfDay[2]);			// 4 ~ 6
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Ver. No Report_REP    : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_REP);	// 7
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Ver. NoReport_CAT     : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_CAT); // 8 
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	sprintf(strTmp,"Main Ver. No                : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_MainVersion); // 9 
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	sprintf(strTmp,"Sub. Ver. No                : %d", SI.Cat247.m_Cat247.Data.UAP.cVersionNumberReport_SubVersion); // 10
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


	sprintf(strTmp,"Buf[ 0 ~ 9 ]                     : %X %X %X %X %X %X %X %X %X %X ",
		SI.Cat247.m_Cat247.Data.buf[0] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[1] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[2] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[3] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[4] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[5] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[6] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[7] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[8] & 0xFF,
		SI.Cat247.m_Cat247.Data.buf[9] & 0xFF);
	Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
*/

}





void 	CCASSGL::PrintGPS_INS_219Data(int x, int y, int nSend)
{
	char		strTmp[256];
	int			nX, nY,nXV, nGap;


	nX = x;
	nY = y;
	nXV = x+ 130;
	nGap = -20;


	if( nSend  == 0 )
	{
		sprintf(strTmp,"Recv GPS_INS_219 (cnt %d)",EnDeCoder.m_CGPS_INS_219.nRecvCnt );
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
		sprintf(strTmp,"(Cnt 55 %d Cnt 5555  %d MsgType %d )", EnDeCoder.m_nRecvCnt55, EnDeCoder.m_nRecvCnt5555,EnDeCoder.m_nRecvCntMsgType);
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
		// 0
		sprintf(strTmp,"Header");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x%x",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.cPacketHeader[0],EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.cPacketHeader[1] );
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"PacketType");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":%x%x",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.cPacketType[0],EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.cPacketType[1] );
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Pay Load");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":%d",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.cPayloadLength);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;



		UINT16	u16;
		float	fValue;
		sprintf(strTmp,"Roll Angle");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usRollAngle);
		//fValue = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 5,	2.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) * R2D;	// dScaleFactor  ;
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fRollAngle = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 5,	2.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] )  * R2D;	// dScaleFactor

		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fRollAngle );
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////
		sprintf(strTmp,"Pitch Angle");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usPitchAngle);
		//sprintf(strTmp,":%d",u16);

		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fPitchAngle = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 7,	2.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) * R2D;	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fPitchAngle );
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////
		sprintf(strTmp,"Yaw Angle");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);

		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usYawAngle);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fYawAngle = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 9,	2.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) * R2D;	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fYawAngle );
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Roll Rate");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usRollRate);
		//sprintf(strTmp,":%d",u16);

		// EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fRollRate = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 11,	7.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fRollRate * R2D);
	

		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Pitch Rate");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usPitchRate);
		//sprintf(strTmp,":%d",u16);

		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fPitchRate = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 13,	7.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fPitchRate * R2D);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Yaw Rate");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usYawRate);
		//sprintf(strTmp,":%d",u16);

		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fYawRate = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 15,	7.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fYawRate * R2D);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		sprintf(strTmp,"Acc X");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usAccX);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccX = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 17,	20.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccX);

		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Acc Y");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usAccY);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccY = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 19,	20.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccY);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Acc Z");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usAccZ);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccZ = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 21,	20.0*PHI/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAccZ);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"VN");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usNorthVelocity);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fNorthVelocity = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 23,	512/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fNorthVelocity);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"VE");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usEastVelocity);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fEastVelocity = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 25,	512/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fEastVelocity);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"VD");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usDownVelocity);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fDownVelocity = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 27,	512/pow(2.0,16.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fDownVelocity);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Longitude");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);

		//double dValue;
		//fValue = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 29,	2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) * R2D;	// dScaleFactor  ;
		//dValue = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 29,	2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor  ;
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLongitude = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 29,	2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) ;	// dScaleFactor
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLongitude =  EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0], 29) * R2D;
	
		sprintf(strTmp,":%.6f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLongitude);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Latitude");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);

		//fValue = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 33,	2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] ) * R2D;	// dScaleFactor  ;
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLatitude = EnDeCoder.LRU_GPSINS_Nav440_CalData (4, 33,	2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLatitude = EnDeCoder.LRU_GPSINS_NAV440_INT32( 2.0*PHI/pow(2.0,32.0), & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0],33) * R2D;	// dScaleFactor

		sprintf(strTmp,":%.6f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fLatitude);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////

		sprintf(strTmp,"Altitude");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		//u16 = EnDeCoder.SwapUINT16(EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usAltitude_GPS);
		//sprintf(strTmp,":%d",u16);
		//EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAltitude_GPS = EnDeCoder.LRU_GPSINS_Nav440_CalData (2, 37,	0.25f, & EnDeCoder.m_CGPS_INS_219.Recv.Value.uc[0] );	// dScaleFactor
		sprintf(strTmp,":%.2f",EnDeCoder.m_CGPS_INS_219.RecvConvertValue.fAltitude_GPS);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
/////////////////////////////////////////////////////////////////////////////////////////////////////


		sprintf(strTmp,"Roll rate Senser");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":%f",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usRollrateSensorTemperature);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"DMI ITOW");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":%d",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.nDMIITOW);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"BIT Status");
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":%d",EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.usBITStatus);
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
			
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS_219.Recv.Value.gpsIns219.CheckSum) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

	}
	else
	{
		sprintf(strTmp,"Send GPS_INS219 (Cnt %d)",EnDeCoder.m_CGPS_INS.nSendCnt);
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"Header") ;								// 0
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %x%x",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Header[0], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Header[1]) ;								// 0
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Yaw") ;		 		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					EnDeCoder. m_CGPS_INS.Send.Value.gpsIns.Yaw) ;		 		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Pitch") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Pitch) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Roll") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Roll) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_P") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_P) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_Q") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_Q) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AngularRate_R") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AngularRate_R) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																		
		sprintf(strTmp,"GPSAltitude") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.GPSAltitude) ;	
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vn(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Vn) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Ve(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",					 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Ve) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"Vd(MPS)") ;				
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Vd) ;				
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"AccX") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccX) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccY") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccY) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;

		sprintf(strTmp,"AccZ") ;			
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",				 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.AccZ) ;			
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"Longitude ") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Longitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"Latitude  : %f") ;		
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %f",			 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.Latitude) ;		
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
																	
		sprintf(strTmp,"TimeY ") ;	
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,":  20%d:%d:%d:%d:%d:%d",	
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[0], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[1],
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[2], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[3],
			EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[4], EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.TimeYMDHMS[5]
			) ;
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;


		sprintf(strTmp,"GPSFixMode") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT); 
		sprintf(strTmp,": %d",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.GPSFixMode) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	
		sprintf(strTmp,"CheckSum") ;					
		Printf( (int) nX, (int) nY ,strTmp,MIDDLE_FONT);
		sprintf(strTmp,": %x",		 EnDeCoder.m_CGPS_INS.Send.Value.gpsIns.CheckSum) ;					
		Printf( (int) nXV, (int) nY ,strTmp,MIDDLE_FONT); nY+=nGap;
	}
}


