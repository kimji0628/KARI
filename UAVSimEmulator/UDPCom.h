// UDPCom.h: interface for the UDPCom class.
//wsock32.lib 
//////////////////////////////////////////////////////////////////////
//#include "UDPCom.h"
//
//CUDPCom* UDPCom = new CUDPCom;
//
//UDPCom->InitUDPServer(5000,0); // UDP receive
//UDPCom->Run(); // UDP receive
//UDPCom->CloseUDP(); // UDP Close
//받은 데이터 처리는  ProcessData 함수 수정
//
//UDPCom->InitUDPClient(5000,"222.222.222.222",0); // UDP send
//  COMM_MESSAGE commMsg;
//
//	commMsg.data.f[0] = 100.0f;
//	commMsg.data.f[1] = 200.0f;
//	commMsg.data.f[2] = 300.0f;
//	commMsg.data.f[3] = 400.0f;
//	commMsg.data.f[4] = 500.0f;
//	commMsg.data.f[5] = 600.0f;
//	UDPCom->SendData((COMM_MESSAGE*)&commMsg,0);
//////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __winsock2_h__
	#include <winsock2.h>
#endif
#pragma comment(lib,"wsock32.lib")

#define MAX_SERVER_UDPSOCK	10
#define MAX_CLIENT_UDPSOCK	10

#define MAX_UDP_DATA_FLOAT	8

#define UDP_SERVER	0
#define UDP_CLIENT	1

typedef struct {
	int		socket_id;
	int		source_port;
	int		port_number;
	char	ip_addr[16];
	int		broadcast;
	struct	sockaddr_in sock_data;
} SIM_SOCKET;



#define COMM_API __declspec(dllexport)

class COMM_API CUDPCom
{
public:
	CUDPCom();
	virtual ~CUDPCom();

	BOOL m_bSendData;
	SIM_SOCKET m_UDPSock_Server[MAX_SERVER_UDPSOCK];
	SIM_SOCKET m_UDPSock_Client[MAX_CLIENT_UDPSOCK];
	BOOL m_bUDP_Server[MAX_SERVER_UDPSOCK];
	BOOL m_bUDP_Client[MAX_CLIENT_UDPSOCK];

	void CloseUDP();
	BOOL IsUDP(int nIndex=0,int nFlag=UDP_SERVER);

	int InitUDPClient(int nPort, char* sIP,int nIndex=0, int nEnableBroadcast=0 );
	int InitUDPAsClient(SIM_SOCKET *udp, int nEnableBroadcast );

	int tcp_client_init(char *ip_addr, int port_no);


// 110526 UDPServer BroadCast 옵션 추가
	//	int InitUDPServer(int nPort, int nIndex=0);
	//	int InitUDPAsServer(SIM_SOCKET *udp);
	int InitUDPServer(int nPort, int nIndex, char bEnableBroadcast);
	int InitUDPAsServer(SIM_SOCKET *udp, char bEnableBroadcast);

//	int SendMsg(const void *packet, int len, int nIndex);
	int SendData(unsigned char *packet, int len, int nIndex);
	int ReceiveData(unsigned char *packet, int len, int nIndex);

};

