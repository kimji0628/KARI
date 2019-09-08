// UDPCom.cpp: implementation of the UDPCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPCom::CUDPCom()
{

m_UDPSock_Server[0].port_number = 5000;


}

CUDPCom::~CUDPCom()
{

}
///////////////////////////////////////////////////////////////////////

// 101216 UDPServer BroadCast 옵션 추가
/*
int CUDPCom::InitUDPAsServer(SIM_SOCKET *udp)
{
	WSADATA			wsaData;
	u_long			ulCmdArg = 1;
	SOCKADDR_IN		m_addr;   // address to send to
	char			*ch=NULL;
	char			str[256];

	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
//		sprintf(str,"WSAStartup failed with error %d",WSAGetLastError());
//		AfxMessageBox(str);
		WSACleanup();
		return -1;
	}
	//
	// Copy the resolved information into the sockaddr_in structure
	//
	udp->socket_id = INVALID_SOCKET;  // initialize socket to invalid handle
	// create the socket and prepare it for receiving data
	udp->socket_id = socket(AF_INET, SOCK_DGRAM, 0);

	if (udp->socket_id == INVALID_SOCKET)
	{
//		printf("Socket Create Failed");
		return(0);
	}
	else
	{

		// bind the socket, allowing WinSock to assign the service port
		m_addr.sin_family = AF_INET;                // Internet address family
		m_addr.sin_port = htons(udp->port_number );				
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// any network interface

		if(bind(udp->socket_id, (LPSOCKADDR)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
		{
//			printf("Bind Error");	 
			if (udp->socket_id <0 ) 
			{
//				printf("Client: Error Opening socket: Error %d\n",WSAGetLastError());
				WSACleanup();
				return -1;
			}
			return(0);
		}
		else
		{
			// find out the port number WinSock assigned
			SOCKADDR_IN addr;
			int nAddrLen = sizeof(addr);

			if(getsockname(udp->socket_id, (LPSOCKADDR)&addr, &nAddrLen) == SOCKET_ERROR)
			{
//				printf("getsockname error");
				return(0);
			}
		}
		return(udp->socket_id);
	}
}
*/
int CUDPCom::InitUDPAsServer(SIM_SOCKET *udp, char bEnableBroadcast)
{
	WSADATA			wsaData;
	u_long			ulCmdArg = 1;
	SOCKADDR_IN		m_addr;   // address to send to
	char			*ch=NULL;
	char			str[256];
	
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		//		sprintf(str,"WSAStartup failed with error %d",WSAGetLastError());
		//		AfxMessageBox(str);
		WSACleanup();
		return -1;
	}
	//
	// Copy the resolved information into the sockaddr_in structure
	//
	udp->socket_id = INVALID_SOCKET;  // initialize socket to invalid handle
	// create the socket and prepare it for receiving data
	udp->socket_id = socket(AF_INET, SOCK_DGRAM, 0);

	
	
	if (udp->socket_id == INVALID_SOCKET)
	{
		//		printf("Socket Create Failed");
		return(0);
	}
	else
	{

		setsockopt(udp->socket_id,
			SOL_SOCKET,
			SO_BROADCAST,
			(char *)&bEnableBroadcast,
			sizeof(bEnableBroadcast));

		BOOL reuse = TRUE;
		setsockopt(udp->socket_id,
			SOL_SOCKET,
			SO_REUSEADDR,
			(char *)&reuse, sizeof(int));

		
		// bind the socket, allowing WinSock to assign the service port
		m_addr.sin_family = AF_INET;                // Internet address family
		m_addr.sin_port = htons(udp->port_number );				
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// any network interface
		
		if(bind(udp->socket_id, (LPSOCKADDR)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
		{
			//			printf("Bind Error");	 
			if (udp->socket_id <0 ) 
			{
				//				printf("Client: Error Opening socket: Error %d\n",WSAGetLastError());
				WSACleanup();
				return -1;
			}
			return(0);
		}
		else
		{
			// find out the port number WinSock assigned
			SOCKADDR_IN addr;
			int nAddrLen = sizeof(addr);
			
			if(getsockname(udp->socket_id, (LPSOCKADDR)&addr, &nAddrLen) == SOCKET_ERROR)
			{
				//				printf("getsockname error");
				return(0);
			}
		}
		return(udp->socket_id);
	}
}





BOOL CUDPCom::IsUDP(int nIndex, int nFlag)
{
	if(nFlag == UDP_SERVER)
	{
		return m_bUDP_Server[nIndex];
	}
	else
	{
		return m_bUDP_Client[nIndex];
	}
}



int CUDPCom::InitUDPServer(int nPort, int nIndex, char bEnableBroadcast)
{

	m_UDPSock_Server[nIndex].port_number = nPort;
	
	if(InitUDPAsServer((SIM_SOCKET *)&m_UDPSock_Server[nIndex], bEnableBroadcast))
	{
		m_bUDP_Server[nIndex] = TRUE;
		return 0;
	}
	else
	{
		m_bUDP_Server[nIndex] = FALSE;
		return -1;
	}
}

void CUDPCom::CloseUDP()
{

	int i = 0;
	
	for(i = 0; i < MAX_SERVER_UDPSOCK; i++)
	{
		if(m_bUDP_Server[i] == TRUE)
		{
			closesocket(m_UDPSock_Server[i].socket_id);
		}
	}

	for(i = 0; i < MAX_CLIENT_UDPSOCK; i++)
	{
		if(m_bUDP_Client[i] == TRUE)
		{
			closesocket(m_UDPSock_Client[i].socket_id);
		}
	}
}


//int CUDPCom::SendData(const void *packet, int len, int nIndex)
int CUDPCom::SendData(unsigned char *packet, int len, int nIndex)
{
	int     sockSize;
	int		nSendNo;

 	sockSize = sizeof(struct sockaddr_in);

	if (nSendNo = sendto(m_UDPSock_Client[nIndex].socket_id, (char*)packet, len, 0, (struct sockaddr *) &m_UDPSock_Client[nIndex].sock_data, sockSize) ==ERROR)
	{
		return -1;
	}
	return nSendNo;

}


////////////////////////////////////////////////////////////////////////////////////
