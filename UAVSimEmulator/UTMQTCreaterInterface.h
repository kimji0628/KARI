#pragma once
#pragma pack(1)

typedef struct {
	unsigned char c1:1;
	unsigned char c2:1;
	unsigned char c3:1;
	unsigned char c4:1;
	unsigned char c5:1;
	unsigned char c6:1;
	unsigned char c7:1;
	unsigned char c8:1;
} FSPEC_CHAR;


typedef struct {
//   FX 01 = 0xD3
	char  	DataSourceIdentification[2];
	char  	TargetReportDescriptor;
	char	ServiceIdentification;
	char	HighResolutionPositioninWGS84Coordinates[8];
//   FX 02 = 0x11
	char	TargetAddress[3];
//   FX03 = 0x43
	char	GeometricHeight[2];
	char	FlightLevel[2];
//	FX04	0x03
	char	TimeofASTERIXReportTransmission[3];
//	FX05	0xC1
	char	TargetIdentification[6];
	char	EmitterCategory;
//  FX06	0x01
//  FX07	0x02
	char	SpecialPurposeField;
} UTM_QT_CAT21MSG;


typedef struct
{
	char	CatTypyID;
	char	chLengh[2];
	char	FSPEC[7];
	UTM_QT_CAT21MSG	Msg;
} UTM_QTInterface;
















class CUTMQTCreaterInterface
{
public:
	UTM_QTInterface  InterfaceMsg;
public:
	CUTMQTCreaterInterface(void);
	~CUTMQTCreaterInterface(void);
	void	MakeUTMQTMsg();
};
