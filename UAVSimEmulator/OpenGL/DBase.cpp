#include "stdafx.h"
#include "DBase.h"

#define		TEST_OUTPUT		0

CODENAME	code2name[] =
{
	fltBoundingCenter,			"fltBoundingCenter",			false,
	fltBoundingOrientation,		"fltBoundingOrientation",		false,
	fltBoundingSphere,			"fltBoundingSphere",			false,
	fltBoundingCylinder,		"fltBoundingCylinder",			false,
	fltBoundingHull,			"fltBoundingHull",				false,
	fltBHNext,					"fltBHNext",					false,
	fltBHPnt1,					"fltBHPnt1",					false,
	fltBHPnt2,					"fltBHPnt2",					false,
	fltBHPnt3,					"fltBHPnt3",					false,
	fltBoundingHistogram,		"fltBoundingHistogram",			false,
	fltHistPosts,				"fltHistPosts",					false,
	fltXrefGfxCntx,				"fltXrefGfxCntx",				false,
	fltPolyGfxCntx,				"fltPolyGfxCntx",				false,
	fltTxtGeoCoordData,			"fltTxtGeoCoordData",			false,
	fltTxtGeoCoord,				"fltTxtGeoCoord",				false,
	fltTxtGeoCoordLst,			"fltTxtGeoCoordLst",			false,
	fltTGData,					"fltTGData",					false,
	fltTGNext,					"fltTGNext",					false,
	fltTGCoords,				"fltTGCoords",					false,
	fltImgGeoCoords,			"fltImgGeoCoords",				false,
	fltSound,					"fltSound",						true,
	fltSoundPalette,			"fltSoundPalette",				false,
	fltSndNext,					"fltSndNext",					false,
	fltSndOffset,				"fltSndOffset",					false,
	fltSndNormal,				"fltSndNormal",					false,
	fltPath,					"fltPath",						false,
	fltCoord3f,					"fltCoord3f",					false,
	fltEyePoint,				"fltEyePoint",					false,
	fltEyeRotCenter,			"fltEyeRotCenter",				false,
	fltEyeRotMatrix,			"fltEyeRotMatrix",				false,
	fltEyeLookFrom,				"fltEyeLookFrom",				false,
	fltEyeEyeDir,				"fltEyeEyeDir",					false,
	fltFPoint,					"fltFPoint",					false,
	fltSWIfmt,					"fltSWIfmt",					false,
	fltTerTrans,				"fltTerTrans",					false,
	fltAmbient,					"fltAmbient",					false,
	fltBottomLeftFront,			"fltBottomLeftFront",			false,
	fltBoundingBox,				"fltBoundingBox",				false,
	fltBox,						"fltBox",						false,
	fltBsp,						"fltBsp",						false,
	fltColorRGBA,				"fltColorRGBA",					false,
	fltCylinder,				"fltCylinder",					false,
	fltDPlane,					"fltDPlane",					false,
	fltIDblInfo,				"fltIDblInfo",					false,
	fltIDfadInfo,				"fltIDfadInfo",					false,
	fltVDfadInfo,				"fltVDfadInfo",					false,
	fltDiffuse,					"fltDiffuse",					false,
	fltDof,						"fltDof",						false,
	fltIDownBead,				"fltIDownBead",					false,
	fltEmissive,				"fltEmissive",					false,
	fltFMaterial,				"fltFMaterial",					false,
	fltIFirstInstance,			"fltIFirstInstance",			false,
	fltGfxCntx,					"fltGfxCntx",					false,
	fltGroup,					"fltGroup",						false,
	fltHeader,					"fltHeader",					true,
	fltIMaterial,				"fltIMaterial",					false,
	fltCoord2i,					"fltCoord2i",					false,
	fltIbead,					"fltIbead",						false,
	fltCoord3d,					"fltCoord3d",					false,
	fltImage,					"fltImage",						false,
	fltImgPivot,				"fltImgPivot",					false,
	fltImgUp,					"fltImgUp",						false,
	fltIInsert,					"fltIInsert",					false,
	fltLightSource,				"fltLightSource",				false,
	fltLightSourcePalette,		"fltLightSourcePalette",		false,
	fltILinkInfo,				"fltILinkInfo",					false,
	fltVLinkInfo,				"fltVLinkInfo",					false,
	fltLodCenterPoint,			"fltLodCenterPoint",			false,
	fltLod,						"fltLod",						false,
	fltLtsPosition,				"fltLtsPosition",				false,
	fltLtspAmbient,				"fltLtspAmbient",				false,
	fltLtspDiffuse,				"fltLtspDiffuse",				false,
	fltLtspSpecular,			"fltLtspSpecular",				false,
	fltIMasterBead,				"fltIMasterBead",				false,
	fltMatrix,					"fltMatrix",					false,
	fltIMesh,					"fltIMesh",						false,
	fltINextBead,				"fltINextBead",					false,
	fltVNextBead,				"fltVNextBead",					false,
	fltINextInstance,			"fltINextInstance",				false,
	fltINextSelect,				"fltINextSelect",				false,
	fltVNextSelect,				"fltVNextSelect",				false,
	fltINextSelect2,			"fltINextSelect2",				false,
	fltVNextSelect2,			"fltVNextSelect2",				false,
	fltNormColor,				"fltNormColor",					false,
	fltOSWIfmt,					"fltOSWIfmt",					false,
	fltObject,					"fltObject",					false,
	fltOterTrans,				"fltOterTrans",					false,
	fltPackedColor,				"fltPackedColor",				false,
	fltPolyColor2Rgb,			"fltPolyColor2Rgb",				false,
	fltPolyColorRgb,			"fltPolyColorRgb",				false,
	fltPolygon,					"fltPolygon",					false,
	fltRecDummy,				"fltRecDummy",					false,
	fltIRecInfo,				"fltIRecInfo",					false,
	fltVExtInfo,				"fltVExtInfo",					false,
	fltVRecInfo,				"fltVRecInfo",					false,
	fltRecUndef,				"fltRecUndef",					false,
	fltShareVtxS,				"fltShareVtxS",					false,
	fltISoundPath,				"fltISoundPath",				false,
	fltSpecular,				"fltSpecular",					false,
	fltISplit,					"fltISplit",					false,
	fltStrucrec,				"fltStrucrec",					false,
	fltISubBead,				"fltISubBead",					false,
	fltVSubVertex,				"fltVSubVertex",				false,
	fltISuperBead,				"fltISuperBead",				false,
	fltVSuperVertex,			"fltVSuperVertex",				false,
	fltSwSwitches,				"fltSwSwitches",				false,
	fltSwitch,					"fltSwitch",					false,
	fltTopRightBack,			"fltTopRightBack",				false,
	fltIUpBead,					"fltIUpBead",					false,
	fltVUpBead,					"fltVUpBead",					false,
	fltVNormal,					"fltVNormal",					false,
	fltVertex,					"fltVertex",					false,
	fltVector,					"fltVector",					false,
	fltXformPtr,				"fltXformPtr",					false,
	fltXmDblInfo,				"fltXmDblInfo",					false,
	fltXmGeneral,				"fltXmGeneral",					false,
	fltXmHeader,				"fltXmHeader",					false,
	fltXmLimits,				"fltXmLimits",					false,
	fltXmNext,					"fltXmNext",					false,
	fltXmPut,					"fltXmPut",						false,
	fltXmPutFromAlign,			"fltXmPutFromAlign",			false,
	fltXmPutFromOrigin,			"fltXmPutFromOrigin",			false,
	fltXmPutFromTrack,			"fltXmPutFromTrack",			false,
	fltXmPutToAlign,			"fltXmPutToAlign",				false,
	fltXmPutToOrigin,			"fltXmPutToOrigin",				false,
	fltXmPutToTrack,			"fltXmPutToTrack",				false,
	fltXmRotRefPoint1,			"fltXmRotRefPoint1",			false,
	fltXmRotRefPoint2,			"fltXmRotRefPoint2",			false,
	fltXmScaleRefPoint1,		"fltXmScaleRefPoint1",			false,
	fltXmScaleRefPoint2,		"fltXmScaleRefPoint2",			false,
	fltXmRotate,				"fltXmRotate",					false,
	fltXmRotateAxis,			"fltXmRotateAxis",				false,
	fltXmRotateCenter,			"fltXmRotateCenter",			false,
	fltXmRotateEdge,			"fltXmRotateEdge",				false,
	fltXmScale,					"fltXmScale",					false,
	fltXmScaleCenter,			"fltXmScaleCenter",				false,
	fltXmScalePointCenter,		"fltXmScalePointCenter",		false,
	fltXmScaleToPoint,			"fltXmScaleToPoint",			false,
	fltXmTranslate,				"fltXmTranslate",				false,
	fltXmTranslateDelta,		"fltXmTranslateDelta",			false,
	fltXmTranslateFrom,			"fltXmTranslateFrom",			false,
	fltXref,					"fltXref",						true,
	fltTextText,				"fltTextText",					false,
	fltLpDirection,				"fltLpDirection",				false,
	fltLpModel,					"fltLpModel",					false,
	fltLpAnimationVector,		"fltLpAnimationVector",			false,
	fltLpAttr,					"fltLpAttr",					false,
	fltLpCoordArray,			"fltLpCoordArray",				false,
	fltLpPercentArray,			"fltLpPercentArray",			false,
	fltLpRangeArray,			"fltLpRangeArray",				false,
	fltCurve,					"fltCurve",						false,
	fltText,					"fltText",						false,
	fltLightPoint,				"fltLightPoint",				false,
	fltRoadFirstControlPoint,	"fltRoadFirstControlPoint",		false,
	fltRoadMiddleControlPoint,	"fltRoadMiddleControlPoint",	false,
	fltRoadLastControlPoint,	"fltRoadLastControlPoint",		false,
	fltRoad,					"fltRoad",						false,
	fltRoadAttr,				"fltRoadAttr",					false,
	fltCat,						"fltCat",						false,
	fltClipV0,					"fltClipV0",					false,
	fltClipV1,					"fltClipV1",					false,
	fltClipV2,					"fltClipV2",					false,
	fltClipV3,					"fltClipV3",					false,
	fltClipPlane0,				"fltClipPlane0",				false,
	fltClipPlane1,				"fltClipPlane1",				false,
	fltClipPlane2,				"fltClipPlane2",				false,
	fltClipPlane3,				"fltClipPlane3",				false,
	fltClipPlane4,				"fltClipPlane4",				false,
	fltClip,					"fltClip",						false,
	fltTM3PtOriginUV,			"fltTM3PtOriginUV",				false,
	fltTM3PtAlignUV,			"fltTM3PtAlignUV",				false,
	fltTM3PtShearUV,			"fltTM3PtShearUV",				false,
	fltTM3PtOriginXYZ,			"fltTM3PtOriginXYZ",			false,
	fltTM3PtAlignXYZ,			"fltTM3PtAlignXYZ",				false,
	fltTM3PtShearXYZ,			"fltTM3PtShearXYZ",				false,
	fltTM4PtOriginUV,			"fltTM4PtOriginUV",				false,
	fltTM4PtAlignUV,			"fltTM4PtAlignUV",				false,
	fltTM4PtShearUV,			"fltTM4PtShearUV",				false,
	fltTM4PtPerspectiveUV,		"fltTM4PtPerspectiveUV",		false,
	fltTM4PtOriginXYZ,			"fltTM4PtOriginXYZ",			false,
	fltTM4PtAlignXYZ,			"fltTM4PtAlignXYZ",				false,
	fltTM4PtShearXYZ,			"fltTM4PtShearXYZ",				false,
	fltTM4PtPerspectiveXYZ,		"fltTM4PtPerspectiveXYZ",		false,
	fltTMSphCenter,				"fltTMSphCenter",				false,
	fltTMRadVertex1,			"fltTMRadVertex1",				false,
	fltTMRadVertex2,			"fltTMRadVertex2",				false,
	fltTM3PointPut,				"fltTM3PointPut",				false,
	fltTM4PointPut,				"fltTM4PointPut",				false,
	fltTMSphericalProject,		"fltTMSphericalProject",		false,
	fltTMRadialProject,			"fltTMRadialProject",			false,
	fltMappingData,				"fltMappingData",				false,
	fltTextureMapping,			"fltTextureMapping",			false,
	fltGridOrigin,				"fltGridOrigin",				false,
	fltGridAlign,				"fltGridAlign",					false,
	fltGridTrack,				"fltGridTrack",					false,
	fltGrid,					"fltGrid",						false,
	fltHelperOrigin,			"fltHelperOrigin",				false,
	fltHelperAlign1,			"fltHelperAlign1",				false,
	fltHelperAlign2,			"fltHelperAlign2",				false,
	fltHelper,					"fltHelper",					false,
	fltTorsionVector,			"fltTorsionVector",				false,
	fltTorsion,					"fltTorsion",					false,
	fltSurface,					"fltSurface",					false,
	fltVectord,					"fltVectord",					false,
	fltMeshAttr,				"fltMeshAttr",					false,
	fltMesh,					"fltMesh",						false,
	fltLpAppearancePalette,		"fltLpAppearancePalette",		false,
	fltLpAnimationPalette,		"fltLpAnimationPalette",		false,
	fltLightPointSystem,		"fltLightPointSystem",			false,
	-1,							"UnKnown",						false,
};

int	g_IllegalSiblingCount = 0;

DBase::DBase()
{
	m_dbName[0]			= '\0';
	m_dbFilename[0]		= '\0';

	m_flt				= NULL;
	m_SP				= 0;

	m_currentExtRefNo	= 0;
}

DBase::~DBase()
{
}

int
DBase::LoadDB( char* dbName, char* dbFileName, char* path, char* workingDirectory, AIRPORT* ap )
{
	int		argc	= 0;
	char*	argv[2] = { m_dbName, dbFileName };
	char	pathFilename[256];

	m_SP				= 0;
	m_nofExtRefList		= 0;
	m_apUnderLoading	= ap;

	m_extRefName.InitPathStack( workingDirectory );
	m_extRefName.PushPath( path );

	strcpy( m_dbPath, m_extRefName.CurrentPath() );
	strcpy( m_dbName, dbName );
	strcpy( pathFilename, m_extRefName.MakeFullPathFilename(dbFileName) );

	argv[1]				= pathFilename;

	/* open database */
	if ( ( m_flt = mgOpenDb( argv[1] ) ) == MG_NULL )
	{
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		cLog.Log ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	memset( &m_geoBuff, 0, sizeof(GEO_BUFF) );

	strcpy( m_geoBuff.workingDirectory, workingDirectory );

	m_currentExtRefNo	= m_nofExtRefList++;
	
//	m_geoBuff.first			= true;
	g_IllegalSiblingCount	= 0;

	//	--------------- Count Palette table ----------------
	PrintTexturePalette( m_flt );
	PrintMaterialPalette( m_flt );
	PrintLPAppearancePalette( m_flt, argv[1] );
	PrintLPAnimationPalette( m_flt, argv[1] );

	TraverseDB( m_flt );

	mgCloseDb( m_flt );

	GEO_BUFF*	gp = GeoBuff();

#if	TEST_OUTPUT
	cLog.Log( "----------------------------< Flt Database : %s >-----------------------------\n", dbName  );
	cLog.Log( "%d fltExtRef\nn",	gp->nofExtRefNode );
	cLog.Log( "%d fltGroup\n",		gp->nofGroupNode );
	cLog.Log( "%d fltLOD\n",		gp->nofLODNode );
	cLog.Log( "%d fltDOF\n",		gp->nofDOFNode );
	cLog.Log( "%d fltBSP\n",		gp->nofBSPNode );
	cLog.Log( "%d fltObj\n",		gp->nofObjNode );
	cLog.Log( "%d fltSwitch\n",		gp->nofSwitchNode );
	cLog.Log( "%d fltMesh\n",		gp->nofMesh );
	cLog.Log( "%d fltLightPoint\n",	gp->nofLgtPnt );
	cLog.Log( "%d fltVtxCombo\n",	gp->nofVtxCombo );
	cLog.Log( "%d fltVtxLgt\n",		gp->nofVtxLgt );

	cLog.Log( "%d Material\n",		gp->nofMaterial );
	cLog.Log( "%d Texture\n",		gp->nofTexture );
	cLog.Log( "%d LpAppearList\n",	gp->noflpApprList );
	cLog.Log( "%d LpAnimList\n",	gp->noflpAnimList );
	cLog.Log( "-----------------------------------------------------------------------------\n" );
#endif

	AllocGeoBuff( gp, 10000, 50000 );		// maxTransPoly = 10000, maxTransVtxCombo = 50000

	m_extRefName.InitPathStack( workingDirectory );
	m_extRefName.PushPath( path );

	// open database 
	if ( !(m_flt = mgOpenDb (argv[1]) ) )
	{
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		cLog.Log ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	m_currentExtRefNo	= AddExtRefName( argv[1], m_flt );

//	m_geoBuff.first	= true;

	ReadTexturePalette( m_flt );
	ReadMaterialPalette( m_flt );
	ReadLPApprPalette( m_flt );			// nof lightpoint palette 가 0이어야 됨.
	ReadLPAnimPalette( m_flt );			// nof lightpoint palette 가 0이어야 됨.

	// ------------------- < Push > -------------------
	m_currentFlt	= m_flt;

	m_xFormMVM.LoadIdentity();
	m_rotMVM.LoadIdentity();

	ReadDB( m_flt, 0 );

	// ------------------- < Pop > --------------------

	mgCloseDb( m_flt );

	return true;
}

int
DBase::SaveDB( char* dbName, char* dbFileName, char* workingDirectory )
{
	return true;
}

void
insert_tab(short indent)
{
	for (int i = 0; i < indent; i++)
		cLog.Log ("\t");
}

void
DBase::TraverseDB( mgrec *rec )
{
	// traverse down to the vertex level, going into external references 
	int nodetype;
	static int		num_tabs = 0;
	mgrec*			thisrec = rec;			// child 첫번 sibling을 가리키고 있음
	mgrec*			newDb;					// external ref node
	char			filename[256];
	char			pathFilename[256];

	while (thisrec)
	{
		nodetype = mgGetCode (thisrec);

		PrintNode( thisrec, num_tabs );		// node를 찍은 후 사후 처리를 한다.

		// external ref 경우 자신의 texture/material을 따로 가지고있다. 
		if ( nodetype == eFltXref )
		{
			mgGetAttBuf (thisrec, fltXrefFilename, filename);

			m_extRefName.PushPath( m_extRefName.ExtractPathOnly(filename) );
			strcpy( filename, m_extRefName.ExtractFileNameOnly(filename) );
			strcpy( pathFilename, m_extRefName.MakeFullPathFilename( filename ) );

			newDb = mgOpenDb (pathFilename);

			if ( newDb == NULL )
			{
				cLog.LogExit( "External Ref : %s not found!\n", pathFilename );
			}

			m_currentExtRefNo	= m_nofExtRefList++;

			if ( strcmp( filename, "flight0_0.flt" ) == 0 )
			{
				num_tabs = num_tabs;
			}

			//	--------------- Count Palette table ----------------
			PrintTexturePalette( newDb );
			PrintMaterialPalette( newDb );
			PrintLPAppearancePalette( newDb, pathFilename );
			PrintLPAnimationPalette( newDb, pathFilename );

			TraverseDB (newDb);

			m_extRefName.PopPath();

			mgCloseDb(newDb);
		}
		else
		{
			num_tabs++;

			// children 
			if (mgGetChild (thisrec))
			{
				TraverseDB(mgGetChild (thisrec));
			}
			
			num_tabs--;
		}
		// traverse right 
		thisrec = mgGetNext (thisrec);
	}
}

int
DBase::GetLgtGroupType( char* recName, int& groupID )
{
	if ( m_apUnderLoading == NULL )
		return 0;

	for ( int i = 0; i < m_apUnderLoading->nofReilNode; i++ )
	{
		if ( _stricmp( m_apUnderLoading->reilGroupProp[i].extDefName, recName ) == 0 )
		{
			groupID = i;
			return REIL_LGT;
		}
	}

	for ( i = 0; i < m_apUnderLoading->nofStrobeNode; i++ )
	{
		if ( _stricmp( m_apUnderLoading->strobeGroupProp[i].extDefName, recName ) == 0 )
		{
			groupID = i;
			return STROBE_LGT;
		}
	}

	return 0;
}

void
DBase::ReadDB( mgrec *rec, int parentStatus, NODE* parentNode )
{
	// traverse down to the vertex level, going into external references 
	int				nodetype;
	static int		num_tabs = 0;
	mgrec*			thisrec = rec;			// child 첫번 sibling을 가리키고 있음
	mgrec*			newDb;					// external ref node
	char			filename[256];
	char			pathFilename[256];
	NODE*			thisNode;
	char*			nodeName;
	float			dimension[6];

	int				lgtPntGroupType;
	static int		lgtPntGroupID;
	int				tmpLgtPntGroupID;


// 임시 
	static	int		nTempCnt = 0;
	int			nCnt = 0;
// 임시 끝 
	while ( thisrec )
	{
// 임시 시작 
		nTempCnt++;
		nCnt = nTempCnt;
// 임시 끝 

		if( (nCnt %1000 ) == 0)
		{
			printf("aaa");

		}
		if( (nCnt %100 ) == 0)
		{
			printf("aaa");

		}

		if( (nCnt %10 ) == 0)
		{
			printf("aaa");

		}


		m_xFormMVM.PushMatrix();
		m_rotMVM.PushMatrix();

		nodeName		= mgGetName (thisrec);
		nodetype		= mgGetCode (thisrec);

		if ( nodetype == eFltGroup )
		{
			lgtPntGroupType	= GetLgtGroupType( nodeName, tmpLgtPntGroupID );
		}
		else
		{
			lgtPntGroupType	= 0;
		}

		if ( lgtPntGroupType )
			lgtPntGroupID = tmpLgtPntGroupID;

		thisNode = CompleteNodeField( thisrec, parentNode, lgtPntGroupType | parentStatus, lgtPntGroupID, dimension );	// fltHeader일 때 (thisrec와 thisNode는 ROOT를 가리킨다.)

		mgFree( nodeName );

		// external ref 경우 자신의 texture/material을 따로 가지고있다. 
		if ( nodetype == eFltXref )
		{
			m_extRefList[m_nofExtRefList].dbRec		= thisrec;
			mgGetAttBuf (thisrec, fltXrefFilename, filename);

			m_extRefName.PushPath( m_extRefName.ExtractPathOnly(filename) );
			strcpy( filename, m_extRefName.ExtractFileNameOnly(filename) );
			strcpy( pathFilename, m_extRefName.MakeFullPathFilename( filename ) );

			newDb = mgOpenDb (pathFilename);

			if ( newDb == NULL )
			{
				cLog.LogExit( "External Ref : %s not found!\n", filename );
			}

			// ------------------- < Push > -------------------
			PushFltStack( m_currentFlt, m_currentExtRefNo, pathFilename, filename );

			m_currentExtRefNo = AddExtRefName( filename, newDb );
			
			ReadTexturePalette( newDb );
			ReadMaterialPalette( newDb );
			ReadLPApprPalette( newDb );
			ReadLPAnimPalette( newDb );

			m_currentFlt	= newDb;
			ReadDB ( newDb, lgtPntGroupType | parentStatus, thisNode );									// newDb는 child이고 thisNode는 상대적 fltXref로 parent이다
			PopFltStack( &m_currentFlt, m_currentExtRefNo, pathFilename, filename );
			// ------------------- < Pop >- -------------------

			m_extRefName.PopPath();

			mgCloseDb(newDb);
		}
		// extRef가 아닌 대부분의 경우 여기로 들어온다.
		else
		{		
			num_tabs++;

			// children 
			if (mgGetChild (thisrec))
			{
				ReadDB( mgGetChild (thisrec), lgtPntGroupType | parentStatus, thisNode );				// thisrec는 sibling 중 하나이고 이것의 child와 
			}

			num_tabs--;
		}

		if ( parentNode )
		{
			if ( parentNode->type == NODE_IS_LGTPNT || parentNode->type == NODE_IS_MESH )
			{
				if ( parentNode->bv[3] == 0.0 )
				{
					parentNode->xmin	= dimension[0];
					parentNode->xmax	= dimension[1];
					parentNode->ymin	= dimension[2];
					parentNode->ymax	= dimension[3];
					parentNode->zmin	= dimension[4];
					parentNode->zmax	= dimension[5];

					parentNode->bv[3]	= 1.0;				// 값이 있다는 표시
				}
				else
				{
					if ( parentNode->xmin > dimension[0] )		parentNode->xmin = dimension[0];
					if ( parentNode->xmax < dimension[1] )		parentNode->xmax = dimension[1];
					if ( parentNode->ymin > dimension[2] )		parentNode->ymin = dimension[2];
					if ( parentNode->ymax < dimension[3] )		parentNode->ymax = dimension[3];
					if ( parentNode->zmin > dimension[4] )		parentNode->zmin = dimension[4];
					if ( parentNode->zmax < dimension[5] )		parentNode->zmax = dimension[5];
				}
			}
			else
			{
				if ( parentNode->bv[3] == 0.0 )
				{
					parentNode->xmin	= thisNode->xmin;
					parentNode->xmax	= thisNode->xmax;
					parentNode->ymin	= thisNode->ymin;
					parentNode->ymax	= thisNode->ymax;
					parentNode->zmin	= thisNode->zmin;
					parentNode->zmax	= thisNode->zmax;

					parentNode->bv[3]	= 1.0;				// 값이 있다는 표시
				}
				else
				{
					if ( parentNode->xmin > thisNode->xmin )		parentNode->xmin = thisNode->xmin;
					if ( parentNode->xmax < thisNode->xmax )		parentNode->xmax = thisNode->xmax;
					if ( parentNode->ymin > thisNode->ymin )		parentNode->ymin = thisNode->ymin;
					if ( parentNode->ymax < thisNode->ymax )		parentNode->ymax = thisNode->ymax;
					if ( parentNode->zmin > thisNode->zmin )		parentNode->zmin = thisNode->zmin;
					if ( parentNode->zmax < thisNode->zmax )		parentNode->zmax = thisNode->zmax;
				}
			}
		}

		thisrec = mgGetNext (thisrec);								// traverse right 

		m_xFormMVM.PopMatrix();
		m_rotMVM.PopMatrix();
	}

	if ( parentNode )
	{
		parentNode->bv[0] = ( parentNode->xmin + parentNode->xmax ) / 2.0f;
		parentNode->bv[1] = ( parentNode->ymin + parentNode->ymax ) / 2.0f;
		parentNode->bv[2] = ( parentNode->zmin + parentNode->zmax ) / 2.0f;

		double dx, dy, dz;

		dx	= ( parentNode->xmax - parentNode->xmin ) / 2.0;
		dy	= ( parentNode->ymax - parentNode->ymin ) / 2.0;
		dz	= ( parentNode->zmax - parentNode->zmin ) / 2.0;

		parentNode->bv[3]	= (float)sqrt( dx*dx + dy*dy + dz*dz );
	}
}

// ================================== < Materials Of fltData > =================================
int
DBase::PrintMaterialPalette (mgrec *db)
{
	mgrec *mat;
	int index;	//, matcount;

	if (mat = mgGetFirstMaterial (db, &index ))
	{
		m_geoBuff.nofMaterial++;

		while (mat = mgGetNextMaterial (mat, &index))
		{
			m_geoBuff.nofMaterial++;
		}
		return MG_TRUE;
	}
	return MG_FALSE;
}

// ================================== < Textures Of fltData > =================================
int
DBase::PrintTexturePalette (mgrec *db)
{
	int		patindex;	//, texcount;
	int		width, height, type;
	char	patname[1024];
	mgrec*	attr_rec;

	if (mgGetFirstTexture (db, &patindex, patname))
	{
		do
		{
			if (attr_rec = mgGetTextureAttributes (db, patindex))
			{
				mgGetAttList (attr_rec, fltImgWidth, &width,
										fltImgHeight, &height,
										fltImgType, &type,
										MG_NULL);
			
				m_geoBuff.nofTexture++;
			}
			else
			{
				cLog.LogExit("Texture %d: %s: Error: cannot get attributes\n",
						  patindex, patname);
			}
		} while ( mgGetNextTexture (db, &patindex, patname) );

		return MG_TRUE;
	}
	return MG_FALSE;
}

// ================================== < Each Code within fltTree > =================================
void
DBase::PrintNode( mgrec* thisnode, int num_tabs )
{
	char*		nodeName;
	int			noChild = mgCountChild (thisnode);
	int			codeIdx;
	short		repCnt;

	if ( mgIsCode (thisnode, fltHeader)) 
	{
		m_geoBuff.nofHeaderNode++;
	}
	else if ( mgIsCode (thisnode, fltXref)) 
	{
		m_geoBuff.nofExtRefNode++;
	}
	else if ( mgIsCode (thisnode, fltGroup)) 
	{
		m_geoBuff.nofGroupNode++;
	}
	else if ( mgIsCode (thisnode, fltLod)) 
	{
		m_geoBuff.nofLODNode++;
	}
	else if ( mgIsCode (thisnode, fltBsp)) 
	{
		m_geoBuff.nofBSPNode++;
	}
	else if ( mgIsCode (thisnode, fltDof)) 
	{
		m_geoBuff.nofDOFNode++;
	}
	else if ( mgIsCode (thisnode, fltSwitch)) 
	{
		m_geoBuff.nofSwitchNode++;
	}
	else if ( mgIsCode (thisnode, fltObject))
	{
		m_geoBuff.nofObjNode++;
	}
	else if ( mgIsCode (thisnode, fltPolygon)) 
	{
		m_geoBuff.nofMesh++;
	}
	else if ( mgIsCode (thisnode, fltMesh)) 
	{
		m_geoBuff.nofMesh++;
	}
	else if ( mgIsCode (thisnode, fltLightPoint)) 
	{
		m_geoBuff.nofLgtPnt++;
	}
	else if ( mgIsCode (thisnode, fltVertex)) 
	{
		if ( mgIsCode (mgGetParent( thisnode ), fltLightPoint) )
		{
			mgGetAttList (mgGetParent( thisnode ), fltRepCnt, &repCnt, MG_NULL);

			if ( repCnt )
				m_geoBuff.nofVtxLgt += (repCnt+1);
			else
				m_geoBuff.nofVtxLgt++;
		}
		else
		{
			m_geoBuff.nofVtxCombo++;
		}
	}
	else
	{
		codeIdx		= Code2Idx(thisnode);
		nodeName	= mgGetName (thisnode);
		insert_tab( num_tabs );
		cLog.Log("%s[x%d]: %s\n", code2name[codeIdx].codeName, noChild, nodeName );
		mgFree(nodeName);

		if ( !code2name[codeIdx].codeKnown )
		{
			cLog.LogExit( "Not implemented yet!!!!!!!!\n" );
		}
	}
}

// ================================== < Print Each Codes in fltData > =================================
int
DBase::Code2Idx( mgrec* thisnode )
{
	int		i = 0;

	while ( code2name[i].codeVal != -1 )
	{
		if ( mgIsCode(thisnode, code2name[i].codeVal) )
			break;

		i++;
	}

	return i;
}

// ---------------------------------------------------------------
//	Input: nodeType
//
//		nodeType별로 방을 확보한후 entry주소를 반환한다.
//
//		NODE_HEADER*	m_headerNode;
//	
//		int				m_nofGroupNode;
//		NODE_GROUP*		m_groupNode;
//	
//		int				m_nofLODNode;
//		NODE_LOD*		m_lodNode;
//		
//		int				m_nofDOFNode;
//		NODE_DOF*		m_dofNode;
//	
//		int				m_nofBSPNode;
//		NODE_BSP*		m_bspNode;
//		
//		int				m_nofObjNode;
//		NODE_OBJ*		m_objNode;
//	
//		int				m_nofSwitchNode;
//		NODE_OBJ*		m_switchNode;
//	
//		int				m_nofMesh;
//		MESH*			m_mesh;
//	
//		int				m_nofLgtPnt;
//		LGTPNT*			m_lgtPnt;
//	
//		int				m_nofVtxCombo;
//		VTXCOMBO*		m_vtxCombo;
// ---------------------------------------------------------------
void*
DBase::CreateNode( int nodeType )
{
	void*	retPtr;

	switch( nodeType )
	{
	case NODE_IS_HEADER:
		retPtr	= m_geoBuff.headerNode		+ m_geoBuff.nofHeaderNode++;
		break;
	case NODE_IS_EXTREF:
		retPtr	= m_geoBuff.extRefNode		+ m_geoBuff.nofExtRefNode++;
		break;
	case NODE_IS_GROUP:
		retPtr	= m_geoBuff.groupNode		+ m_geoBuff.nofGroupNode++;
		break;
	case NODE_IS_LOD:
		retPtr	= m_geoBuff.lodNode			+ m_geoBuff.nofLODNode++;
		break;
	case NODE_IS_DOF:
		retPtr	= m_geoBuff.dofNode			+ m_geoBuff.nofDOFNode++;
		break;
	case NODE_IS_BSP:
		retPtr	= m_geoBuff.bspNode			+ m_geoBuff.nofBSPNode++;
		break;
	case NODE_IS_OBJ:
		retPtr	= m_geoBuff.objNode			+ m_geoBuff.nofObjNode++;
		break;
	case NODE_IS_SWITCH:
		retPtr	= m_geoBuff.switchNode		+ m_geoBuff.nofSwitchNode++;
		break;
	default:
		retPtr	= NULL;
		break;
	}

	return retPtr;
}

MESH*
DBase::AddMesh()
{
	return m_geoBuff.mesh + m_geoBuff.nofMesh++;
}

LGTPNT*
DBase::AddLgtPnt()
{
	return	m_geoBuff.lgtPnt + m_geoBuff.nofLgtPnt++;
}

VTXCOMBO*
DBase::AddVertex( MESH* mp )
{
	if ( !mp->nofVtx )
		mp->vtxLink	= m_geoBuff.vtxCombo + m_geoBuff.nofVtxCombo;

	mp->nofVtx++;

	return m_geoBuff.vtxCombo + m_geoBuff.nofVtxCombo++;
}

VTXLGT*
DBase::AddVertexLgt( LGTPNT* lp )
{
	if ( !lp->nofVtx )
		lp->vtxLink	= m_geoBuff.vtxLgt + m_geoBuff.nofVtxLgt;

	lp->nofVtx++;

	return m_geoBuff.vtxLgt + m_geoBuff.nofVtxLgt++;
}

/*
	MXLL_TRANSLATE	= 'T', // @emem a translation matrix
	MXLL_SCALE		= 'S', // @emem a scale matrix
	MXLL_ROTEDGE	= 'E', // @emem a rotation about an edge
	MXLL_ROTPT		= 'R', // @emem a rotation about a point
	MXLL_PUT			= 'P', // @emem a simultaneous translation, rotation and scale matrix
	MXLL_TOPOINT	= 'p', // @emem a simultaneous scale and rotation matrix
	MXLL_GENERAL	= 'M'  // @emem a matrix of one or more undefined transformations
*/
void
DBase::ReadXforms(mgrec *node, NODE* thisNode, char* nodeName )
{
	int		xtype, maxlimit;
	mgrec*	xrec;

	if (mgHasXform (node))
	{
		xrec = mgGetXform (node);

		thisNode->nofXform = 0;

		while ( xrec )
		{
			xtype = mgGetXformType (xrec);
			mgGetAttList (xrec, fltXmLimitMax, &maxlimit, mgNULL);

			switch (xtype)
			{
				case MXLL_TRANSLATE:
				{
					double	x, y, z;

					thisNode->xformType[thisNode->nofXform++] = NODE_XLATED;

					mgGetCoord3d (xrec, fltXmTranslateDelta, &x, &y, &z);
					thisNode->xlat[0]	= x;
					thisNode->xlat[1]	= y;
					thisNode->xlat[2]	= z;

					thisNode->status	|= NODE_XFORMED;

					m_xFormMVM.Translated( x, y, z );

//					for ( int i = 0; i < thisNode->depth; i++ )
//						cLog.Log( "\t" );
//					cLog.Log( "Node %s xlat: %.2f, %.2f, %.2f\n", nodeName, x, y, z );
					break;
				}
				case MXLL_ROTPT:
				{
					float angle;
					double x, y, z;
					float i, j, k;

					thisNode->xformType[thisNode->nofXform++] = NODE_ROTATED;

					mgGetCoord3d (xrec, fltXmRotateCenter, &x, &y, &z);

					thisNode->rotCenter[0]	= x;
					thisNode->rotCenter[1]	= y;
					thisNode->rotCenter[2]	= z;

//					mgGetVector ( xrec, fltEyeEyeDir, &i, &j, &k );
					mgGetVector ( xrec, fltXmRotateAxis, &i, &j, &k );
/*					mgGetAttList (xrec,
									fltVectorI, &i,
									fltVectorJ, &j,
									fltVectorK, &k,
									mgNULL);
*/

					mgGetAttList (xrec, 
									fltXmRotateAngle, &angle,
									mgNULL);

					thisNode->rot[0]	= angle;
					thisNode->rot[1]	= i;
					thisNode->rot[2]	= j;
					thisNode->rot[3]	= k;

					thisNode->status	|= NODE_XFORMED;

					m_xFormMVM.Translated( x, y, z );
					m_xFormMVM.RotAxisd( angle, i, j, k );
					m_xFormMVM.Translated( -x, -y, -z );

					m_rotMVM.RotAxisd( angle, i, j, k );

//					for ( int n = 0; n < thisNode->depth; n++ )
//						cLog.Log( "\t" );
//					cLog.Log( "Node %s rot: %.2f, %.2f, %.2f, %.2f\n", nodeName, angle, i, j, k );
					break;
				}
				case MXLL_SCALE:
				{
					float	sx, sy, sz;
					double	x,	y,	z;

					thisNode->xformType[thisNode->nofXform++] = NODE_SCALED;

					mgGetCoord3d (xrec, fltXmScaleCenter, &x, &y, &z);

					mgGetAttList (xrec,
									fltXmScaleX, &sx,
									fltXmScaleY, &sy,
									fltXmScaleZ, &sz,
									mgNULL);

					thisNode->scale[0]	= sx;
					thisNode->scale[1]	= sy;
					thisNode->scale[2]	= sz;

					thisNode->scaleCenter[0]	= x;
					thisNode->scaleCenter[1]	= y;
					thisNode->scaleCenter[2]	= z;

					thisNode->status	|= NODE_XFORMED;

					m_xFormMVM.Translated( x, y, z );
					m_xFormMVM.Scaled( sx, sy, sz );
					m_xFormMVM.Translated( -x, -y, -z );
					break;
				}
			}

			xrec = mgGetNext( xrec );
		}
	}
}

NODE*
DBase::CompleteNodeField( mgrec* thisnode, NODE* parentNode, int thisIsLgtPntGroup, int lgtGroupID, float* dimension )
{
	char*		nodeName	= NULL;
	char*		fileName	= NULL;
	int			noChild = mgCountChild (thisnode);
	int			codeIdx;
	int			myType = -1;

	NODE*					np;
	static NODE_HEADER*		nhp;
	static NODE_EXTREF*		nxp;
	static NODE_GROUP*		ngp;
	static NODE_LOD*		nlp;
	static NODE_DOF*		ndp;
	static NODE_BSP*		nbp;
	static NODE_SWITCH*		nsp;
	static NODE_OBJ*		nop;
	static MESH*			meshPtr;
	static LGTPNT*			lgtpntPtr;	

	// LOD
	double					lodSwIn, lodSwOut;

	// DOF
	double					dofCurX;
	double					dofCurY;
	double					dofCurZ;
	double					dofPutAnchorX;
	double					dofPutAnchorY;
	double					dofPutAnchorZ;
	double					dofPutAlignX;
	double					dofPutAlignY;
	double					dofPutAlignZ;
	double					dofPutTrackX;
	double					dofPutTrackY;
	double					dofPutTrackZ;

	bool					dofLimitX;
	bool					dofLimitY;
	bool					dofLimitZ;
	bool					dofLimitXRot;
	bool					dofLimitYRot;
	bool					dofLimitZRot;

	double					dofIncX;
	double					dofIncY;
	double					dofIncZ;
	double					dofIncXRot;
	double					dofIncYRot;
	double					dofIncZRot;
	
	double					dofMinX, dofMaxX;
	double					dofMinY, dofMaxY;
	double					dofMinZ, dofMaxZ;
	double					dofMinXRot, dofMaxXRot;
	double					dofMinYRot, dofMaxYRot;
	double					dofMinZRot, dofMaxZRot;

	double					v_0[3];
	double					v_1[3];
	double					v_2[3];
	double					dofXlatNorm[3];
	double					dofRotNorm[3];

	// BSP
	double					pa, pb, pc, pd;

	// OBJ
	int						hideOnDay, hideOnDusk, hideOnDark, flatShaded;

	// POLYGON
	short					tindex = -1, tmindex = -1, matindex = -1;
	short					tindex1;

	// VERTEX
	VTXCOMBO*				vc;
	VTXLGT*					vl;
	double					x, y, z;
	double					xx, yy, zz;
	double					cx, cy, cz;
	float					nx, ny, nz;
	float					u, v;						// base texture coord
	float					u1, v1;						// multitexture coord
	short					r, g, b, a;
	double					xyz[3];

	LGTPNT*					LGTPNT_PTR;
	MESH*					MESH_PTR;

	int						first;
	float					xmin, xmax, ymin, ymax, zmin, zmax;
	double					len;

	nodeName	= mgGetName (thisnode);

	codeIdx		= Code2Idx(thisnode);

	if ( mgIsCode (thisnode, fltHeader) )
	{
		np	= (NODE*)CreateNode( NODE_IS_HEADER );
		nhp	= (NODE_HEADER*)np;

		memset( nhp, 0, sizeof(NODE_HEADER) );
		ReadXforms( thisnode, np, nodeName );

		myType	= NODE_IS_HEADER;
	}
	else if ( mgIsCode (thisnode, fltXref)) 
	{
		np	= (NODE*)CreateNode( NODE_IS_EXTREF );
		nxp	= (NODE_EXTREF*)np;

		memset( nxp, 0, sizeof(NODE_EXTREF) );
		ReadXforms( thisnode, np, nodeName );

		myType	= NODE_IS_EXTREF;
	}
	else if ( mgIsCode (thisnode, fltGroup)) 
	{
		np	= (NODE*)CreateNode( NODE_IS_GROUP );
		ngp	= (NODE_GROUP*)np;

		memset( ngp, 0, sizeof(NODE_GROUP) );
		ReadXforms( thisnode, np, nodeName );

		myType	= NODE_IS_GROUP;
	}
	else if ( mgIsCode (thisnode, fltLod)) 
	{
		mgGetAttList( thisnode, fltLodSwitchIn, &lodSwIn,
							fltLodSwitchOut, &lodSwOut, MG_NULL);

		mgGetCoord3d( thisnode, fltLodCenterPoint, &cx, &cy, &cz );

		np			= (NODE*)CreateNode( NODE_IS_LOD );
		nlp			= (NODE_LOD*)np;

		memset( nlp, 0, sizeof(NODE_LOD) );
		ReadXforms( thisnode, np, nodeName );

		m_xFormMVM.PassMVMf( (float)cx, (float)cy, (float)cz, &nlp->cx );

		nlp->swIn	= (float)lodSwIn;
		nlp->swOut	= (float)lodSwOut;
		myType	= NODE_IS_LOD;
	}
	else if ( mgIsCode (thisnode, fltDof)) 
	{
		mgGetAttList( thisnode, 
						fltDofCurX,			&dofCurX,
						fltDofCurY,			&dofCurY,
						fltDofCurZ,			&dofCurZ,

						fltDofPutAnchorX,	&dofPutAnchorX,
						fltDofPutAnchorY,	&dofPutAnchorY,
						fltDofPutAnchorZ,	&dofPutAnchorZ,

						fltDofPutAlignX,	&dofPutAlignX,
						fltDofPutAlignY,	&dofPutAlignY,
						fltDofPutAlignZ,	&dofPutAlignZ,

						fltDofPutTrackX,	&dofPutTrackX,
						fltDofPutTrackY,	&dofPutTrackY,
						fltDofPutTrackZ,	&dofPutTrackZ,

						fltDofLimitX,		&dofLimitX,
						fltDofLimitY,		&dofLimitY,
						fltDofLimitZ,		&dofLimitZ,

						fltDofLimitXRot,	&dofLimitXRot,
						fltDofLimitYRot,	&dofLimitYRot,
						fltDofLimitZRot,	&dofLimitZRot,

						fltDofIncX,			&dofIncX,
						fltDofIncX,			&dofIncY,
						fltDofIncX,			&dofIncZ,

						fltDofIncXRot,		&dofIncXRot,
						fltDofIncYRot,		&dofIncYRot,
						fltDofIncZRot,		&dofIncZRot,

						fltDofMinX,			&dofMinX,
						fltDofMaxX,			&dofMaxX,
						fltDofMinX,			&dofMinX,
						fltDofMaxX,			&dofMaxX,
						fltDofMinX,			&dofMinX,
						fltDofMaxX,			&dofMaxX,

						fltDofMinXRot,		&dofMinXRot,
						fltDofMaxXRot,		&dofMaxXRot,
						fltDofMinYRot,		&dofMinYRot,
						fltDofMaxYRot,		&dofMaxYRot,
						fltDofMinZRot,		&dofMinZRot,
						fltDofMaxZRot,		&dofMaxZRot,

						MG_NULL );

		np			= (NODE*)CreateNode( NODE_IS_DOF );
		ndp			= (NODE_DOF*)np;

		memset( ndp, 0, sizeof(NODE_DOF) );
		ReadXforms( thisnode, np, nodeName );

		ndp->dofXlat[0]		= dofCurX;
		ndp->dofXlat[1]		= dofCurY;
		ndp->dofXlat[2]		= dofCurZ;

		ndp->dofRotCenter[0]	= dofPutAnchorX;
		ndp->dofRotCenter[1]	= dofPutAnchorY;
		ndp->dofRotCenter[2]	= dofPutAnchorZ;

		v_0[0]				= 0.0;
		v_0[1]				= 0.0;
		v_0[2]				= 0.0;

		v_1[0]				= dofPutAlignX - dofPutAnchorX;
		v_1[1]				= dofPutAlignY - dofPutAnchorY;
		v_1[2]				= dofPutAlignZ - dofPutAnchorZ;

		v_2[0]				= dofPutTrackX - dofPutAnchorX;
		v_2[1]				= dofPutTrackY - dofPutAnchorY;
		v_2[2]				= dofPutTrackZ - dofPutAnchorZ;

		if ( dofLimitX || dofLimitY || dofLimitZRot )
		{
			if ( dofLimitX )
			{
				len				= sqrt( v_1[0]*v_1[0] + v_1[1]*v_1[1] + v_1[2]*v_1[2] );
				dofXlatNorm[0]	= v_1[0] / len;
				dofXlatNorm[1]	= v_1[1] / len;
				dofXlatNorm[2]	= v_1[2] / len;

				ndp->dofMinXlat	= dofMinX;
				ndp->dofMaxXlat	= dofMaxX;
				ndp->dofXlatInc	= dofMaxX - dofMinX;
			}
			else if ( dofLimitY )
			{
				len				= sqrt( v_1[0]*v_1[0] + v_1[1]*v_1[1] + v_1[2]*v_1[2] );
				dofXlatNorm[0]	= v_2[0] / len;
				dofXlatNorm[1]	= v_2[1] / len;
				dofXlatNorm[2]	= v_2[2] / len;

				ndp->dofMinXlat	= dofMinY;
				ndp->dofMaxXlat	= dofMaxY;
				ndp->dofXlatInc	= dofMaxY - dofMinY;
			}
			else
			{
				CalcConvexNormal( v_0, v_1, v_2, dofXlatNorm );

				ndp->dofMinXlat	= dofMinZ;
				ndp->dofMaxXlat	= dofMaxZ;
				ndp->dofXlatInc	= dofMaxZ - dofMinZ;
			}

			ndp->dofXlatNorm[0]		= dofXlatNorm[0];
			ndp->dofXlatNorm[1]		= dofXlatNorm[1];
			ndp->dofXlatNorm[2]		= dofXlatNorm[2];

			ndp->xlatOn	= true;
		}
		else
			ndp->xlatOn	= false;

		if ( dofLimitXRot || dofLimitYRot || dofLimitZRot )
		{
			if ( dofLimitZRot )
			{
				CalcConvexNormal( v_0, v_1, v_2, dofRotNorm );

				ndp->dofMinRot	= dofMinZRot;
				ndp->dofMaxRot	= dofMaxZRot;
				ndp->dofRotInc	= dofMaxZRot - dofMinZRot;
			}
			else if ( dofLimitXRot )
			{
				len				= sqrt( v_1[0]*v_1[0] + v_1[1]*v_1[1] + v_1[2]*v_1[2] );
				dofRotNorm[0]	= v_1[0] / len;
				dofRotNorm[1]	= v_1[1] / len;
				dofRotNorm[2]	= v_1[2] / len;

				ndp->dofMinRot	= dofMinXRot;
				ndp->dofMaxRot	= dofMaxXRot;
				ndp->dofRotInc	= dofMaxXRot - dofMinXRot;
			}
			else if ( dofLimitYRot )
			{
				len				= sqrt( v_1[0]*v_1[0] + v_1[1]*v_1[1] + v_1[2]*v_1[2] );
				dofRotNorm[0]	= v_2[0] / len;
				dofRotNorm[1]	= v_2[1] / len;
				dofRotNorm[2]	= v_2[2] / len;

				ndp->dofMinRot	= dofMinYRot;
				ndp->dofMaxRot	= dofMaxYRot;
				ndp->dofRotInc	= dofMaxYRot - dofMinYRot;
			}

			ndp->dofRotNorm[0]		= dofRotNorm[0];
			ndp->dofRotNorm[1]		= dofRotNorm[1];
			ndp->dofRotNorm[2]		= dofRotNorm[2];

			ndp->rotOn	= true;
		}
		else
		{
			ndp->rotOn	= false;
		}

		myType	= NODE_IS_DOF;
	}
	else if ( mgIsCode (thisnode, fltBsp)) 
	{
		mgGetPlane( thisnode, fltDPlane, &pa, &pb, &pc, &pd );

		np			= (NODE*)CreateNode( NODE_IS_BSP );
		nbp			= (NODE_BSP*)np;

		memset( nbp, 0, sizeof(NODE_BSP) );
		ReadXforms( thisnode, np, nodeName );

		nbp->a		= pa;
		nbp->b		= pb;
		nbp->c		= pc;
		nbp->d		= pd;
		myType	= NODE_IS_BSP;

	}
	else if ( mgIsCode (thisnode, fltSwitch)) 
	{
		int		swCurMask;
		int		swMaxMask;
		int		swCount;

		mgGetAttList( thisnode,
						fltSwCurMask,		&swCurMask,
						fltSwMaxMask,		&swMaxMask,
						fltSwCount,			&swCount,
						MG_NULL);

		np			= (NODE*)CreateNode( NODE_IS_SWITCH );
		nsp			= (NODE_SWITCH*)np;

		memset( nsp, 0, sizeof(NODE_SWITCH) );

		nsp->maxMask		= swMaxMask;
		nsp->currentMask	= swCurMask;

		ReadXforms( thisnode, np, nodeName );
		myType		= NODE_IS_SWITCH;
	}
	else if ( mgIsCode (thisnode, fltObject))
	{
		mgGetAttList (thisnode, fltObjNoDay,	&hideOnDay,
							fltObjNoDusk,	&hideOnDusk,
							fltObjNoNight,	&hideOnDark,
							fltObjNoShade,	&flatShaded,
							MG_NULL);
		
		np				= (NODE*)CreateNode( NODE_IS_OBJ );
		nop				= (NODE_OBJ*)np;

		memset( nop, 0, sizeof(NODE_OBJ) );
		ReadXforms( thisnode, np, nodeName );

		if ( hideOnDay )
			nop->todSW |= TOD_HIDE_ON_DAY;
		if ( hideOnDusk )
			nop->todSW |= TOD_HIDE_ON_DUSK;
		if ( hideOnDark )
			nop->todSW |= TOD_HIDE_ON_DARK;
		myType	= NODE_IS_OBJ;

	}
	else if ( mgIsCode (thisnode, fltPolygon) || mgIsCode (thisnode, fltMesh) )
	{
		TEXLIST*	tp;
		meshPtr		= AddMesh();

		m_xFormMVM.GetMatrix( (double*)meshPtr->xformMVM );

		MESH_PTR	= meshPtr;

		memset( meshPtr, 0, sizeof(MESH) );

		mgGetAttList( thisnode,
						fltPolyTexture,			&tindex,
						fltLayerTexture1,		&tindex1,
						fltPolyTexmap,			&tmindex,
						fltPolyMaterial,		&matindex,
						MG_NULL);

		tp	= TexList( meshPtr->extRefID, tindex );

		meshPtr->texNo			= tindex;
		meshPtr->texNo1			= tindex1;
		meshPtr->matNo			= matindex;

		if ( tindex > -1 )
		{
			meshPtr->renderFlag	|= PROP_TEXTURED;
		}

		if ( tindex1 > -1 )
		{
			meshPtr->renderFlag	|= PROP_MULTI_TEXTURED;
		}

		if ( matindex > -1 )
		{
			meshPtr->renderFlag	|= PROP_LIGHTED;
		}

		if ( mgGetPolyColorRGB(thisnode, &r, &g, &b ) == MG_TRUE )
		{
			meshPtr->primeColor[0]	= (BYTE)r;
			meshPtr->primeColor[1]	= (BYTE)g;
			meshPtr->primeColor[2]	= (BYTE)b;
		}
		else
		{
			meshPtr->renderFlag	|= PROP_LIGHTED;
		}
	
		mgGetVtxNormal(thisnode,&nx,&ny,&nz);

		if ( mgIsCode (thisnode, fltPolygon) )
			meshPtr->type		= POLY_IS_POLY;
		else
			meshPtr->type		= POLY_IS_TRI_MESH;

		meshPtr->extRefID	= m_currentExtRefNo;
		meshPtr->next		= NULL;
		meshPtr->nofVtx		= 0;

		meshPtr->faceNorm[0]	= nx;
		meshPtr->faceNorm[1]	= ny;
		meshPtr->faceNorm[2]	= nz;

		myType	= NODE_IS_MESH;
		np		= (NODE*)meshPtr;
	}
	else if ( mgIsCode (thisnode, fltLightPoint)) 
	{
		mgGetVtxNormal(thisnode,&nx,&ny,&nz);

		lgtpntPtr			= AddLgtPnt();
		LGTPNT_PTR			= lgtpntPtr;

		memset( lgtpntPtr, 0, sizeof(LGTPNT) );

		int		lgtAppearance, lgtAnimation;
		short	repCnt;
		mgrec*	xrec;
		double	dx, dy, dz;

		mgGetAttList (thisnode, fltLpAppearance,	&lgtAppearance,
								fltLpAnimation,		&lgtAnimation,
								fltRepCnt,			&repCnt,
								MG_NULL);

		if ( lgtAnimation > 0 )
			aLog.Log( "LightPoint %s has Anim %d\n", nodeName, lgtAnimation );

		lgtpntPtr->renderFlag	= PROP_POINT_SMOOTH;
		lgtpntPtr->apprNo		= lgtAppearance;
		lgtpntPtr->animNo		= lgtAnimation;
		lgtpntPtr->extRefID		= m_currentExtRefNo;
		lgtpntPtr->type			= POLY_IS_LGTPNT;
		lgtpntPtr->nofVtx		= 0;
		lgtpntPtr->repCnt		= repCnt;
		lgtpntPtr->lgtType		= thisIsLgtPntGroup;			// no on/off & no intensity group
		lgtpntPtr->lgtGroupID	= lgtGroupID;

		if ( lgtAnimation != -1 )
		{
			aLog.Log( "LightPoint %s has Anim%d\n", nodeName, lgtAnimation );
		}

		if ( mgHasXform (thisnode) )
		{
			xrec = mgGetXform (thisnode);

			mgGetCoord3d (xrec, fltXmTranslateFrom, &x, &y, &z );
			mgGetCoord3d (xrec, fltXmTranslateDelta, &dx, &dy, &dz );

			lgtpntPtr->xlatFrom[0]	= x;
			lgtpntPtr->xlatFrom[1]	= y;
			lgtpntPtr->xlatFrom[2]	= z;

			lgtpntPtr->xlatDelta[0]	= dx;
			lgtpntPtr->xlatDelta[1]	= dy;
			lgtpntPtr->xlatDelta[2]	= dz;
		}

		myType	= NODE_IS_LGTPNT;
		np		= (NODE*)lgtpntPtr;
	}
	else if ( mgIsCode (thisnode, fltVertex)) 
	{
		mgGetVtxCoord(thisnode,&x,&y,&z);
		mgGetVtxNormal(thisnode,&nx,&ny,&nz);
		mgGetVtxColorRGBA( thisnode, &r, &g, &b, &a );

		if ( mgIsCode (mgGetParent( thisnode ), fltLightPoint) )
		{
			first = true;

			if ( lgtpntPtr->repCnt )
			{
				x	+= lgtpntPtr->xlatFrom[0];
				y	+= lgtpntPtr->xlatFrom[1];
				z	+= lgtpntPtr->xlatFrom[2];

				m_rotMVM.PassMVMd( nx, ny, nz, xyz );

				nx	= (float)xyz[0];
				ny	= (float)xyz[1];
				nz	= (float)xyz[2];

				for ( int i = 0; i < lgtpntPtr->repCnt; i++ )		// repCnt + 1 했던게 error였던거 같음
				{
					m_xFormMVM.PassMVMd( x, y, z, xyz );

					xx	= xyz[0];
					yy	= xyz[1];
					zz	= xyz[2];

					if ( first )
					{
						xmin = xmax = (float)xx;
						ymin = ymax = (float)yy;
						zmin = zmax = (float)zz;

						first = false;
					}
					else
					{
						if ( xmin > xx )
							 xmin = (float)xx;

						if ( xmax < xx )
							 xmax = (float)xx;

						if ( ymin > yy )
							 ymin = (float)yy;

						if ( ymax < yy )
							 ymax = (float)yy;

						if ( zmin > zz )
							 zmin = (float)zz;

						if ( zmax < zz )
							 zmax = (float)zz;
					}

					vl	= AddVertexLgt( lgtpntPtr );
				
					vl->vtx[0]		= xx;
					vl->vtx[1]		= yy;
					vl->vtx[2]		= zz;

					vl->norm[0]		= nx;
					vl->norm[1]		= ny;
					vl->norm[2]		= nz;

					mgGetVtxColorRGBA ( thisnode, &r, &g, &b, &a );

					vl->color[0]	= (BYTE)r;
					vl->color[1]	= (BYTE)g;
					vl->color[2]	= (BYTE)b;
					vl->color[3]	= (BYTE)a;

					x	+= lgtpntPtr->xlatDelta[0];
					y	+= lgtpntPtr->xlatDelta[1];
					z	+= lgtpntPtr->xlatDelta[2];
				}
			}
			else
			{
				m_xFormMVM.PassMVMd( x, y, z, xyz );

				x	= xyz[0];
				y	= xyz[1];
				z	= xyz[2];

				m_rotMVM.PassMVMd( nx, ny, nz, xyz );

				nx	= (float)xyz[0];
				ny	= (float)xyz[1];
				nz	= (float)xyz[2];

				if ( first )
				{
					xmin = xmax = (float)x;
					ymin = ymax = (float)y;
					zmin = zmax = (float)z;

					first = false;
				}
				else
				{
					if ( xmin > x )
						 xmin = (float)x;

					if ( xmax < x )
						 xmax = (float)x;

					if ( ymin > y )
						 ymin = (float)y;

					if ( ymax < y )
						 ymax = (float)y;

					if ( zmin > z )
						 zmin = (float)z;

					if ( zmax < z )
						 zmax = (float)z;
				}

				vl	= AddVertexLgt( lgtpntPtr );
			
				vl->vtx[0]		= x;
				vl->vtx[1]		= y;
				vl->vtx[2]		= z;

				vl->norm[0]		= nx;
				vl->norm[1]		= ny;
				vl->norm[2]		= nz;

				mgGetVtxColorRGBA ( thisnode, &r, &g, &b, &a );

				vl->color[0]	= (BYTE)r;
				vl->color[1]	= (BYTE)g;
				vl->color[2]	= (BYTE)b;
				vl->color[3]	= (BYTE)a;
			}
		}
		else
		{
			m_xFormMVM.PassMVMd( x, y, z, xyz );

			xx	= xyz[0];
			yy	= xyz[1];
			zz	= xyz[2];

			if ( first )
			{
				xmin = xmax = (float)xx;
				ymin = ymax = (float)yy;
				zmin = zmax = (float)zz;

				first = false;
			}
			else
			{
				if ( xmin > xx )
					 xmin = (float)xx;

				if ( xmax < xx )
					 xmax = (float)xx;

				if ( ymin > yy )
					 ymin = (float)yy;

				if ( ymax < yy )
					 ymax = (float)yy;

				if ( zmin > zz )
					 zmin = (float)zz;

				if ( zmax < zz )
					 zmax = (float)zz;
			}

			vc	= AddVertex( meshPtr );

			vc->vtx[0]	= x;
			vc->vtx[1]	= y;
			vc->vtx[2]	= z;

			vc->norm[0]	= nx;
			vc->norm[1]	= ny;
			vc->norm[2]	= nz;

			mgGetAttList (thisnode, fltVU, &u, fltVV, &v, MG_NULL);

			vc->st[0]	= u;
			vc->st[1]	= v;

			if ( meshPtr->texID1 > -1 )
			{
				mgGetAttList (thisnode, fltLayerU1, &u1, fltLayerV1, &v1, MG_NULL );

				vc->st1[0]	= u1;
				vc->st1[1]	= v1;
			}
		}

		dimension[0] = xmin;
		dimension[1] = xmax;
		dimension[2] = ymin;
		dimension[3] = ymax;
		dimension[4] = zmin;
		dimension[5] = zmax;
	}
	else
	{
		codeIdx		= Code2Idx(thisnode);
		if ( !code2name[codeIdx].codeKnown )
			exit(0);					// for check more format to be supported ........
	}

	// ----------------------- < node hierachy setup > --------------------
	if ( myType > -1 )
	{
		NODE*	sibling;

		m_xFormMVM.GetMatrix( (double*)np->xformMVM );
		m_rotMVM.GetMatrix( (double*)np->rotMVM );

		np->child		= NULL;					// 지금 내가 태어났는디 자식이 있겄냐 ?
		np->parent		= parentNode;			// 나의 애비

		strcpy( np->linkname, nodeName );		// 나의 이름

		if ( parentNode == NULL )				// ROOT fltHeader경우
		{
			np->left	= NULL;
			np->right	= NULL;
			np->depth	= 0;
		}
		else if ( parentNode == (NODE*)0xcccccccc )				// fltHeader경우
		{
			cLog.LogExit( "%s Has Illegal parent!\n", nodeName );
		}
		else
		{
			sibling = (NODE*)parentNode->child;

			if ( sibling == NULL )							// 첫 아들이면 맏이로 등록하고 
			{
				parentNode->child	= np;

				np->left	= NULL;
				np->right	= NULL;
			}
			else											// 이미 자식이 있므면 막내를 찾는다.
			{
				while ( sibling->right != NULL )
				{
					sibling = (NODE*)sibling->right;
				}

				sibling->right		= np;
				np->left			= sibling;
				np->right			= NULL;
			}

			np->depth	= parentNode->depth + 1;
		}

		if ( np->status & NODE_XFORMED )
		{
			for ( int i = 0; i < np->nofXform; i++ )
			{
				if ( np->xformType[i] & NODE_ROTATED )
				{
					np->rotZ	= np->rot[0] + parentNode->rotZ;
				}
			}
		}
		else
		{
			if ( parentNode )
				np->rotZ	= parentNode->rotZ;
			else
				np->rotZ	= 0.0;
		}

		np->type	= myType;						// 나의 종류
	}

	mgFree( nodeName );

	return np;
}

int
DBase::AllocGeoBuff( GEO_BUFF* gp, int maxTransPoly, int maxTransVtxCombo )
{
	if ( m_nofExtRefList )
	{
		m_maxNofExtRef	= m_nofExtRefList;

		if (( m_extRefList	= new EXTREF_LIST[m_nofExtRefList]) == NULL )
		{
			cLog.LogExit( "GeoBuff Alloc Error: *mgrec[x%d]\n", m_nofExtRefList );
		}

		memset( m_extRefList, 0, sizeof(EXTREF_LIST)*m_nofExtRefList );
	}

	m_nofExtRefList			= 0;			// 다시 0을 만들어야 읽어들이면서 증가시킬 수 있다.

	if ( gp->nofHeaderNode )
	if ((gp->headerNode	= new NODE_HEADER[gp->nofHeaderNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: headerNode[x%d]\n", gp->nofHeaderNode );
	}
	memset( gp->headerNode, 0, sizeof(NODE_HEADER)*gp->nofHeaderNode );


	if ( gp->nofExtRefNode )
	if ((gp->extRefNode	= new NODE_EXTREF[gp->nofExtRefNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: extRefNode[x%d]\n", gp->nofExtRefNode );
	}
	memset( gp->extRefNode, 0, sizeof(NODE_EXTREF)*gp->nofExtRefNode );

	if ( gp->nofGroupNode )
	if (( gp->groupNode	= new NODE_GROUP[gp->nofGroupNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: groupNode[x%d]\n", gp->nofGroupNode );
	}
	memset( gp->groupNode, 0, sizeof(NODE_GROUP)*gp->nofGroupNode );

	if ( gp->nofLODNode )
	if (( gp->lodNode		= new NODE_LOD[gp->nofLODNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: lodNode[x%d]\n", gp->nofLODNode	);
	}
	memset( gp->lodNode, 0, sizeof(NODE_LOD)*gp->nofLODNode );

	if ( gp->nofDOFNode )
	if (( gp->dofNode		= new NODE_DOF[gp->nofDOFNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: dofNode[x%d]\n", gp->nofDOFNode	);
	}
	memset( gp->dofNode, 0, sizeof(NODE_DOF)*gp->nofDOFNode );

	if ( gp->nofBSPNode )
	if (( gp->bspNode		= new NODE_BSP[gp->nofBSPNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: bspNode[x%d]\n", gp->nofBSPNode	);
	}
	memset( gp->bspNode, 0, sizeof(NODE_BSP)*gp->nofBSPNode );

	if ( gp->nofObjNode )
	if (( gp->objNode		= new NODE_OBJ[gp->nofObjNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: objNode[x%d]\n", gp->nofObjNode	);
	}
	memset( gp->objNode, 0, sizeof(NODE_OBJ)*gp->nofObjNode );

	if ( gp->nofSwitchNode )
	if (( gp->switchNode	= new NODE_SWITCH[gp->nofSwitchNode]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: switchNode[x%d]\n", gp->nofSwitchNode );
	}
	memset( gp->switchNode, 0, sizeof(NODE_SWITCH)*gp->nofSwitchNode );

	if ( gp->nofMesh )
	if (( gp->mesh		= new MESH[gp->nofMesh]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: mesh[x%d]\n", gp->nofMesh );
	}
	memset( gp->mesh, 0, sizeof(MESH)*gp->nofMesh );

	if ( gp->nofLgtPnt )
	if (( gp->lgtPnt		= new LGTPNT[gp->nofLgtPnt]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: lgtPnt[x%d]\n", gp->nofLgtPnt );
	}
	memset( gp->lgtPnt, 0, sizeof(LGTPNT)*gp->nofLgtPnt );

	if ( gp->nofVtxCombo )
	if (( gp->vtxCombo	= new VTXCOMBO[gp->nofVtxCombo]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: vtxCombo[x%d]\n", gp->nofVtxCombo );
	}
	memset( gp->vtxCombo, 0, sizeof(VTXCOMBO)*gp->nofVtxCombo );

	if ( gp->nofVtxLgt )
	if (( gp->vtxLgt	= new VTXLGT[gp->nofVtxLgt]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: vtxLgt[x%d]\n", gp->nofVtxLgt );
	}
	memset( gp->vtxLgt, 0, sizeof(VTXLGT)*gp->nofVtxLgt );

	if ( gp->nofMaterial )
	if (( gp->matList		= new MATLIST[gp->nofMaterial]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: matList[x%d]\n", gp->nofMaterial );
	}
	memset( gp->matList, 0, sizeof(MATLIST)*gp->nofMaterial );

	if ( gp->nofTexture )
	if (( gp->texList		= new TEXLIST[gp->nofTexture]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: texList[x%d]\n", gp->nofTexture );
	}
	memset( gp->texList, 0, sizeof(TEXLIST)*gp->nofTexture );

	if ( gp->noflpApprList )
	if (( gp->lpApprList	= new LPAPPR_LIST[gp->noflpApprList]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: lpApprList[x%d]\n", gp->noflpApprList );
	}
	memset( gp->lpApprList, 0, sizeof(LPAPPR_LIST)*gp->noflpApprList );

	if ( gp->noflpAnimList )
	if (( gp->lpAnimList	= new LPANIM_LIST[gp->noflpAnimList]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: lpAnimList[x%d]\n", gp->noflpAnimList );
	}
	memset( gp->lpAnimList, 0, sizeof(LPANIM_LIST)*gp->noflpAnimList );

	gp->maxTransPoly		= maxTransPoly;
	gp->maxTransVtxCombo	= maxTransVtxCombo;

	if ( gp->maxTransPoly )
	if (( gp->transPoly		= new TRANSPOLY[gp->maxTransPoly]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: transPoly[x%d]\n", gp->nofTransPoly );
	}
	memset( gp->transPoly, 0, sizeof(TRANSPOLY)*gp->maxTransPoly );

	if ( gp->maxTransVtxCombo )
	if (( gp->transVtxCombo	= new VTXCOMBO[gp->maxTransVtxCombo]) == NULL )
	{
		cLog.LogExit( "GeoBuff Alloc Error: transPoly[x%d]\n", gp->nofTransPoly );
	}
	memset( gp->transVtxCombo, 0, sizeof(VTXCOMBO)*gp->maxTransVtxCombo );

	// ---------------
	gp->nofHeaderNode	= 0;
	gp->nofExtRefNode	= 0;
	gp->nofGroupNode	= 0;
	gp->nofLODNode		= 0;
	gp->nofDOFNode		= 0;
	gp->nofBSPNode		= 0;
	gp->nofObjNode		= 0;
	gp->nofSwitchNode	= 0;
	gp->nofMesh			= 0;
	gp->nofLgtPnt		= 0;
	gp->nofVtxCombo		= 0;
	gp->nofVtxLgt		= 0;
	gp->nofMaterial		= 0;
	gp->nofTexture		= 0;
	gp->noflpApprList	= 0;
	gp->noflpAnimList	= 0;

	return 0;
}

void
DBase::FreeGeoBuff()
{
	GEO_BUFF*	gp = GeoBuff();

	if ( gp->transVtxCombo )	
		delete[] gp->transVtxCombo;

	if ( gp->transPoly )		
		delete[] gp->transPoly;

	if ( gp->lpAnimList )		
		delete[] gp->lpAnimList;

	if ( gp->lpApprList )		
		delete[] gp->lpApprList;

	if ( gp->texList )			
		delete[] gp->texList;

	if ( gp->matList )			
		delete[] gp->matList;

	if ( gp->vtxLgt )			
		delete[] gp->vtxLgt;

	if ( gp->vtxCombo )			
		delete[] gp->vtxCombo;

	if ( gp->lgtPnt )			
		delete[] gp->lgtPnt;

	if ( gp->mesh )				
		delete[] gp->mesh;

	if ( gp->switchNode )		
		delete[] gp->switchNode;

	if ( gp->objNode )			
		delete[] gp->objNode;

	if ( gp->bspNode )			
		delete[] gp->bspNode;

	if ( gp->dofNode )			
		delete[] gp->dofNode;

	if ( gp->lodNode )			
		delete[] gp->lodNode;

	if ( gp->groupNode )		
		delete[] gp->groupNode;

	if ( gp->extRefNode )		
		delete[] gp->extRefNode;

	if ( gp->headerNode )		
		delete[] gp->headerNode;

	if ( m_extRefList )			
		delete[] m_extRefList;

	gp->maxTransPoly		= 0;
	gp->maxTransVtxCombo	= 0;
}

// ================================== < Materials Of fltData > =================================
MATLIST*
DBase::AddMaterialList()
{
	return m_geoBuff.matList + m_geoBuff.nofMaterial++;
}

void
DBase::ReadMaterial(mgrec *db, mgrec *mat, int index)
{
	float		ambred, ambgreen, ambblue;
	float		diffred, diffgreen, diffblue;
	float		specred, specgreen, specblue;
	float		matshin, matalpha;
	char		*matname;
	char		madeMatName[128];
	char		*recName;
	MATLIST*	matList;

	matList = AddMaterialList();

	matname	= mgNameOfMaterial(mat, index);

	mgGetNormColor (mat, fltAmbient, &ambred, &ambgreen, &ambblue);
	mgGetNormColor (mat, fltDiffuse, &diffred, &diffgreen, &diffblue);
	mgGetNormColor (mat, fltSpecular, &specred, &specgreen, &specblue);
	mgGetAttList (mat,	fltShininess, &matshin,
						fltMatAlpha, &matalpha, MG_NULL);

	matList->ambient[0]		= ambred;
	matList->ambient[1]		= ambgreen;
	matList->ambient[2]		= ambblue;
	matList->ambient[3]		= matalpha;

	matList->diffuse[0]		= diffred;
	matList->diffuse[1]		= diffgreen;
	matList->diffuse[2]		= diffblue;
	matList->diffuse[3]		= matalpha;

	matList->specular[0]	= specred;
	matList->specular[1]	= specgreen;
	matList->specular[2]	= specblue;
	matList->specular[3]	= matalpha;

	matList->shineness		= matshin;

	matList->matNo			= index;
	matList->extRefID		= m_currentExtRefNo;

	recName = mgGetName (db);
	strcpy( matList->dbName, recName );

	if ( !matname )
	{
		sprintf( madeMatName, "%s_mat%d_%d", recName, m_currentExtRefNo, index );
		strcpy( matList->name, madeMatName );
	}
	else
	{
		strcpy( matList->name, matname );
	}

	mgFree(recName);

	mgFree(matname); /* mgNameOfMaterial allocs, must dealloc */
}

mgbool
DBase::ReadMaterialPalette(mgrec *db)
{
	mgrec *mat;
	int index;	//, matcount;

	if (mat = mgGetFirstMaterial (db, &index ))
	{
		ReadMaterial (db, mat, index);

		while (mat = mgGetNextMaterial (mat, &index))
		{
			ReadMaterial (db, mat, index);
		}
		return MG_TRUE;
	}

	return MG_FALSE;
}

// ================================== < Textures Of fltData > =================================
TEXLIST*
DBase::AddTextureList()
{
	return m_geoBuff.texList + m_geoBuff.nofTexture++;
}

mgbool
DBase::ReadTexturePalette (mgrec *db)
{
	int			patindex;	//, texcount;
	int			width, height, type;
	char		patname[1024];
	mgrec*		attr_rec;
	TEXLIST*	texList;
	char		texName[64];
	char*		recName;

	if ( mgGetFirstTexture (db, &patindex, patname) )
	{
		do
		{
			if (attr_rec = mgGetTextureAttributes (db, patindex))
			{
				mgGetAttList (attr_rec, fltImgWidth, &width,
										fltImgHeight, &height,
										fltImgType, &type,
										MG_NULL);

				texList				= AddTextureList();
				texList->texNo		= patindex;
				texList->extRefID	= m_currentExtRefNo;

				strcpy( texList->texFileName, patname );

				strcpy( texName, m_extRefName.ExtractFileNameOnly( patname ) ); 
				texName[ strchr( texName, '.') - texName ] = '\0';
				strcpy( texList->texName, texName );

				recName = mgGetName(db);
				strcpy( texList->dbName, recName );
				mgFree(recName);
			}
			else
			{
				cLog.LogExit("Texture %d: %s: Error: cannot get attributes\n",
						  patindex, patname);
			}
		} while ( mgGetNextTexture (db, &patindex, patname) );

		return MG_TRUE;
	}
	return MG_FALSE;
}

int
DBase::BoundMatID( int extRefID, int matNo )
{
	GEO_BUFF*	gp = &m_geoBuff;
	MATLIST*	mp;

	for ( int i = 0; i < gp->nofMaterial; i++ )
	{
		mp	= gp->matList + i;

		if ( mp->extRefID == extRefID && mp->matNo == matNo )
			return mp->boundID;
	}

	return -1;
}

int
DBase::BoundTexID( int extRefID, int texNo )
{
	GEO_BUFF*	gp = &m_geoBuff;
	TEXLIST*	tp;

	for ( int i = 0; i < gp->nofTexture; i++ )
	{
		tp	= gp->texList + i;

		if ( tp->extRefID == extRefID && tp->texNo == texNo )
			return tp->boundID;
	}

	
	return -1;
}

TEXLIST*
DBase::TexList( int extRefID, int texNo )
{
	GEO_BUFF*	gp = &m_geoBuff;
	TEXLIST*	tp;

	for ( int i = 0; i < gp->nofTexture; i++ )
	{
		tp	= gp->texList + i;

		if ( tp->extRefID == extRefID && tp->texNo == texNo )
			return tp;
	}

	return NULL;
}

void
DBase::LinkMatAndTexID()
{
	char		str[256];
	GEO_BUFF*	gp = &m_geoBuff;
	MESH*		mp;
	int			extRefID;
	TEXLIST*	tlp;
	eGL			nodeGL;
	VTXCOMBO	vcTmp[10];
	VTXCOMBO*	vc;
//	sprintf(str,"LinkMatAndTexId %d______________________________________________________________________________________________________________________________________________", gp->nofMesh);
//	AfxMessageBox(str); 
	for ( int m = 0; m < gp->nofMesh; m++ )
	{
/*
		if( m > 2000 ) 
		{
			sprintf(str,"Over 1000 Mesh %d : %d : %d_____________________________________________________________________________________________________\n", 
				extRefID, mp->texNo, mp->linkname);
			AfxMessageBox(str); 			
			break;
		}
*/
		mp			= gp->mesh + m;

		extRefID	= mp->extRefID;

		if ( mp->matNo > -1 )
		{
			mp->matID	= BoundMatID( extRefID, mp->matNo );
		}
		else
		{
			mp->matID	= -1;
		}

		mp->renderFlag |= PROP_LIGHTED;


		if ( mp->texNo > -1 )
		{
			tlp			= TexList( extRefID, mp->texNo );
/*
			if ( !tlp )
			{
				cLog.LogExit( "Illegal texList for extRef %d texNo %d on face %s\n", extRefID, mp->texNo, mp->linkname );
			
				sprintf(str,"Illegal texList for extRef %d texNo %d on face %s____________________________________________________________________\n", extRefID, mp->texNo, mp->linkname);
				AfxMessageBox(str); 
			}

			if ( tlp->transparent )
			{
				nodeGL.LoadMatrix( (double*)mp->xformMVM );
				memcpy( vcTmp, mp->vtxLink, sizeof(VTXCOMBO)*mp->nofVtx );
				vc	= (VTXCOMBO*)mp->vtxLink;

				for ( int i = 0; i < mp->nofVtx; i++, vc++ )
				{
					nodeGL.PassMVMdv( vcTmp[i].vtx, vc->vtx );
				}
				mp->renderFlag |= PROP_TRANSPARENT;
			}
			
			mp->renderFlag &= ~PROP_TRANSPARENT;	// #### Force to be opaque ####
*/
			mp->texID	= BoundTexID( extRefID, mp->texNo );
			mp->texID1	= BoundTexID( extRefID, mp->texNo1 );


		}
		else
			mp->texID	= -1;
		
	}
	//
//	sprintf(str,"LinkMatAndTexID ::: _____________________________________________________________________________________________________\n"	);
//	AfxMessageBox(str); 			


}

LGTPNT_APPEAR*
DBase::BoundLPApprID( int extRefID, int lpApprNo )
{
	GEO_BUFF*		gp = &m_geoBuff;
	LPAPPR_LIST*	lp;

	for ( int i = 0; i < gp->noflpApprList; i++ )
	{
		lp	= gp->lpApprList + i;

		if ( lp->extRefID == extRefID && lp->lpApprNo == lpApprNo )
			return (LGTPNT_APPEAR*)lp;
	}

	return NULL;
}

LGTPNT_ANIM*
DBase::BoundLPAnimID( int extRefID, int lpAnimNo )
{
	GEO_BUFF*		gp = &m_geoBuff;
	LPANIM_LIST*	lp;

	for ( int i = 0; i < gp->noflpAnimList; i++ )
	{
		lp	= gp->lpAnimList + i;

		if ( lp->extRefID == extRefID && lp->lpAnimNo == lpAnimNo )
			return (LGTPNT_ANIM*)lp;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////
//	clipping plane은 후 좌우/상하 순서로 한다.
//
//	lobe angle이 180를 넘어가면 안된다.
//
//	일단 후방 plane을 잡고
//		Horizontal lobe angle이 180도 이면 skip
//								180도 보다 작으면 등록
//		Vertical lobe angle이 180도 이면 skip
//								180도 보다 작으면 등록
//
/////////////////////////////////////////////////////////////////
void
DBase::CalcPlaneCoeff( VTXLGT* vc, LGTPNT* lp )
{
	eGL		tmpGL;
	double	az, in;
	double	vtx[4];
	float	norm[4];
	double	coeff[5][4];
	double	coneVtx[5][3];			// 맨 마지막은 normal의 방향을 위해
	int		nofPlane = 0;
	double	planeNorm[3];
	double	fov, foh;

	memcpy( vtx, vc->vtx, sizeof(double)*3 );
	memcpy( norm, vc->norm, sizeof(float)*3 );

	fov		= lp->apprPtr->lpVertLobeAngle;
	foh		= lp->apprPtr->lpHorizLobeAngle;

	// +x 축 기준으로 작성된 coeff를 주어진 norm까지 xform한다.
	az	= atan2( norm[1], norm[0] ) * R2D;
	in	= atan2( norm[2], sqrt( norm[0]*norm[0] + norm[1]*norm[1] ) ) * R2D;

	tmpGL.LoadIdentity();
	tmpGL.Rotated( az, 'z' );
	tmpGL.Rotated( -in, 'y' );		// -y 축을 기준으로 pitch를 들어야 하므로

	coneVtx[0][0] = coneVtx[1][0] = coneVtx[2][0] = coneVtx[3][0] = cos( foh / 2.0 * D2R ) * 2.0;

	coneVtx[0][1] = coneVtx[1][1] = -sin( foh / 2.0 * D2R ) * 2.0;
	coneVtx[2][1] = coneVtx[3][1] =  sin( foh / 2.0 * D2R ) * 2.0;

	coneVtx[0][2] = coneVtx[3][2] =  sin( fov / 2.0 * D2R ) * 2.0;
	coneVtx[1][2] = coneVtx[2][2] = -sin( fov / 2.0 * D2R ) * 2.0;

	coneVtx[4][0] = 10.0;
	coneVtx[4][1] = 0.0;
	coneVtx[4][2] = 0.0;

	for ( int i = 0 ; i < 5; i++ )
	{
		tmpGL.PassMVMdv( coneVtx[i], vc->coneVtx[i] );

		vc->coneVtx[i][0] += vtx[0];
		vc->coneVtx[i][1] += vtx[1];
		vc->coneVtx[i][2] += vtx[2];
	}

//	memcpy(	vc->coneVtx, lp->coneVtx, sizeof(double)*5*3 );

	// back plane coeff -----------------------
	coeff[4][0]	= -norm[0];							// negated component of norm
	coeff[4][1]	= -norm[1];
	coeff[4][2]	= -norm[2];

	vc->plane[nofPlane].a	= coeff[4][0];
	vc->plane[nofPlane].b	= coeff[4][1];
	vc->plane[nofPlane].c	= coeff[4][2];
	vc->plane[nofPlane].d	= -( vc->plane[nofPlane].a * vtx[0] + vc->plane[nofPlane].b * vtx[1] + vc->plane[nofPlane].c * vtx[2] );
	nofPlane++;

	if  ( foh < 180.0 )
	{
		// left plane coeff
		CalcConvexNormal( vtx, vc->coneVtx[3], vc->coneVtx[2], planeNorm );
		vc->plane[nofPlane].a	= planeNorm[0];
		vc->plane[nofPlane].b	= planeNorm[1];
		vc->plane[nofPlane].c	= planeNorm[2];
		vc->plane[nofPlane].d	= -( vc->plane[nofPlane].a * vtx[0] + vc->plane[nofPlane].b * vtx[1] + vc->plane[nofPlane].c * vtx[2] );
		nofPlane++;

		// right plane coeff
		CalcConvexNormal( vtx, vc->coneVtx[1], vc->coneVtx[0], planeNorm );
		vc->plane[nofPlane].a	= planeNorm[0];
		vc->plane[nofPlane].b	= planeNorm[1];
		vc->plane[nofPlane].c	= planeNorm[2];
		vc->plane[nofPlane].d	= -( vc->plane[nofPlane].a * vtx[0] + vc->plane[nofPlane].b * vtx[1] + vc->plane[nofPlane].c * vtx[2] );
		nofPlane++;
	}

	if  ( fov < 180.0 )
	{
		// upper plane coeff
		CalcConvexNormal( vtx, vc->coneVtx[0], vc->coneVtx[3], planeNorm );
		vc->plane[nofPlane].a	= planeNorm[0];
		vc->plane[nofPlane].b	= planeNorm[1];
		vc->plane[nofPlane].c	= planeNorm[2];
		vc->plane[nofPlane].d	= -( vc->plane[nofPlane].a * vtx[0] + vc->plane[nofPlane].b * vtx[1] + vc->plane[nofPlane].c * vtx[2] );
		nofPlane++;

		// lower plane coeff
		CalcConvexNormal( vtx, vc->coneVtx[2], vc->coneVtx[1], planeNorm );
		vc->plane[nofPlane].a	= planeNorm[0];
		vc->plane[nofPlane].b	= planeNorm[1];
		vc->plane[nofPlane].c	= planeNorm[2];
		vc->plane[nofPlane].d	= -( vc->plane[nofPlane].a * vtx[0] + vc->plane[nofPlane].b * vtx[1] + vc->plane[nofPlane].c * vtx[2] );
		nofPlane++;
	}

	vc->nofPlane = nofPlane;
}

int
DBase::GetIntensityCtrlGroupID( int lpApprNo )
{
	int		i;

	for ( i = 0; i < m_apUnderLoading->nofRwyLgtApperance; i++ )
	{
		if ( m_apUnderLoading->rwyLgtAppearance[i] == lpApprNo )
			return RUNWAY_LGT;
	}
	
	for ( i = 0; i < m_apUnderLoading->nofApproachLgtApperance; i++ )
	{
		if ( m_apUnderLoading->approachLgtAppearance[i] == lpApprNo )
			return APPROACH_LGT;
	}
	
	for ( i = 0; i < m_apUnderLoading->nofTaxiwayLgtApperance; i++ )
	{
		if ( m_apUnderLoading->taxiwayLgtAppearance[i] == lpApprNo )
			return TAXIWAY_LGT;
	}

	return 0;
}

void
DBase::LinkLPApprAndLPAnim()
{
	GEO_BUFF*	gp = &m_geoBuff;
	LGTPNT*		lp;
	int			extRefID;
	VTXLGT*		vc;
	float		halfOfSqrtTwo = (float)( sqrt(2.0) / 2.0 );

	for ( int l = 0; l < gp->nofLgtPnt; l++ )
	{
		lp			= gp->lgtPnt + l;

		extRefID	= lp->extRefID;

		// ------------------- link lightpoint appearance property ------------------
		if ( lp->apprNo > -1 )
		{
			lp->apprPtr	= BoundLPApprID( extRefID, lp->apprNo );
		}
		else
			lp->apprPtr	= NULL;

		// ------------------- lgtpnt intensity control grouping --------------------
		if ( !lp->lgtType )		// PAPI/REIL/STROBE 가 이미 define 되어 있을 경우 엎어쓰지 않도록
		{
			lp->lgtType	= GetIntensityCtrlGroupID( lp->apprNo );
		}
		
		// ------------------- calc seperate plane coeffcient -----------------------
		vc	= (VTXLGT*)lp->vtxLink;

		if ( vc && lp->apprPtr->lpDirectionalityType ) //== 1 || lp->apprPtr->lpDirectionalityType == 2 ) )
		{
			for ( int v = 0; v < lp->nofVtx; v++, vc++ )
			{
				if ( lp->apprPtr->lpHorizLobeAngle <= 0.0 || lp->apprPtr->lpHorizLobeAngle > 180.0 )
				{
					cLog.LogExit( "Illegal Horizontal lobe angle %.2f in Light Point %s\n", lp->apprPtr->lpHorizLobeAngle, lp->linkname );
				}

				if ( lp->apprPtr->lpVertLobeAngle <= 0.0 || lp->apprPtr->lpVertLobeAngle > 180.0 )
				{
					cLog.LogExit( "Illegal Vertical lobe angle %.2f in Light Point %s\n", lp->apprPtr->lpVertLobeAngle, lp->linkname );
				}

				CalcPlaneCoeff( vc, lp );
			}
		}

		// ------------------- link lightpoint animation property ------------------
		if ( lp->animNo > -1 )
		{
			lp->animPtr	= BoundLPAnimID( extRefID, lp->animNo );
		}
		else
			lp->animPtr	= NULL;
	}
}

// ================================== < Lightpoint properties > =================================
int
DBase::PrintLPAppearancePalette( mgrec *db, char* dbName )
{
	mgrec*	appr_rec;
	mgrec*	attr_rec;

	int		patindex, lpacount;

	int		lpDirectionalityType	= 0;
	float	lpMinPixelSize			= 0;
	float	lpMaxPixelSize			= 0;
	float	lpActualPixelSize		= 0;
	int		lpDaySW					= 0;
	int		lpDuskSW				= 0;
	int		lpNightSW				= 0;
	float	lpVisibilityRange		= 0;

	// --------------------------- LightPoint Appearance Palette --------------------------------
	lpacount = mgGetLightPointAppearanceCount(db);

	if ( ( appr_rec = mgGetFirstLightPointAppearance(db, &patindex) ) )
	{
		do
		{
			if ( ( attr_rec = mgGetLightPointAppearance (db, patindex) ) )
			{
				if ( !mgGetAttList(attr_rec, fltLpDirectionalityType,	&lpDirectionalityType, MG_NULL ) )
					lpDirectionalityType = -1;
				if ( !mgGetAttList(attr_rec, fltLpMinPixelSize,			&lpMinPixelSize, MG_NULL ) )
					lpMinPixelSize = -1.0;
				if ( !mgGetAttList(attr_rec, fltLpMaxPixelSize,			&lpMaxPixelSize, MG_NULL ) )
					lpMaxPixelSize = -1.0;
				if ( !mgGetAttList(attr_rec, fltLpActualSize,			&lpActualPixelSize, MG_NULL ) )
					lpActualPixelSize = -1.0;
				if ( !mgGetAttList(attr_rec, fltLpDay,					&lpDaySW, MG_NULL ) )
					lpDaySW	 = -1;
				if ( !mgGetAttList(attr_rec, fltLpDusk,					&lpDuskSW, MG_NULL ) )
					lpDuskSW = -1;
				if ( !mgGetAttList(attr_rec, fltLpNight,				&lpNightSW, MG_NULL ) )
					lpNightSW = -1;
				if ( !mgGetAttList(attr_rec, fltLpRange,				&lpVisibilityRange, MG_NULL ) )
					lpVisibilityRange = -1.0;

				m_geoBuff.noflpApprList++;
			}
			else
			{
				cLog.LogExit("LightPoint Appearance %d: Error: cannot get attributes\n",
						  patindex );
			}
		} while ( ( appr_rec = mgGetNextLightPointAppearance(appr_rec, &patindex) ) );
	}

	return lpacount;
}

int
DBase::PrintLPAnimationPalette( mgrec *db, char* dbName )
{
	mgrec*	anim_rec;
	mgrec*	attr_rec;

	int		patindex, lpacount;

	int		lpaType					= 0;
	int		lpaRotOn				= 0;
	int		lpaFlashOn				= 0;
	int		lpaRotDirection			= 0;				// if true CCW
	int		lpaSeqLength			= 0;
	float	lpaPeriod				= 0.0;
	float	lpaPhaseDelay			= 0.0;
	float	lpaTimeOn				= 0.0;

	// --------------------------- LightPoint Animation Palette --------------------------------
	lpacount = mgGetLightPointAnimationCount(db);

	if ( ( anim_rec = mgGetFirstLightPointAnimation(db, &patindex) ) )
	{
		do
		{
			if ( ( attr_rec = mgGetLightPointAnimation (db, patindex) ) )
			{
				mgGetAttList (attr_rec, fltLpDirectionalityType,	&lpaType,
										fltLpAnimationType,			&lpaType,
										fltLpRotating,				&lpaRotOn,
										fltLpFlashing,				&lpaFlashOn,
										fltLpRotateCCW,				&lpaRotDirection,
										fltLpPeriod,				&lpaPeriod,
										fltLpPhaseDelay,			&lpaPhaseDelay,
										fltLpTimeOn,				&lpaTimeOn,
										fltLpSequenceLength,		&lpaSeqLength,
										MG_NULL);


				m_geoBuff.noflpAnimList++;
			}
			else
			{
				cLog.LogExit("LightPoint Animation %d: Error: cannot get attributes\n",
						  patindex );
			}
		} while ( ( anim_rec = mgGetNextLightPointAnimation(anim_rec, &patindex) ) );
	}

	return lpacount;
}

// ================================== < Lightpoint properties > =================================
LPAPPR_LIST*
DBase::AddLPAppearList()
{
	return m_geoBuff.lpApprList + m_geoBuff.noflpApprList++;
}
LPANIM_LIST*
DBase::AddLPAnimList()
{
	return m_geoBuff.lpAnimList + m_geoBuff.noflpAnimList++;
}

int
DBase::ReadLPApprPalette (mgrec *db)
{
	mgrec*	appr_rec;
	mgrec*	attr_rec;
	char*	recName;

	int				patindex;	//, lpacount;
	LPAPPR_LIST*	lpApprList;

	char			patname[1024];

	int				lpDirectionalityType	= 0;
	float			lpMinPixelSize			= 0;
	float			lpMaxPixelSize			= 0;
	float			lpActualPixelSize		= 0;
	int				lpDaySW					= 0;
	int				lpDuskSW				= 0;
	int				lpNightSW				= 0;
	float			lpVisibilityRange		= 0;

	float			lpHorizLobeAngle		= 0.0;
	float			lpVertLobeAngle			= 0.0;
	float			lpLobeRollAngle			= 0.0;
	float			lpLobeFallOff			= 0.0;

	float			lpAmbientIntensity		= 0.0;
	bool			lpNoBackColor			= true;
	float			lpBackColorIntensity	= 0.0;


	// --------------------------- LightPoint Appearance Palette --------------------------------
	if ( ( appr_rec = mgGetFirstLightPointAppearance(db, &patindex) ) )
	{
		do
		{
			if ( ( attr_rec = mgGetLightPointAppearance (db, patindex) ) )
			{
				if ( !mgGetAttList( attr_rec, fltLpDirectionalityType,	&lpDirectionalityType,	MG_NULL ) )
					lpDirectionalityType	= -1;
				if ( !mgGetAttList( attr_rec, fltLpMinPixelSize,		&lpMinPixelSize,		MG_NULL ) )
					lpMinPixelSize			= -1;
				if ( !mgGetAttList( attr_rec, fltLpMaxPixelSize,		&lpMaxPixelSize,		MG_NULL ) )
					lpMaxPixelSize			= -1;
				if ( !mgGetAttList( attr_rec, fltLpActualSize,			&lpActualPixelSize,		MG_NULL ) )
					lpActualPixelSize		= -1;
				if ( !mgGetAttList( attr_rec, fltLpDay,					&lpDaySW,				MG_NULL ) )
					lpDaySW					= -1;
				if ( !mgGetAttList( attr_rec, fltLpDusk,				&lpDuskSW,				MG_NULL ) )
					lpDuskSW				= -1;
				if ( !mgGetAttList( attr_rec, fltLpNight,				&lpNightSW,				MG_NULL ) )
					lpNightSW				= -1;
				if ( !mgGetAttList( attr_rec, fltLpRange,				&lpVisibilityRange,		MG_NULL ) )
					lpVisibilityRange		= -1;
				if ( !mgGetAttList( attr_rec, fltLpHorizLobeAngle,		&lpHorizLobeAngle,		MG_NULL ) )
					lpHorizLobeAngle		= -1;
				if ( !mgGetAttList( attr_rec, fltLpVertLobeAngle,		&lpVertLobeAngle,		MG_NULL ) )
					lpVertLobeAngle			= -1;
				if ( !mgGetAttList( attr_rec, fltLpLobeRollAngle,		&lpLobeRollAngle,		MG_NULL ) )
					lpLobeRollAngle			= -1;
				if ( !mgGetAttList( attr_rec, fltLpLobeFallOff,			&lpLobeFallOff,			MG_NULL ) )
					lpLobeFallOff			= -1;
				if ( !mgGetAttList( attr_rec, fltLpAmbientIntensity,	&lpAmbientIntensity,	MG_NULL ) )
					lpAmbientIntensity		= -1;
				if ( !mgGetAttList( attr_rec, fltLpNoBackColor,			&lpNoBackColor,			MG_NULL ) )
					lpNoBackColor			= true;
				if ( !mgGetAttList( attr_rec, fltLpBackColorIntensity,	&lpBackColorIntensity,	MG_NULL ) )
					lpBackColorIntensity	= -1;

				lpApprList = AddLPAppearList();

				lpApprList->lpApprNo	= patindex;
				lpApprList->extRefID	= m_currentExtRefNo;

				sprintf( patname, "%_lpAppr%d", patindex );
				recName = mgGetName(db);
				strcpy( lpApprList->dbName, recName );
				strcat( lpApprList->dbName, patname );
				mgFree(recName);

				lpApprList->lpDirectionalityType	= lpDirectionalityType;
				lpApprList->lpMinPixelSize			= lpMinPixelSize;
				lpApprList->lpMaxPixelSize			= lpMaxPixelSize;
				lpApprList->lpActualPixelSize		= lpActualPixelSize;
				lpApprList->lpVisibilityRange		= lpVisibilityRange;

				lpApprList->lpTOD					= 0;

				if ( !lpDaySW ) lpApprList->lpTOD	|= TOD_HIDE_ON_DAY;
				if ( !lpDuskSW ) lpApprList->lpTOD	|= TOD_HIDE_ON_DUSK;
				if ( !lpNightSW ) lpApprList->lpTOD	|= TOD_HIDE_ON_DARK;

				lpApprList->lpHorizLobeAngle		= lpHorizLobeAngle;
				lpApprList->lpVertLobeAngle			= lpVertLobeAngle;
				lpApprList->lpLobeRollAngle			= lpLobeRollAngle;
				lpApprList->lpLobeFallOff			= lpLobeFallOff;

				lpApprList->lpAmbientIntensity		= lpAmbientIntensity;
				lpApprList->lpNoBackColor			= lpNoBackColor;
				lpApprList->lpBackColorIntensity	= lpBackColorIntensity;
			}
			else
			{
				cLog.LogExit("LightPoint Appearance %d: Error: cannot get attributes\n",
						  patindex );
			}
		} while ( ( appr_rec = mgGetNextLightPointAppearance(appr_rec, &patindex) ) );
	}

	return MG_FALSE;
}

int
DBase::ReadLPAnimPalette (mgrec *db)
{
	mgrec*	anim_rec;
	mgrec*	attr_rec;
	char*	recName;

	int				patindex;	//, lpacount;
	LPANIM_LIST*	lpAnimList;

	char			patname[1024];

	int				lpaType					= 0;
	int				lpaRotOn				= 0;
	int				lpaFlashOn				= 0;
	int				lpaRotDirection			= 0;				// if true CCW
	int				lpaSeqLength			= 0;
	float			lpaPeriod				= 0.0;
	float			lpaPhaseDelay			= 0.0;
	float			lpaTimeOn				= 0.0;

	// --------------------------- LightPoint Animation Palette --------------------------------
	if ( ( anim_rec = mgGetFirstLightPointAnimation(db, &patindex) ) )
	{
		do
		{
			if ( ( attr_rec = mgGetLightPointAnimation (db, patindex) ) )
			{
				mgGetAttList (attr_rec, fltLpAnimationType,			&lpaType,
										fltLpRotating,				&lpaRotOn,
										fltLpFlashing,				&lpaFlashOn,
										fltLpRotateCCW,				&lpaRotDirection,
										fltLpPeriod,				&lpaPeriod,
										fltLpPhaseDelay,			&lpaPhaseDelay,
										fltLpTimeOn,				&lpaTimeOn,
										fltLpSequenceLength,		&lpaSeqLength,
										MG_NULL);
				lpAnimList = AddLPAnimList();

				lpAnimList->lpAnimNo		= patindex;
				lpAnimList->extRefID		= m_currentExtRefNo;
				lpAnimList->lpaType			= lpaType;
				lpAnimList->lpaFlashOn		= lpaFlashOn;
				lpAnimList->lpaRotDirection	= lpaRotDirection;
				lpAnimList->lpaSeqLength	= lpaSeqLength;
				lpAnimList->lpaPeriod		= lpaPeriod;
				lpAnimList->lpaTimeOn		= lpaTimeOn;
				lpAnimList->lpaPhaseDelay	= lpaPhaseDelay;

				sprintf( patname, "%_lpAnim%d", patindex );
				recName = mgGetName(db);
				strcpy( lpAnimList->dbName, recName );
				strcat( lpAnimList->dbName, patname );
				mgFree(recName);

//				cLog.Log ("LightPoint Animation[%d] : type = %d\n", patindex, lpaType );
			}
			else
			{
				cLog.LogExit("LightPoint Animation %d: Error: cannot get attributes\n",
						  patindex );
			}
		} while ( ( anim_rec = mgGetNextLightPointAnimation(anim_rec, &patindex) ) );
	}

	return MG_FALSE;
}

int
DBase::ExtRefName2ID( char* name )
{
	for ( int i = 0; i < m_nofExtRefList; i++ )
	{
		if ( _stricmp( m_extRefList[i].extRefName, name ) == 0 )
			return i;
	}

	return -1;
}

int
DBase::AddExtRefName( char* name, mgrec* thisrec )
{
	int		extRefID = ExtRefName2ID(name);

	if ( extRefID == -1 )
	{
		if ( m_nofExtRefList >= m_maxNofExtRef )
		{
			cLog.LogExit( "ExtRef full at db %d\n", name );
		}

		extRefID	= m_nofExtRefList++;
		strcpy( m_extRefList[extRefID].extRefName, name );
		m_extRefList[extRefID].dbRec	= thisrec;
	}
	else
		cLog.LogExit( "ExtRef %s already exist\n", name );

	return extRefID;
}

void
DBase::PushFltStack( mgrec* extRefRec, int extRefNo, char *extRefFileName, char* extRefName )
{
	int		sp = m_SP++;

	if ( extRefNo == 35 )
		extRefNo = extRefNo;

	if ( m_SP >= MAX_STACK_DEPTH )
	{
		cLog.LogExit( "Flt stack overflow!\n" );
	}

	m_stack[m_SP].extRefRec		= extRefRec;
	m_stack[m_SP].extRefNo		= extRefNo;
	strcpy( m_stack[m_SP].extRefFileName,	extRefFileName );
	strcpy( m_stack[m_SP].extRefName,		extRefName );
}

void
DBase::PopFltStack( mgrec** extRefRec, int& extRefNo, char* extRefFileName, char* extRefName )
{
	if ( !m_SP )
	{
		cLog.LogExit( "Flt stack underflow!\n" );
	}

	*extRefRec		= m_stack[m_SP].extRefRec;
	extRefNo		= m_stack[m_SP].extRefNo;
	strcpy( extRefFileName, m_stack[m_SP].extRefFileName );
	strcpy( extRefName, m_stack[m_SP].extRefName );

	m_SP--;
}

void
DBase::PrintNodeLinkage( NODE* np, int nodeSP, int nodeStatus  )
{
	NODE_HEADER*	nhp;
	NODE_GROUP*		ngp;
	NODE_LOD*		nlp;
	NODE_DOF*		ndp;
	NODE_BSP*		nbp;
	NODE_OBJ*		nop;
	NODE_SWITCH*	nsp;
	MESH*			mp;
	LGTPNT*			lp;

	double			dx, dy, dz, len;

	static	int		nofHeader				= 0;
	static	int		nofExtRef				= 0;
	static	int		nofGroup				= 0;
	static	int		nofLOD					= 0;
	static	int		nofDOF					= 0;
	static	int		nofBSP					= 0;
	static	int		nofSWITCH				= 0;
	static	int		nofOBJ					= 0;
	static	int		nofRenderedPolygon		= 0;
	static	int		nofRenderedMesh			= 0;
	static	int		nofRenderedLightPoint	= 0;

	if ( nodeSP == 0 )
	{
		nofHeader				= 0;
		nofExtRef				= 0;
		nofGroup				= 0;
		nofLOD					= 0;
		nofDOF					= 0;
		nofBSP					= 0;
		nofSWITCH				= 0;
		nofOBJ					= 0;
		nofRenderedPolygon		= 0;
		nofRenderedMesh			= 0;
		nofRenderedLightPoint	= 0;
	}

	if ( !np )
		return;

	// ========================== (( Opaque 1st Pass Render )) ==========================
	while( 1 )			// next sibling loop
	{
		if ( np->status & NODE_XFORMED )
		{
			for ( int i = 0; i < nodeSP; i++ )
				gLog.Log( "\t" );

			gLog.Log( "glPushMatrix()-----------\n" );

			for ( i = 0; i < np->nofXform; i++ )
			{
				if ( np->xformType[i] == NODE_XLATED )
					gLog.Log( "glTranslated( %.2f, %.2f, %.2f)------------\n", np->xlat[0], np->xlat[1], np->xlat[2] );
				else if ( np->xformType[i] == NODE_ROTATED )
					gLog.Log( "glRotated( %.2f, %.2f, %.2f, %.2f)------------\n", np->rot[0], np->rot[1], np->rot[2], np->rot[3] );
				else if ( np->xformType[i] == NODE_SCALED )
					gLog.Log( "glScaled( %.2f, %.2f, %.2f)------------\n", np->scale[0], np->scale[1], np->scale[2] );
			}
		}

		for ( int i = 0; i < nodeSP; i++ )
			gLog.Log( "\t" );

		switch( np->type )
		{
		case NODE_IS_HEADER:
			nhp = (NODE_HEADER*)np;
			nofHeader++;
			gLog.Log( "Header %s\n", np->linkname );
			if ( np->child )
				PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_EXTREF:
			ngp = (NODE_GROUP*)np;
			nofExtRef++;
			gLog.Log( "ExtRef %s\n", np->linkname );
			if ( np->child )
				PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_GROUP:
			ngp = (NODE_GROUP*)np;
			nofGroup++;
			gLog.Log( "Group %s\n", np->linkname );
			if ( np->child )
				PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_LOD:
			nlp = (NODE_LOD*)np;

			dx = nlp->cx - m_dbEyePos[0];
			dy = nlp->cy - m_dbEyePos[1];
			dz = nlp->cz - m_dbEyePos[2];

			len = (float)sqrt( dx*dx + dy*dy + dz*dz );			// lod node중심 까지의 거리

			nofLOD++;

			if ( nlp->swIn < len || nlp->swOut > len ) 		// lod descendants를 그리지 않는다.
			{
				break;
			}

			gLog.Log( "Lod %s( center: %.2f, %.2f, %.2f  swIn: %.2f  swOut: %.2f )\n", np->linkname, nlp->cx, nlp->cy, nlp->cz, nlp->swIn, nlp->swOut );

			if ( np->child )
				PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_DOF:
			ndp = (NODE_DOF*)np;
			nofDOF++;
			
			gLog.Log( "Dof %s( xlat: %.2f, %.2f, %.2f   rot:%.2f, %.2f, %.2f, %.2f  scale: %.2f, %.2f, %.2f )\n",
						np->linkname,
						ndp->dofXlat[0], ndp->dofXlat[1], ndp->dofXlat[2],
						ndp->dofRotAngle, ndp->dofRotNorm[1], ndp->dofRotNorm[2], ndp->dofRotNorm[3],
						ndp->dofScale[0], ndp->dofScale[1], ndp->dofScale[2] );

			PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_BSP:
			nbp = (NODE_BSP*)np;
			nofBSP++;
			gLog.Log( "Bsp %s( plane: a=%.2f, b=%.2f, c=%.2f, d=%.2f )  Eye: (%.2f, %.2f, %.2f )\n", np->linkname, nbp->a, nbp->b, nbp->c, nbp->d, m_dbEyePos[0], m_dbEyePos[1], m_dbEyePos[2] );

			len = nbp->a * m_dbEyePos[0]
				+ nbp->b * m_dbEyePos[1]
				+ nbp->c * m_dbEyePos[2]
				+ nbp->d;

			if ( len < 0.0 )
			{
				PrintNodeLinkage( (NODE*)np->child, nodeSP+1, NODE_CHILD_OF_BSP );
			}
			else
			{
				PrintNodeLinkage( (NODE*)( ( (np->child)->right)->right), nodeSP+1, NODE_CHILD_OF_BSP | NODE_REV_DIRECTION );
			}			
			break;

		case NODE_IS_SWITCH:
			nsp = (NODE_SWITCH*)np;
			nofSWITCH++;
			gLog.Log( "Switch %s( %d )\n", np->linkname, 0 );
			PrintNodeLinkage( (NODE*)np->child, nodeSP+1, NODE_CHILD_OF_SWITCH );
			break;

		case NODE_IS_OBJ:
			nop = (NODE_OBJ*)np;
			nofOBJ++;
			gLog.Log( "Obj %s( todSW: %d )\n", np->linkname, nop->todSW );
			PrintNodeLinkage( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_MESH:
			mp	= (MESH*)np;
			nofRenderedMesh++;
			gLog.Log( "Mesh %s( tex: %d  mat: %d  renderFlag: %X )\n", 
							np->linkname, mp->texID, mp->matID, mp->renderFlag );

			gLog.Log( "Xlat(%.2f, %.2f, %.2f)\n", np->xformMVM[3][0], np->xformMVM[3][1], np->xformMVM[3][2] );

			if ( !( nodeStatus & NODE_CHILD_OF_BSP ) )
				PrintNodeLinkage( (NODE*)mp->child, nodeSP+1 );
			break;

		case NODE_IS_LGTPNT:
			lp	= (LGTPNT*)np;
			nofRenderedLightPoint++;
			gLog.Log( "Lgtpnt %s( appr: %d  anim: %d  repCnt: %d  type: %d  xlatFrom( %.2f, %.2f, %.2f )  xlatDelta( %.2f, %.2f, %.2f )\n",
									np->linkname, lp->apprNo, lp->animNo, lp->repCnt, lp->type,
									lp->xlatFrom[0], lp->xlatFrom[1], lp->xlatFrom[2],
									lp->xlatDelta[0], lp->xlatDelta[1], lp->xlatDelta[2] );

			gLog.Log( "Xlat(%.2f, %.2f, %.2f)\n", np->xformMVM[3][0], np->xformMVM[3][1], np->xformMVM[3][2] );
			PrintNodeLinkage( (NODE*)lp->child, nodeSP+1 );
			break;
		}

		if ( np->status & NODE_XFORMED )
			gLog.Log( "glPopMatrix()-----------\n" );

		if ( nodeStatus & NODE_CHILD_OF_SWITCH )
			return;

		if ( nodeStatus & NODE_REV_DIRECTION )
			np = (NODE*)np->left;
		else
			np = (NODE*)np->right;

		if ( !np )
			return;
	}

	if ( !nodeSP )
	{
		gLog.Log( "==================<< Count >> ==================" );

		gLog.Log( "nofHeader: %d\n", nofHeader );
		gLog.Log( "nofExtRef: %d\n", nofExtRef );
		gLog.Log( "nofGroup: %d\n", nofGroup );
		gLog.Log( "nofLOD: %d\n", nofLOD );
		gLog.Log( "nofDOF: %d\n", nofDOF );
		gLog.Log( "nofBSP: %d\n", nofBSP );
		gLog.Log( "nofSWITCH: %d\n", nofSWITCH );
		gLog.Log( "nofOBJ: %d\n", nofOBJ );
		gLog.Log( "nofRenderedPolygon: %d\n", nofRenderedPolygon );
		gLog.Log( "nofRenderedMesh: %d\n", nofRenderedMesh );
		gLog.Log( "nofRenderedLightPoint: %d\n", nofRenderedLightPoint );
	}

	gLog.LogClose();

	return;
}

void
DBase::SetEyePos( double* eyePos )
{
	m_dbEyePos = eyePos;
}

void
DBase::CalcConvexNormal( double* v0, double* v1, double* v2, double* v )
{
    double xa, xb, ya, yb, za, zb;
	double l;
	double a, b, c;

	xa = v1[0] - v0[0];
	ya = v1[1] - v0[1];
	za = v1[2] - v0[2];

	xb = v2[0] - v0[0];
	yb = v2[1] - v0[1];
	zb = v2[2] - v0[2];

	a = ya*zb - za*yb;
	b = za*xb - xa*zb;
	c = xa*yb - ya*xb;

	l = sqrt( a*a + b*b + c*c );
 
	if( l == 0.0)
	{
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
    }
    else {
        v[0] = (a / l);
        v[1] = (b / l);
        v[2] = (c / l);
    }
}
