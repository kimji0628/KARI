#include "StdAfx.h"
#include "UTMQTCreaterInterface.h"

CUTMQTCreaterInterface	gUTMQTInterface;


CUTMQTCreaterInterface::CUTMQTCreaterInterface(void)
{
	MakeUTMQTMsg();
}

CUTMQTCreaterInterface::~CUTMQTCreaterInterface(void)
{
}


void	CUTMQTCreaterInterface::MakeUTMQTMsg()
{
	InterfaceMsg.CatTypyID = 0x15;
	InterfaceMsg.chLengh[1] = sizeof(UTM_QTInterface);
	InterfaceMsg.FSPEC[0] = 0xD3;
	InterfaceMsg.FSPEC[1] = 0x11;
	InterfaceMsg.FSPEC[2] = 0x43;
	InterfaceMsg.FSPEC[3] = 0x03;
	InterfaceMsg.FSPEC[4] = 0xC1;
	InterfaceMsg.FSPEC[5] = 0x01;
	InterfaceMsg.FSPEC[6] = 0x02;
/*
//   FX 01 = 0xD3
	InterfaceMsg.Msg.DataSourceIdentification[2];
	InterfaceMsg.Msg.TargetReportDescriptor;
	interfaceMsg.Msg.ServiceIdentification;
	InterfaceMsg.Msg.HighResolutionPositioninWGS84Coordinates[8];
//   FX 02 = 0x11
	InterfaceMsg.Msg.TargetAddress[3];
//   FX03 = 0x43
	InterfaceMsg.Msg.GeometricHeight[2];
	InterfaceMsg.Msg.FlightLevel[2]
//	FX04	0x03
	InterfaceMsg.Msg.TimeofASTERIXReportTransmission[3];
//	FX05	0xC1
	InterfaceMsg.Msg.TargetIdentification[6];
	InterfaceMsg.Msg.EmitterCategory;
//  FX06	0x01
//  FX07	0x02
	InterfaceMsg.Msg.SpecialPurpose Field;
*/
}