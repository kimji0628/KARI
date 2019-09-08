#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <mgapiall.h>

#include "FileName.h"
#include "Model.h"
#include "eGL.h"

#if !defined(_DBASE_H_INCLUDED_)
#define _DBASE_H_INCLUDED_

struct	CODENAME
{
	int				codeVal;
	char*			codeName;
	int				codeKnown;
};

struct	EXTREF_LIST
{
	mgrec*			dbRec;
	char			extRefName[256];
	char			extRefFileName[256];
};

#define	MAX_STACK_DEPTH		50

struct	FLT_STACK
{
	mgrec*			extRefRec;
	int				extRefNo;
	char			extRefPath[256];
	char			extRefFileName[256];
	char			extRefName[256];
};

class	DBase
{
private:
	char			m_dbName[64];
	char			m_dbFilename[256];
	char			m_dbPath[256];

	int				m_SP;
	FLT_STACK		m_stack[MAX_STACK_DEPTH];
	AIRPORT*		m_apUnderLoading;

	mgrec*			m_flt;
	mgrec*			m_currentFlt;
	int				m_currentExtRefNo;

	int				m_maxNofExtRef;
	int				m_nofExtRefList;
	EXTREF_LIST*	m_extRefList;
	GEO_BUFF		m_geoBuff;

	double*			m_dbEyePos;

	FileName		m_extRefName;

	eGL				m_xFormMVM;
	eGL				m_rotMVM;

public:
	DBase();
	~DBase();

	int				LoadDB( char* dbName, char* dbFileName, char* path,  char* workingDirectory, AIRPORT* ap );
	int				SaveDB( char* dbName, char* dbFileName, char* workingDirectory );

	void			PrintNode( mgrec* node, int num_tabs );
	int				PrintMaterialPalette (mgrec *db);
	int				PrintTexturePalette (mgrec *db);
	int				PrintLPAppearancePalette (mgrec *db, char* dbName);
	int				PrintLPAnimationPalette (mgrec *db, char* dbName );
	int				Code2Idx( mgrec* thisnode );

	void			TraverseDB( mgrec *node );
	void			ReadDB( mgrec *node, int parentStatus, NODE* np = NULL );
	int				GetLgtGroupType( char* recName, int& groupID );
	int				AllocGeoBuff( GEO_BUFF* gp, int maxTransPoly = 1000, int maxTransVtxCombo = 5000 );
	void			FreeGeoBuff();
	void*			CreateNode( int nodeType );
	void			ReadXforms( mgrec *node, NODE* thisNode, char* nodeName = NULL);

	NODE*			CompleteNodeField( mgrec* thisnode, NODE* parentNode, int thisIsLgtPntGroup, int lgtGroupID, float* dimension );

	MESH*			AddMesh();
	LGTPNT*			AddLgtPnt();

	VTXCOMBO*		AddVertex( MESH* mp );
	VTXLGT*			AddVertexLgt( LGTPNT* lp );

	void			ReadMaterial(mgrec *db, mgrec *mat, int index);
	mgbool			ReadMaterialPalette(mgrec *db);
	mgbool			ReadTexturePalette(mgrec *db );
	int				ReadLPApprPalette(mgrec *db );
	int				ReadLPAnimPalette(mgrec *db );

	MATLIST*		AddMaterialList();
	TEXLIST*		AddTextureList();
	LPAPPR_LIST*	AddLPAppearList();
	LPANIM_LIST*	AddLPAnimList();

	int				BoundMatID( int extRefID, int matNo );
	int				BoundTexID( int extRefID, int texNo );
	TEXLIST*		TexList( int extRefID, int texNo );
	LGTPNT_APPEAR*	BoundLPApprID( int extRefID, int lpApprNo );
	LGTPNT_ANIM*	BoundLPAnimID( int extRefID, int lpAnimNo );
//	void			CalcPlaneCoeff( double* vtx, float* norm, double foh, double fov, LGTPNT* lp );
	void			CalcPlaneCoeff( VTXLGT* vc, LGTPNT* lp );

	GEO_BUFF*		GeoBuff()			{ return &m_geoBuff; }
	char*			DBName()			{ return m_dbName; }
	mgrec*			GetDBRoot()			{ return m_flt; }
	
	void			LinkMatAndTexID();
	void			LinkLPApprAndLPAnim();
	int				GetIntensityCtrlGroupID( int lpApprNo );

	int				ExtRefName2ID( char* name );
	int				AddExtRefName( char* name, mgrec* thisrec );

	void			PushFltStack( mgrec* extRefRec, int extRefNo, char* extRefFileName, char* extRefName );
	void			PopFltStack( mgrec** extRefRec, int& extRefNo, char* extRefFileName, char* extRefName );

	void			SetEyePos( double* eyePos );
	void			PrintNodeLinkage( NODE* np, int nodeSP = 0, int nodeStatus = 0 );
	void			CalcConvexNormal( double* v0, double* v1, double* v2, double* v );

};

#endif		// _DBASE_H_INCLUDED_
