#if !defined(_XR_MODEL_H_INCLUDED_)
#define _XR_MODEL_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/gl.h>
#include "eGL.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"
#include "LightPoint.h"

#define	MAX_MODEL					50				// 34     2002. 03. 20
#define	MAX_NODE					5000			// 6032
#define	MAX_LNODE					5000			// 6032
#define	MAX_BVLOD					5000			// 6032

#define	MAX_POLYGON					300000			// 167960
#define	MAX_TRANSPARENT_POLYGON		20000
#define	MAX_MULTITEXTURED_POLYGON	20000
#define	MAX_VTXCOMBO				500000			// 503880
#define	MAX_LGTPNT					50000

#define	MAX_TRANSORT				10000
#define	MAX_LGTSTR_GROUP			1000	

#define	MAX_VTX_LIST				500000			// 119289

#define	MAX_TRANSPARENT_VTXCOMBO	20000
#define	MAX_MESH					1000
#define	MAX_MAT						1000

#define	NODE_EMPTY					0x00000001
#define	NODE_HIDDEN					0x00000002
#define	NODE_STLINKED				0x00000004
#define	NODE_OPENED					0x00000008

#define	NODE_BACKFACE				0x00000010
#define	NODE_LOCALIZED				0x00000020

#define	NODE_XFORMED				0x00000100
//#define	NODE_XLATED					0x00000200
//#define	NODE_ROTATED				0x00000400
//#define	NODE_SCALED					0x00000800
#define	NODE_IMPORTED				0x00001000
#define	NODE_LINKPORTED				0x00002000
#define	NODE_SELECTED				0x00004000
#define	NODE_LISTED					0x00008000
#define	NODE_LANDING_LIGHTED		0x00010000


//#define	NODE_XFORM_ENABLED			0x00010000

#define	NODE_XLATED					1
#define	NODE_ROTATED				2
#define	NODE_SCALED					3

//===============================================================================
#define	MULTI_TEXTURE_MASK			0xFF000000
#define	PROP_MULTI_TEXTURED			0x80000000		// 1: simply Multi-texture polygon
#define	PROP_MULTI_TEXTURED1		0x40000000		// 1: doubly Multi-texture polygon
#define	PROP_MULTI_BLEND_ADD		0x20000000
#define	PROP_MULTI_REFLECTIVE		0x10000000
#define	PROP_MULTI_LIGHTED			0x08000000		// not working ( 2nd-pass multi texture surface is not lighted now )

#define	PROP_TEXTURED				0x00800000
#define	PROP_LIGHTED				0x00400000
#define	PROP_FLAT_SHADED			0x00200000
#define	PROP_REFLECTIVE				0x00100000

#define	PROP_TRANSPARENT			0x00080000
#define	PROP_BLEND_TEV				0x00040000
#define	PROP_BLEND_ADD				0x00020000
#define	PROP_PRIME_COLOR			0x00010000

#define	PROP_ZBUFFER_OFF			0x00008000
#define	PROP_TWO_SIDED				0x00004000
#define	PROP_POINT_SMOOTH			0x00002000

#define	PROP_LIGHT_DIRECTIONAL		0x00000800
#define	PROP_LIGHT_ROTATE_ANIM		0x00000400
#define	PROP_LIGHT_ONOFF_ANIM		0x00000200

#define	PROP_STAMP					0x00000002
#define	PROP_ROAD					0x00000001

// g_node[polyNo].globalProp bit assignment T--FXZWS
// TR-FXZWS (Transp, x, x, Flat, Texture, TwoSided, SmoothPoint )
#define	NODE_TRANSPARENT			PROP_TRANSPARENT
#define	NODE_ROAD					PROP_ROAD
#define	NODE_STAMP					PROP_STAMP
#define	NODE_FLAT_SHADE				PROP_FLAT_SHADED
#define	NODE_TEXTURED				PROP_TEXTURED
#define	NODE_ZBUFFER_OFF			PROP_ZBUFFER_OFF
#define	NODE_TWO_SIDED				PROP_TWO_SIDED
#define	NODE_SMOOTH					PROP_SMOOTH

#define	MAX_TRANSORT				10000
#define	MAX_LGTSTR_GROUP			1000	

// For on / off control
#define	DEFAULT_LGT					0
#define	APPROACH_LGT				0x00000001
#define	RUNWAY_LGT					0x00000002
#define	TAXIWAY_LGT					0x00000004
#define	REIL_LGT					0x00000008
#define	VASI_PAPI_LGT				0x00000010
#define	STROBE_LGT					0x00000020

#define	DISP_WIRE					0x00000001
#define	DISP_ALL_LOD				0x00000002
#define	DISP_BSP_PLANE				0x00000004
#define	DISP_LOD_CIRCLE				0x00000008
#define	DISP_LIGHT_NORMAL			0x00000010
#define	DISP_BLACK_BKGND			0x00000020
#define DISP_RAIN					0x00000040
#define DISP_SNOW					0x00000080
#define	DISP_AXIS					0x00000100
#define	DISP_BV						0x00000200
#define	HIDE_SKY_BOX				0x00000400
#define	BV_TEST						0x00000800
#define	DISP_LANDING_LGT			0x00001000

#define	NODE_REV_DIRECTION			0x00000001
#define	NODE_CHILD_OF_BSP			0x00000002
#define	NODE_CHILD_OF_SWITCH		0x00000004
#define	NODE_CHILD_OF_APPROACH_LGT	0x00000010
#define	NODE_CHILD_OF_RUNWAY_LGT	0x00000010
#define	NODE_CHILD_OF_TAXIWAY_LGT	0x00000010

// =================================== << OBJ type structued >> ====================================
#ifndef	_VTXCOMBO_
#define _VTXCOMBO_
struct VTXCOMBO
{
	float	color[4];
	float	norm[4];
	double	st[2];
	double	st1[2];					// multi texture
	double	vtx[4];
	double	avtx[4];
};
#endif

struct LINK
{
	int				type;		// NODE_IS_HEADER ~ NODE_IS_SWITCH (8가지 종류)
	LINK*			parent;
	LINK*			child;
	LINK*			left;
	LINK*			right;
	int				depth;
	double			rotZ;
	Matrix			rotMVM;
	Matrix			xformMVM;

	float			bv[4];
	float			xmin, xmax;
	float			ymin, ymax;
	float			zmin, zmax;

	char			linkname[64];		// node자신의 이름
};

struct GEO : public LINK
{
	int				type;			// poly, mesh (tri-strip, tri-fan, quad-strip, indexed-poly, lgtpnt
	int				nofVtx;
	void*			vtxLink;		// VTXCOMBO* or VTXLGT*
	unsigned int	renderFlag;
	GEO*			next;

	BYTE			primeColor[4];
	float			faceNorm[4];	// polygon face normal, or lgtpnt beam direction
};

struct MESH : public GEO
{
	int				texNo;
	int				texNo1;
	int				matNo;

	int				texID;			// primary	 texture
	int				texID1;			// secondary texture
	int				matID;			// primary Material ID ( white material )

	int				extRefID;		// 여러개의 external ref단위별로 matID/texID 가 0부터 시작하기 때문에 필요함
	int				rendered;
};

struct TRANSPOLY
{
	int				sameCoord;		// if true then use vtx coord from meshPtr->vtxLink
	MESH*			meshPtr;
	VTXCOMBO*		transVtxLink;	// if false the use vtx coord from transVtxLink
	double			centerPos[3];
};

struct PLANE
{
	double			a;
	double			b;
	double			c;
	double			d;
};

struct VTXLGT
{
	BYTE			color[4];
	BYTE			backColor[4];
	float			norm[4];
	double			vtx[4];

	int				nofPlane;
	PLANE			plane[5];

	double			coneCntrVtx[3];
	double			coneVtx[5][3];
};

#ifndef _EXTDEF_LGT_
#define	_EXTDEF_LGT_

struct	EXTDEF_LGT
{
	char	extDefName[64];
	float	vAngle;
	float	hLobe;
	float	vLobe;
	float	visibility;
	float	actPntSize;
	float	maxPntSize;
	float	minPntSize;
};

#endif

struct LGTPNT : public GEO
{
	int				lgtType;
	int				lgtGroupID;		// 
	int				apprNo;
	int				animNo;

	LGTPNT_APPEAR*	apprPtr;
	LGTPNT_ANIM*	animPtr;
	int				extDefType;		// REIL_LGT, VASI_PAPI_LGT, STROBE_LGT 사용
	EXTDEF_LGT*		extDefPtr;

	short			repCnt;
	double			xlatFrom[3];
	double			xlatDelta[3];
	int				extRefID;		// 여러개의 external ref단위별로 matID/texID 가 0부터 시작하기 때문에 필요함

//	double			rotZ;
//	Matrix			rotMVM;
//	Matrix			xformMVM;

//	int				nofPlane;
//	PLANE			plane[5];

//	double			coneVtx[5][3];

	int				rendered;
};

struct TRANS_POLYGON
{
	MESH*			mp;
	int				absCoord;
	VTXCOMBO*		vtxLink;		// vertex combo start addr
};

struct TRANSORT : public MESH
{
	int				polyNo;
	int				glMeshType;
	MESH*			mp;
};

struct NODE : public LINK
{
	int				status;		// bit0:	set - empty
								// bit1:	set - hidden (enalbed/disabled)
								// bit2:	set - St linked
								// bit3:	set - opened

								// bit4:	set - backface
								// bit5:	set - localized

								// bit8:	set - xformed
								// bit9:	set - xlated
								// bit10:	set - rotated
								// bit11:	set - scaled

								// bit12:	set - imported

								// bit31:	set - selected

	float			cx, cy, cz, radius;
	float			dimension[6];	// x, y, z 방향 최대-최소값 (자신의 하위 tree에 속한 모든 obj의 합임)

	BYTE			nofXform;
	BYTE			xformType[3];
	double			xlat[3];
	float			rot[4];
	double			rotCenter[3];
	double			scale[3];
	double			scaleCenter[3];
};

struct NODE_EXTREF : public NODE		// External reference node
{
	char			xrefFileName[256];		// DB filename
};

struct NODE_HEADER : public NODE		// Root node
{
	char			filename[256];		// DB filename
	char			matListFile[256];	// material list를 저장하고있는 filename
	char			texListFile[256];	// texture list를 저장하고있는 filename
	char			palListFile[256];	// palette list를 저장하고있는 filename
	int				version;			// DB format version
};

struct NODE_OBJ : public NODE				// 실제 형상을 가지는 node
{
	unsigned int	globalRenderProp;		// T--FTZWS (Transp, x, x, Flat, Texture, TwoSided, SmoothPoint )
	int				matID;					// Node전체의 material이 같을 경우 사용
	int				texID;					// Node전체의 texture가 같을 경우 사용
	float			norm[3];
	float			color[3];
	float			transparency;			// 0.0 : transparent, 1.0 : opaque

	GEO*			polyLink;				// mesh or lgtpnt
	int				nofGeo;
	int				todSW;					// 
};

struct NODE_GROUP : public NODE_OBJ			// 단순히 tree를 구성하기 위한 node
{
};

struct NODE_LOD : public NODE_OBJ			// level of detail 분기를 위한 node
{
	float			cx, cy, cz;
	float			swIn, swOut;
};

struct NODE_DOF : public NODE				// 관절운동을 지원하는 node
{
	double			dofXlat[3];				// tx, ty, tz
	double			dofXlatNorm[3];
	double			dofXlatInc;
	double			dofMinXlat;
	double			dofMaxXlat;
	
	double			dofRotCenter[3];
	double			dofRotAngle;			// angle, ax, ay, az
	double			dofRotNorm[3];
	double			dofRotInc;
	double			dofMinRot;
	double			dofMaxRot;
	
	int				dofScaled;
	float			dofScale[3];			// sx, sy, sz
	
	int				xlatOn;
	int				rotOn;
	int				scaleOn;

	double			dofFrame;
};

struct NODE_BSP : public NODE				// bsp tree 분기점
{
	double			a, b, c, d;
};

struct NODE_SWITCH : public NODE			// on/off를 제어하는 node
{
	int				maxMask;				// if true then render descendants
	int				currentMask;
};

struct MATLIST : public MATERIAL
{
	int				matNo;					// mgGetFirstMaterial 에서 return된 index 값
	int				extRefID;
	char			dbName[256];			// external ref db filename
};

struct TEXLIST : public sTEXTURE
{
	int				texNo;					// mgGetFirstTexture 에서 return된 index 값
	int				extRefID;
	char			dbName[256];			// external ref db filename
};

struct LPAPPR_LIST : public LGTPNT_APPEAR
{
	int				lpApprNo;				// mgGetFirstTexture 에서 return된 index 값
	int				extRefID;
	char			dbName[256];			// external ref db filename
};

struct LPANIM_LIST : public LGTPNT_ANIM
{
	int				lpAnimNo;				// mgGetFirstTexture 에서 return된 index 값
	int				extRefID;
	char			dbName[256];			// external ref db filename
};

#define	NODE_IS_HEADER	1
#define	NODE_IS_EXTREF	2
#define	NODE_IS_GROUP	3
#define	NODE_IS_LOD		4
#define	NODE_IS_DOF		5
#define	NODE_IS_BSP		6
#define	NODE_IS_SWITCH	7
#define	NODE_IS_OBJ		8
#define	NODE_IS_MESH	9
#define	NODE_IS_LGTPNT	10

#define	POLY_IS_POLY			10
#define	POLY_IS_TRI_MESH		11
#define	POLY_IS_TRI_FAN			12
#define POLY_IS_QUAD_STRIP		13
#define	POLY_IS_INDEXED_POLY	14
#define	POLY_IS_LGTPNT			15

#define	VTX_MASK_COLOR			0x00000010
#define	VTX_MASK_NORM			0x00000008
#define	VTX_MASK_ST				0x00000004
#define	VTX_MASK_ST1			0x00000002
#define	VTX_MASK_VTX			0x00000001

#define	TOD_HIDE_ON_DAY			0x00000001
#define	TOD_HIDE_ON_DUSK		0x00000002
#define	TOD_HIDE_ON_DARK		0x00000004

struct	GEO_BUFF
{
	char			workingDirectory[256];

	int				nofHeaderNode;
	NODE_HEADER*	headerNode;

	int				nofExtRefNode;
	NODE_EXTREF*	extRefNode;
	
	int				nofGroupNode;
	NODE_GROUP*		groupNode;

	int				nofLODNode;
	NODE_LOD*		lodNode;
	
	int				nofDOFNode;
	NODE_DOF*		dofNode;

	int				nofBSPNode;
	NODE_BSP*		bspNode;
	
	int				nofObjNode;
	NODE_OBJ*		objNode;

	int				nofSwitchNode;
	NODE_SWITCH*	switchNode;

	int				nofMesh;
	MESH*			mesh;

	int				nofLgtPnt;
	LGTPNT*			lgtPnt;

	int				nofVtxCombo;
	VTXCOMBO*		vtxCombo;

	int				nofVtxLgt;
	VTXLGT*			vtxLgt;

	int				defaultMatID;

	int				nofMaterial;
	MATLIST*		matList;

	int				nofTexture;
	TEXLIST*		texList;

	int				noflpApprList;
	LPAPPR_LIST*	lpApprList;

	int				noflpAnimList;
	LPANIM_LIST*	lpAnimList;

	int				maxTransPoly;			// max nofTranspoly
	int				nofTransPoly;
	TRANSPOLY*		transPoly;

	int				maxTransVtxCombo;
	int				nofTransVtxCombo;
	VTXCOMBO*		transVtxCombo;

/*	int				first;
	double			xmin, xmax;
	double			ymin, ymax;
	double			zmin, zmax;
*/
};

#ifndef	_SIXDOF_
#define	_SIXDOF_
struct	SIXDOF
{
	double		x, y, z;
	double		az, in, tw;
};
#endif

#ifndef _AIRPORT_
#define	_AIRPORT_

struct AIRPORT
{
	double		xlat[3];
	double		rotZ;
	double		scale[3];

	char		dbName[256];
	char		dbFileName[256];
	char		path[256];

	// ------------ PAPI will be added by LgtPnt -------------
	int			nofPAPI;
	EXTDEF_LGT	papi[64];			// max four papi system per fltDB

	// ------------ REIL will be added by group --------------
	int			nofReilNode;
	EXTDEF_LGT	reilGroupProp[8];

	// ------------ STROBE will be added by group --------------
	int			nofStrobeNode;
	EXTDEF_LGT	strobeGroupProp[8];

	// ------------ intensity control --------------
	int			nofRwyLgtApperance;
	int			rwyLgtAppearance[32];

	int			nofApproachLgtApperance;
	int			approachLgtAppearance[32];
	
	int			nofTaxiwayLgtApperance;
	int			taxiwayLgtAppearance[32];

	// ----------- ground Color ---------------------
	float		gndColor[4][3];

	// ----------- Runway group ---------------------
	int			nofRwyGroup;
	char		rwyGroupName[10][64];
	NODE*		rwyGroupNodePtr[10];

	double		landingLgtSizeX;
	double		landingLgtSizeY;

	double		landingLgtCoeff1;
	double		landingLgtCoeff2;
};

#endif

#ifndef _TIMEOFDAY_
#define	_TIMEOFDAY_

struct	TIMEOFDAY
{
	char	todName[64];
	int		localLight;
	float	lightColor[9];
	int		airplaneLocalLight;
	float	airplaneLightColor[9];
	int		lightBoundID;

	int		localViewer;
	float	lmodelColor[3];
	int		lmodelBoundID;

	float	lightAz;
	float	lightIn;

	int		fogEnabled;				// 1 : enabled
	int		fogMode;				// GL_LINEAR, GL_EXP, and GL_EXP2
	float	fogColor[3];
	float	fogVisibility;
	float	fogDensity;

	char	skyTexFileName1[64];
	int		skyTexID1;
	char	skyTexFileName2[64];
	int		skyTexID2;
	double	buttom;
	double	top;
	float	cloudWallColor[3];
	float	skyColor[3];
//	float	gndColor[3];			// 공항 마다 달라야 하므로 AIRPORT로 옮김
};
#endif

typedef		int	(*FUNC_PROC)( NODE* np );


class Model : public Material, public Texture, public LightPoint
{
private:
	int*			m_renderFlag;
	int*			m_oneShotFlag;
	int*			m_prevMatID;
	int*			m_prevMultiMatID;
	int*			m_prevTexID;
	int*			m_prevMultiTexID;
	int*			m_dispSW;
	int*			m_currentTimeOfDay;
	double*			m_timeElapsed;
	TIMEOFDAY*		m_timeOfDay;

// Rendering control var.
	NODE*			m_nodeStack[30];
	int				m_nodeSP;
	double			m_FOV;
	eGL				m_MVM;

// GEO_BUFF .................................................. <bgn>
	int				m_nofHeaderNode;
	NODE_HEADER*	m_headerNode;

	int				m_nofExtRefNode;
	NODE_EXTREF*	m_extRefNode;

	int				m_nofGroupNode;
	NODE_GROUP*		m_groupNode;

	int				m_nofLODNode;
	NODE_LOD*		m_lodNode;

	int				m_nofDOFNode;
	NODE_DOF*		m_dofNode;

	int				m_nofBSPNode;
	NODE_BSP*		m_bspNode;

	int				m_nofObjNode;
	NODE_OBJ*		m_objNode;

	int				m_nofSwitchNode;
	NODE_SWITCH*	m_switchNode;

	int				m_nofMesh;
	MESH*			m_mesh;

	int				m_nofLgtPnt;
	LGTPNT*			m_lgtPnt;

	int				m_nofVtxCombo;
	VTXCOMBO*		m_vtxCombo;

	int				m_nofVtxLgt;
	VTXLGT*			m_vtxLgt;

	int				m_defaultMatID;

	int				m_nofMaterial;
	MATLIST*		m_matList;

	int				m_nofTexture;
	TEXLIST*		m_texList;

	int				m_noflpApprList;
	LPAPPR_LIST*	m_lpApprList;

	int				m_noflpAnimList;
	LPANIM_LIST*	m_lpAnimList;

	int				m_maxTransPoly;			// max nofTranspoly
	int				m_nofTransPoly;			// max nofTranspoly
	TRANSPOLY*		m_transPoly;

	int				m_maxTransVtxCombo;
	int				m_nofTransVtxCombo;
	VTXCOMBO*		m_transVtxCombo;

// GEO_BUFF .................................................. <end>

	LGTPNT**		m_lgtPntVisible;

	double*			m_modelEyePos;
	AIRPORT*		m_modelAirport;

	int				m_nofTranSort;
	int				m_maxTranSort;
	TRANSORT*		m_tranSort;
	unsigned int*	m_tranSortKey;		// 거리
	int*			m_tranSortIdx;		// index for reference of TRANSORT

	SIXDOF			m_viewFrustum6DOF;

	//............. Fwrd Culling Frustum ..............
	float			m_cullPlaneCoeff[5][4];

	FUNC_PROC		m_traverseCallBack;

	//............. Runtime variables .................
	float			m_defaltLgtPntIntensity;			// 0.2, 0.4, 0.6, 0.8, 1.0	(5개의 대표값)
	float			m_approachLgtIntersity;
	float			m_rwyLgtIntersity;
	float			m_taxiwayLgtIntersity;

	int				m_reilLgtSW;
	int				m_papiSW;
	int				m_strobeSW;	

	int				m_lgtTexID;

public:
	int				m_nofRenderedPolygon;
	int				m_nofRenderedMesh;
	int				m_nofRenderedMultiTexMesh;
	int				m_nofRenderedLightPoint;
	int				m_nofSwInLOD;
	int				m_nofSwOutLOD;
	int				m_nofVisibleGroup;

	int				m_nofRenderedLgtPnt;

public:
	Model();
	~Model();

	void	ClearPolyCount();
	int		RenderModel( NODE* np, int nodeSP = 0, int nodeStatus = 0 );
	int		TraverseModel( NODE* np, int nodeSP = 0, int nodeStatus = 0 );
	void	RenderMultiTexturedPolygon( int polyNo, VTXCOMBO* vc );

	void	RenderTransparentPolygon();
	void	RenderCircle( float x, float y, float z, float r1, float* colorPtr );
	int		NofTransparentPolygon()		{ return m_nofTransPoly; }

	void	PolygonSWHandler( unsigned int renderXorFlag, unsigned int renderFlag );
	void	RenderMesh( int glMeshType, MESH* mp, VTXCOMBO* vc = NULL );
	void	RenderTransMesh( int glMeshType, MESH* mp, VTXCOMBO* vc = NULL );
	void	RenderLightPoints();
	void	RenderTexturedLight( double* pos, float size, int texID );

	void	SetGeoBuffer( GEO_BUFF* geoBuffPtr );
	void	SetDefaultMaterial( int defaultMaterial )		{ m_defaultMatID = defaultMaterial; }
	void	SetLgtTexID( int texID )						{ m_lgtTexID = texID; }
	
	void	SetConrolSW( int* renderFlag, int* oneShotFlag, int* prevMatID, int* prevTexID, int* prevMultiTexID, int* dispSW, int* currentTimeOfDay, TIMEOFDAY* todPtr, double* timeElapsed );
	void	SetEyePos( double* pos )		{ m_modelEyePos = pos; }
	double*	GetEysPos()						{ return m_modelEyePos; }

	void	SetAirportXform( AIRPORT* ap )			{ m_modelAirport = ap; }
	void	SetLgtPntIntensity( int categoryID, float intensity );
	void	SetLgtPntSwitch( int swbit, bool swVal );
	int		IsLgtPntSwitchOn( int swbit );

	NODE*	FindNode( char* nodeName, int nodeType = -1 );
	NODE*	GetNodeID( char* nodeName, int nodeType, int nofList, NODE* nodeList );

	void	SetTraverseCallbackFunc( FUNC_PROC funcPtr )		{ m_traverseCallBack = funcPtr; }

	float*	GetCullPlaneCoeffBuff()								{ return (float*)m_cullPlaneCoeff; }
	int		TestBV( NODE* np );
	void	RenderBV( int depth, char* name = NULL );
	
	void	WriteInsideLandingLightRegion();
	void	WriteOutSideLandingLightRegion();
	void	DisableLandingLightResion();
	void	MakeLandingLightHole();
};
/*
extern	PFNGLMULTITEXCOORD1FARBPROC			glMultiTexCoord1fARB;
extern	PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
extern	PFNGLMULTITEXCOORD3FARBPROC			glMultiTexCoord3fARB;
extern	PFNGLMULTITEXCOORD4FARBPROC			glMultiTexCoord4fARB;
extern	PFNGLMULTITEXCOORD1FVARBPROC		glMultiTexCoord1fvARB;
extern	PFNGLMULTITEXCOORD2FVARBPROC		glMultiTexCoord2fvARB;
extern	PFNGLMULTITEXCOORD3FVARBPROC		glMultiTexCoord3fvARB;
extern	PFNGLMULTITEXCOORD4FVARBPROC		glMultiTexCoord4fvARB;
extern	PFNGLMULTITEXCOORD1DARBPROC			glMultiTexCoord1dARB;
extern	PFNGLMULTITEXCOORD2DARBPROC			glMultiTexCoord2dARB;
extern	PFNGLMULTITEXCOORD3DARBPROC			glMultiTexCoord3dARB;
extern	PFNGLMULTITEXCOORD4DARBPROC			glMultiTexCoord4dARB;
extern	PFNGLMULTITEXCOORD1DVARBPROC		glMultiTexCoord1dvARB;
extern	PFNGLMULTITEXCOORD2DVARBPROC		glMultiTexCoord2dvARB;
extern	PFNGLMULTITEXCOORD3DVARBPROC		glMultiTexCoord3dvARB;
extern	PFNGLMULTITEXCOORD4DVARBPROC		glMultiTexCoord4dvARB;
extern	PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;
extern	PFNGLCLIENTACTIVETEXTUREARBPROC		glClientActiveTextureARB;
*/
//////////////////////////////////////////////////////////////////////

#endif // !defined(_XR_MODEL_H_INCLUDED_)
