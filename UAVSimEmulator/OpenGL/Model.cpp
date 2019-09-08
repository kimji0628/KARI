/*
	REIL.STRB size는 cfg에서 조절 가능
*/

#include "stdafx.h"
#include "Canvas.h""
#include "Model.h"

float	swInColor[3]	= { 1.0, 1.0, 0.0 };
float	swOutColor[3]	= { 1.0, 0.0, 1.0 };

Model::Model()
{
	m_lgtPntVisible	= NULL;
}

Model::~Model()
{
	if ( m_lgtPntVisible )
		free( m_lgtPntVisible );
}

void
Model::ClearPolyCount()
{
	m_nofRenderedPolygon		= 0;
	m_nofRenderedMesh			= 0;
	m_nofRenderedLightPoint		= 0;
	m_nofRenderedLgtPnt			= 0;
	m_nofRenderedMultiTexMesh	= 0;
}

int
Model::RenderModel( NODE* np, int nodeSP, int nodeStatus )
{
	NODE_HEADER*	nhp;
	NODE_GROUP*		ngp;
	NODE_LOD*		nlp;
	NODE_DOF*		ndp;
	NODE_BSP*		nbp;
	NODE_OBJ*		nop;
	NODE_SWITCH*	nsp;
	NODE*			tmpNp;

	int				i;
	double			dx, dy, dz, len;

	static double	eyePos[3];

	if ( nodeSP == 0 )
	{
		glEnable( GL_LIGHT0 );
//		glEnable( GL_NORMALIZE );

		glEnable( GL_LIGHTING );
		glEnable( GL_TEXTURE_2D );

		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );

		glDisable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//		glBlendFunc( GL_SRC_COLOR, GL_ONE );
		glHint( GL_POINT_SMOOTH_HINT, GL_DONT_CARE );

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		*m_renderFlag	= PROP_TEXTURED | PROP_LIGHTED;

		glCallList( m_defaultMatID );
		*m_prevMatID		= -1;
		*m_prevTexID		= -1;
		*m_prevMultiTexID	= -1;

		m_MVM.LoadIdentity();
		m_nodeSP = 0;

		m_nofSwInLOD				= 0;
		m_nofSwOutLOD				= 0;
		m_nofVisibleGroup			= 0;

		m_nofTransPoly				= 0;
		m_nofTransVtxCombo			= 0;

		for ( int i = 0; i < m_nofMesh; i++ )
			m_mesh[i].rendered = false;

		for ( i = 0; i < m_nofLgtPnt; i++ )
			m_lgtPnt[i].rendered = false;

		eGL	tmpGL;

		if ( m_modelAirport )
		{
			tmpGL.LoadIdentity();
			tmpGL.Rotated( -m_modelAirport->rotZ, 'z' );
			tmpGL.Translated( -m_modelAirport->xlat[0], -m_modelAirport->xlat[1], -m_modelAirport->xlat[2] );

			tmpGL.PassMVMdv( m_modelEyePos, eyePos );
		}
		else
		{
			memcpy( eyePos, m_modelEyePos, sizeof(double)*3 );
		}
	}

	if ( !np )
		return NULL;

	// ========================== (( Opaque 1st Pass Render )) ==========================
	while( 1 )			// next sibling loop
	{
		if ( np->type != NODE_IS_MESH && np->type != NODE_IS_LGTPNT && np->nofXform ) //np->status & NODE_XFORMED )
		{
			glPushMatrix();

			for ( int i = 0; i < np->nofXform; i++ )
			{
				if ( np->xformType[i] == NODE_XLATED )
				{
					glTranslated( np->xlat[0], np->xlat[1], np->xlat[2] );
				}
				else if ( np->xformType[i] == NODE_ROTATED )
				{
					glTranslated( np->rotCenter[0], np->rotCenter[1], np->rotCenter[2] );
					glRotated( np->rot[0], np->rot[1], np->rot[2], np->rot[3] );
					glTranslated( -np->rotCenter[0], -np->rotCenter[1], -np->rotCenter[2] );
				}
				else if ( np->xformType[i] == NODE_SCALED )
				{
					glTranslated( np->scaleCenter[0], np->scaleCenter[1], np->scaleCenter[2] );
					glScaled( np->scale[0], np->scale[1], np->scale[2] );
					glTranslated( -np->scaleCenter[0], -np->scaleCenter[1], -np->scaleCenter[2] );
				}
			}
		}

		if ( np->status & NODE_LANDING_LIGHTED )
		{
			glGetDoublev( GL_MODELVIEW_MATRIX, (double*)np->xformMVM );
		}

		switch( np->type )
		{
		case NODE_IS_HEADER:
			nhp = (NODE_HEADER*)np;
			if ( np->child )
				RenderModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_EXTREF:
			ngp = (NODE_GROUP*)np;
			if ( np->child )
				RenderModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_GROUP:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			ngp = (NODE_GROUP*)np;
			m_nofVisibleGroup++;

			if ( np->child )
				RenderModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_LOD:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			nlp = (NODE_LOD*)np;

			dx = nlp->cx - m_modelEyePos[0];
			dy = nlp->cy - m_modelEyePos[1];
			dz = nlp->cz - m_modelEyePos[2];

			len = (float)sqrt( dx*dx + dy*dy + dz*dz );			// lod node중심 까지의 거리

			if ( *m_oneShotFlag )
			{
				cLog.Log( "LOD %s : (%.2f ~ %.2f) len = %.2f\n", nlp->linkname, nlp->swIn, nlp->swOut, len );
			}
			
			if ( *m_dispSW & DISP_LOD_CIRCLE )
				RenderCircle( nlp->cx, nlp->cy, nlp->cz, nlp->swIn+2.0f, swInColor );

			if ( !( *m_dispSW & DISP_ALL_LOD ) )
			if ( nlp->swIn < len || nlp->swOut > len ) 		// lod descendants를 그리지 않는다.
			{
				m_nofSwOutLOD++;
				break;
			}

			if ( *m_dispSW & DISP_LOD_CIRCLE )
				RenderCircle( nlp->cx, nlp->cy, nlp->cz, nlp->swOut+2.0f, swOutColor );

			m_nofSwInLOD++;
				
			RenderModel( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_DOF:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			ndp = (NODE_DOF*)np;

			glPushMatrix();
			m_MVM.PushMatrix();

			if ( ndp->xlatOn )
			{
				glTranslated(		ndp->dofXlat[0] + ndp->dofXlatNorm[0] * ndp->dofXlatInc * ndp->dofFrame,
									ndp->dofXlat[1] + ndp->dofXlatNorm[1] * ndp->dofXlatInc * ndp->dofFrame,
									ndp->dofXlat[2] + ndp->dofXlatNorm[2] * ndp->dofXlatInc * ndp->dofFrame );
				m_MVM.Translated(	ndp->dofXlat[0] + ndp->dofXlatNorm[0] * ndp->dofXlatInc * ndp->dofFrame,
									ndp->dofXlat[1] + ndp->dofXlatNorm[1] * ndp->dofXlatInc * ndp->dofFrame,
									ndp->dofXlat[2] + ndp->dofXlatNorm[2] * ndp->dofXlatInc * ndp->dofFrame );
			}

			if ( ndp->rotOn )
			{
				glTranslated(		ndp->dofRotCenter[0], ndp->dofRotCenter[1], ndp->dofRotCenter[2] );
				m_MVM.Translated(	ndp->dofRotCenter[0], ndp->dofRotCenter[1], ndp->dofRotCenter[2] );

				glRotated(			ndp->dofRotAngle + ndp->dofRotInc * ndp->dofFrame, ndp->dofRotNorm[0], ndp->dofRotNorm[1], ndp->dofRotNorm[2] );
				m_MVM.RotAxisd(		ndp->dofRotAngle + ndp->dofRotInc * ndp->dofFrame, ndp->dofRotNorm[0], ndp->dofRotNorm[1], ndp->dofRotNorm[2] );

				glTranslated(		-ndp->dofRotCenter[0], -ndp->dofRotCenter[1], -ndp->dofRotCenter[2] );
				m_MVM.Translated(	-ndp->dofRotCenter[0], -ndp->dofRotCenter[1], -ndp->dofRotCenter[2] );
			}

//			glScaled(			ndp->dofScale[0], ndp->dofScale[1], ndp->dofScale[2] );
//			m_MVM.Scaled(		ndp->dofScale[0], ndp->dofScale[1], ndp->dofScale[2] );

			RenderModel( (NODE*)np->child, nodeSP+1 );

			m_MVM.PopMatrix();
			glPopMatrix();

			break;

		case NODE_IS_BSP:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			nbp = (NODE_BSP*)np;

			len = nbp->a * m_modelEyePos[0]
				+ nbp->b * m_modelEyePos[1]
				+ nbp->c * m_modelEyePos[2]
				+ nbp->d;

			if ( len < 0.0 )
			{
				RenderModel( (NODE*)np->child, nodeSP+1, NODE_CHILD_OF_BSP );
			}
			else
			{
				tmpNp	= (NODE*)np->child;
				tmpNp	= (NODE*)tmpNp->right;
				tmpNp	= (NODE*)tmpNp->right;

				RenderModel( (NODE*)( ( (np->child)->right)->right), nodeSP+1, NODE_CHILD_OF_BSP | NODE_REV_DIRECTION );
			}

			break;

		case NODE_IS_SWITCH:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			nsp		= (NODE_SWITCH*)np;
			tmpNp	= (NODE*)np->child;

			for ( i = 0; i < nsp->currentMask; i++ )
			{
				tmpNp	= (NODE*)tmpNp->right;
			}

			RenderModel( tmpNp, nodeSP+1, NODE_CHILD_OF_SWITCH );

			break;

		case NODE_IS_OBJ:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			nop = (NODE_OBJ*)np;

			if ( *m_currentTimeOfDay == 1 && nop->todSW & TOD_HIDE_ON_DAY )				// day
					break;
			else if ( (*m_currentTimeOfDay == 2 || *m_currentTimeOfDay == 0 ) && nop->todSW & TOD_HIDE_ON_DUSK )		// dusk
					break;
			else if ( *m_currentTimeOfDay == 3 && nop->todSW & TOD_HIDE_ON_DARK )		// night
					break;

			if ( !( nop->todSW & TOD_HIDE_ON_DAY ) )
				RenderModel( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_MESH:
			if ( *m_dispSW & BV_TEST && !TestBV(np) )
				break;

			if ( !( nodeStatus & NODE_CHILD_OF_BSP ) || *m_dispSW & DISP_BSP_PLANE )
			{
				RenderMesh( GL_POLYGON, (MESH*)np );
				m_nofRenderedPolygon++;
			}
			break;

		case NODE_IS_LGTPNT:
			m_lgtPntVisible[m_nofRenderedLightPoint++]	= (LGTPNT*)np;
			break;
		}

		if ( np->status & NODE_XFORMED )
			glPopMatrix();

		if ( nodeStatus & NODE_CHILD_OF_SWITCH )
			return NULL;

		if ( nodeStatus & NODE_REV_DIRECTION )
			np = (NODE*)np->left;
		else
			np = (NODE*)np->right;

		if ( !np )
			return NULL;
	}

	return NULL;
}

int
Model::TestBV( NODE* np )
{
	float*	bv		= np->bv;
	float*	coeff	= (float*)m_cullPlaneCoeff;

	//............ BV test ..............
	if ( coeff[0]*bv[0] + coeff[1]*bv[1] + coeff[2]*bv[2] +coeff[3] > bv[3] )
	{
		return false;
	}
	else if ( coeff[4]*bv[0] + coeff[5]*bv[1] + coeff[6]*bv[2] +coeff[7] > bv[3] )
	{
		return false;
	}
	else if ( coeff[8]*bv[0] + coeff[9]*bv[1] + coeff[10]*bv[2] +coeff[11] > bv[3] )
	{
		return false;
	}
	else if ( coeff[12]*bv[0] + coeff[13]*bv[1] + coeff[14]*bv[2] +coeff[15] > bv[3] )
	{
		return false;
	}
	else if ( coeff[16]*bv[0] + coeff[17]*bv[1] + coeff[18]*bv[2] +coeff[19] > bv[3] )
	{
		return false;
	}

	return true;
}

void
Model::RenderMesh( int glMeshType, MESH* mp, VTXCOMBO* vc )
{
	int				v;
	unsigned int	renderFlag, renderXorFlag;
	int				multiTexturedPolyExist;

	if ( mp->rendered )
	{
		cLog.LogExit( "Duplicated render!\n" );
	}

	mp->rendered	= true;

	renderFlag = mp->renderFlag;

	//++++++++++++++ Opaque or Opaque_MultiTextured polygon +++++++++++++++++
	if ( !( renderFlag & PROP_TRANSPARENT ) )
	{
		if ( renderFlag & PROP_MULTI_TEXTURED )
			multiTexturedPolyExist = true;

		renderXorFlag = ( *m_renderFlag ^ renderFlag ) & ~( PROP_MULTI_TEXTURED1 | PROP_MULTI_BLEND_ADD | PROP_MULTI_LIGHTED | PROP_MULTI_REFLECTIVE );

		if ( *m_oneShotFlag )
		{
			cLog.Log( "Mesh %s: renderFlag %X xor=%X\n", mp->linkname, renderFlag, renderXorFlag );
		}

		if ( renderXorFlag )
			PolygonSWHandler( renderXorFlag, renderFlag );	// rendering environment setting

		if ( !vc )
			vc	= (VTXCOMBO*)mp->vtxLink;

		switch( ( renderFlag & (PROP_MULTI_TEXTURED|PROP_TEXTURED|PROP_LIGHTED) ) )
		{
		case PROP_TEXTURED | PROP_MULTI_TEXTURED | PROP_LIGHTED:		// shaded multi-textured 
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable( GL_TEXTURE_2D );
			if ( *m_oneShotFlag )
			{
				cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
			}

			if ( mp->matID != *m_prevMatID )
			{
				if ( mp->matID == -1 )
				{
					::glCallList( m_defaultMatID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
					*m_prevMatID = mp->matID;
				}
				else
				{
					::glCallList( mp->matID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
					*m_prevMatID = mp->matID;
				}
			}

			if ( mp->texID != *m_prevTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevTexID = mp->texID;
				}
			}

			if ( mp->texID1 != *m_prevMultiTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID1 );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex1: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevMultiTexID = mp->texID1;

//					glActiveTextureARB(GL_TEXTURE0_ARB);
				}
			}

			glBegin( glMeshType );

			for ( v = 0; v < mp->nofVtx; v++, vc++ )
			{
				glNormal3fv( vc->norm );
				glMultiTexCoord2dARB( GL_TEXTURE0_ARB,  vc->st[0], 1.0 - vc->st[1] );
				glMultiTexCoord2dARB( GL_TEXTURE1_ARB,  vc->st1[0], 1.0 - vc->st1[1] );
				glVertex3dv( vc->vtx );
			}

			glEnd();

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable( GL_TEXTURE_2D );
			glActiveTextureARB(GL_TEXTURE0_ARB);

			m_nofRenderedMultiTexMesh++;
			break;

		case PROP_TEXTURED | PROP_MULTI_TEXTURED:		// shaded multi-textured 
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable( GL_TEXTURE_2D );

			if ( *m_oneShotFlag )
			{
				cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
			}

			if ( mp->texID != *m_prevTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevTexID = mp->texID;
				}
			}

			if ( mp->texID1 != *m_prevMultiTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID1 );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex1: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevMultiTexID = mp->texID1;
//					glActiveTextureARB(GL_TEXTURE0_ARB);
				}
			}

			glColor3ubv( mp->primeColor );

			glBegin( glMeshType );

			for ( v = 0; v < mp->nofVtx; v++, vc++ )
			{
//				glNormal3fv( vc->norm );
				glMultiTexCoord2dARB( GL_TEXTURE0_ARB,  vc->st[0], 1.0 - vc->st[1] );
				glMultiTexCoord2dARB( GL_TEXTURE1_ARB,  vc->st1[0], 1.0 - vc->st1[1] );
				glVertex3dv( vc->vtx );
			}

			glEnd();

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable( GL_TEXTURE_2D );
			glActiveTextureARB(GL_TEXTURE0_ARB);

			m_nofRenderedMultiTexMesh++;
			break;

		case PROP_TEXTURED|PROP_LIGHTED:		// shaded textured
			if ( *m_renderFlag & PROP_MULTI_TEXTURED )
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glDisable( GL_TEXTURE_2D );
				*m_renderFlag &= ~PROP_MULTI_TEXTURED;
			}

			if ( *m_oneShotFlag )
			{
				cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
			}

			if ( mp->matID != *m_prevMatID )
			{
				if ( mp->matID == -1 )
				{
					::glCallList( m_defaultMatID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
					*m_prevMatID = mp->matID;
				}
				else
				{
					::glCallList( mp->matID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
					*m_prevMatID = mp->matID;
				}
			}

			if ( !(*m_renderFlag & PROP_LIGHTED ) )
			{
				glEnable( GL_LIGHTING );
				*m_renderFlag |= PROP_LIGHTED;
			}

			if ( mp->texID != *m_prevTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevTexID = mp->texID;
				}
			}

			glBegin( glMeshType );

			if ( mp->nofVtx == 3 )
			{
				glNormal3fv( vc->norm );
				glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
				glVertex3dv( vc->vtx );
				vc++;

				glNormal3fv( vc->norm );
				glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
				glVertex3dv( vc->vtx );
				vc++;

				glNormal3fv( vc->norm );
				glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
				glVertex3dv( vc->vtx );
				vc++;
			}
			else
			{
				for ( v = 0; v < mp->nofVtx; v++, vc++ )
				{
					glNormal3fv( vc->norm );
					glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
					glVertex3dv( vc->vtx );
				}
			}

			glEnd();
			break;

		case PROP_TEXTURED:		// colored textured
			if ( mp->texID != *m_prevTexID )
			{
				if ( mp->texID >= 0 )
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(  GL_TEXTURE_2D, mp->texID );

					if ( *m_oneShotFlag )
						cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevTexID = mp->texID;
				}
			}

			glColor3ubv( mp->primeColor );

			glBegin( glMeshType );

			for ( v = 0; v < mp->nofVtx; v++, vc++ )
			{
				glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
				glVertex3dv( vc->vtx );
			}

			glEnd();
			break;

		case PROP_LIGHTED:		// colored textured
			if ( mp->matID != *m_prevMatID )
			{
				if ( mp->matID == -1 )
				{
					::glCallList( m_defaultMatID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
					*m_prevMatID = mp->matID;
				}
				else
				{
					::glCallList( mp->matID );
					if ( *m_oneShotFlag )
						cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
					*m_prevMatID = mp->matID;
				}
			}

			glBegin( glMeshType );

			for ( v = 0; v < mp->nofVtx; v++, vc++ )
			{
				glNormal3fv( vc->norm );
				glVertex3dv( vc->vtx );
			}

			glEnd();
			break;

		case 0:						// colored only
			glColor3ubv( mp->primeColor );

			glBegin( glMeshType );

			for ( v = 0; v < mp->nofVtx; v++, vc++ )
			{
				glVertex3dv( vc->vtx );
			}

			glEnd();
			break;

		default:
			cLog.LogExit( "Illegal renderFlag found!\n" );
		}
	}
	else				// transparent polygon
	{
		TRANSPOLY*		tp;

		tp		= m_transPoly + m_nofTransPoly++;

		tp->meshPtr		= mp;

		if ( *m_oneShotFlag )
		{
			cLog.Log( "TransPoly %s %X\n", mp->linkname, mp->renderFlag );
		}
	}
}

void
Model::RenderTransMesh( int glMeshType, MESH* mp, VTXCOMBO* vc )
{
	int				v;
	unsigned int	renderFlag, renderXorFlag;
	int				multiTexturedPolyExist;

	renderFlag = mp->renderFlag;
/*
	//++++++++++++++ Opaque or Opaque_MultiTextured polygon +++++++++++++++++
	if ( renderFlag & PROP_MULTI_TEXTURED )
		multiTexturedPolyExist = true;

	renderXorFlag = ( *m_renderFlag ^ renderFlag ) & ~( PROP_MULTI_TEXTURED1 | PROP_MULTI_BLEND_ADD | PROP_MULTI_LIGHTED | PROP_MULTI_REFLECTIVE );

	if ( *m_oneShotFlag )
	{
		cLog.Log( "Mesh %s: renderFlag %X xor=%X\n", mp->linkname, renderFlag, renderXorFlag );
	}

	if ( renderXorFlag )
		PolygonSWHandler( renderXorFlag, renderFlag );	// rendering environment setting
*/
	if ( !vc )
		vc	= (VTXCOMBO*)mp->vtxLink;

	switch( ( renderFlag & (PROP_MULTI_TEXTURED|PROP_TEXTURED|PROP_LIGHTED) ) )
	{
	case PROP_TEXTURED | PROP_MULTI_TEXTURED | PROP_LIGHTED:		// shaded multi-textured 
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable( GL_TEXTURE_2D );
		if ( *m_oneShotFlag )
		{
			cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
		}

		if ( mp->matID != *m_prevMatID )
		{
			if ( mp->matID == -1 )
			{
				::glCallList( m_defaultMatID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
				*m_prevMatID = mp->matID;
			}
			else
			{
				::glCallList( mp->matID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
				*m_prevMatID = mp->matID;
			}
		}

		if ( mp->texID != *m_prevTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
				*m_prevTexID = mp->texID;
			}
		}

		if ( mp->texID1 != *m_prevMultiTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID1 );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex1: %d->%d\n", *m_prevTexID, mp->texID );
				*m_prevMultiTexID = mp->texID1;

//					glActiveTextureARB(GL_TEXTURE0_ARB);
			}
		}

		glBegin( glMeshType );

		for ( v = 0; v < mp->nofVtx; v++, vc++ )
		{
			glNormal3fv( vc->norm );
			glMultiTexCoord2dARB( GL_TEXTURE0_ARB,  vc->st[0], 1.0 - vc->st[1] );
			glMultiTexCoord2dARB( GL_TEXTURE1_ARB,  vc->st1[0], 1.0 - vc->st1[1] );
			glVertex3dv( vc->vtx );
		}

		glEnd();
		break;

	case PROP_TEXTURED | PROP_MULTI_TEXTURED:		// shaded multi-textured 
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable( GL_TEXTURE_2D );

		if ( *m_oneShotFlag )
		{
			cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
		}

/*			if ( mp->matID != *m_prevMatID )
		{
			if ( mp->matID == -1 )
			{
				::glCallList( m_defaultMatID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
				*m_prevMatID = mp->matID;
			}
			else
			{
				::glCallList( mp->matID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
				*m_prevMatID = mp->matID;
			}
		}
*/
		if ( mp->texID != *m_prevTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
				*m_prevTexID = mp->texID;
			}
		}

		if ( mp->texID1 != *m_prevMultiTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID1 );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex1: %d->%d\n", *m_prevTexID, mp->texID );
					*m_prevMultiTexID = mp->texID1;
//					glActiveTextureARB(GL_TEXTURE0_ARB);
			}
		}

		glColor3ubv( mp->primeColor );

		glBegin( glMeshType );

		for ( v = 0; v < mp->nofVtx; v++, vc++ )
		{
//			glNormal3fv( vc->norm );
			glMultiTexCoord2dARB( GL_TEXTURE0_ARB,  vc->st[0], 1.0 - vc->st[1] );
			glMultiTexCoord2dARB( GL_TEXTURE1_ARB,  vc->st1[0], 1.0 - vc->st1[1] );
			glVertex3dv( vc->vtx );
		}

		glEnd();
		break;

	case PROP_TEXTURED|PROP_LIGHTED:		// shaded textured 
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable( GL_TEXTURE_2D );
		
		if ( *m_oneShotFlag )
		{
			cLog.Log( "Mesh  mat: %d  tex: %d\n", mp->matID, mp->texID );
		}

		if ( mp->matID != *m_prevMatID )
		{
			if ( mp->matID == -1 )
			{
				::glCallList( m_defaultMatID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->DefaultMat(%d)\n", *m_prevMatID, m_defaultMatID );
				*m_prevMatID = mp->matID;
			}
			else
			{
				::glCallList( mp->matID );
				if ( *m_oneShotFlag )
					cLog.Log( "Mat: %d->%d\n", *m_prevMatID, mp->matID );
				*m_prevMatID = mp->matID;
			}
		}

		if ( mp->texID != *m_prevTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
				*m_prevTexID = mp->texID;
			}
		}

		glBegin( glMeshType );

		for ( v = 0; v < mp->nofVtx; v++, vc++ )
		{
			glNormal3fv( vc->norm );
			glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
			glVertex3dv( vc->vtx );
		}

		glEnd();
		break;

	case PROP_TEXTURED:		// colored textured
		if ( mp->texID != *m_prevTexID )
		{
			if ( mp->texID >= 0 )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(  GL_TEXTURE_2D, mp->texID );

				if ( *m_oneShotFlag )
					cLog.Log( "Tex: %d->%d\n", *m_prevTexID, mp->texID );
				*m_prevTexID = mp->texID;
			}
		}

		glColor3ubv( mp->primeColor );

		glBegin( glMeshType );

		for ( v = 0; v < mp->nofVtx; v++, vc++ )
		{
			glTexCoord2d( vc->st[0], 1.0 - vc->st[1] );
			glVertex3dv( vc->vtx );
		}

		glEnd();
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//	RenderNode에서 polygon 단위로 불려지는 모듈 first pass rendering에 필요한 render 환경 설정
//	여기서 Setting하는 OpenGL Switch
//
//	1. GL_BLEND / GL_BLEND									glEnable(), glDisable()
//	2. GL_TEXTURE_GEN_S / GL_TEXTURE_GEN_T					glEnable(), glDisable()
//	3. GL_LIGHTING											glEnable(), glDisable()
//	4. ( GL_SRC_COLOR, GL_ONE )								glBlendFunc()
//	5. ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA )				glBlendFunc()
//	6. GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND		glTexEnvf()
//	7. GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE )	glTexEnvf()
//	8. GL_FLAT / GL_SMOOTH									glShadeModel()
//	9. GL_TEXTURE_2D										glEnable(), glDisable()
// 10. GL_DEPTH_TEST										glEnable(), glDisable()
// 11. GL_CULL_FACE											glEnable(), glDisable()
//
/////////////////////////////////////////////////////////////////////////////////////////////////
void
Model::PolygonSWHandler( unsigned int renderXorFlag, unsigned int renderFlag )
{
	// *m_renderFlag와 polygon의 renderFlag가 다를 경우
	// 즉 다시말해 renderXorFlag가 none Zero인 경우만 이모튤이 호출됨다.

	// --------------------( Trace render SW )---------------------
	if ( renderXorFlag & PROP_TRANSPARENT )
	{
		if ( renderFlag & PROP_TRANSPARENT )
		{
			if ( !( *m_renderFlag & PROP_TRANSPARENT ) )
			{
				glEnable( GL_BLEND );
				*m_renderFlag |= PROP_TRANSPARENT;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_TRANSPARENT )
			{
				glDisable( GL_BLEND );
				*m_renderFlag &= ~PROP_TRANSPARENT;
			}
		}
	}

	if ( renderXorFlag & PROP_REFLECTIVE )
	{
		if ( renderFlag & PROP_REFLECTIVE )
		{
			if ( !( *m_renderFlag & PROP_REFLECTIVE ) )
			{
				glEnable( GL_TEXTURE_GEN_S );
				glEnable( GL_TEXTURE_GEN_T );
				*m_renderFlag |= PROP_REFLECTIVE;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_REFLECTIVE )
			{
				glDisable( GL_TEXTURE_GEN_S );
				glDisable( GL_TEXTURE_GEN_T );
				*m_renderFlag &= ~PROP_REFLECTIVE;
			}
		}
	}

	if ( renderXorFlag & PROP_LIGHTED )
	{
		if ( renderFlag & PROP_LIGHTED )
		{
			if ( !( *m_renderFlag & PROP_LIGHTED ) )
			{
				glEnable( GL_LIGHTING );
				*m_renderFlag |= PROP_LIGHTED;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_LIGHTED )
			{
				glDisable( GL_LIGHTING );
				*m_renderFlag &= ~PROP_LIGHTED;
			}
		}
	}

	if ( renderXorFlag & PROP_BLEND_ADD )
	{
		if ( renderFlag & PROP_BLEND_ADD )
		{
			if ( !( *m_renderFlag & PROP_BLEND_ADD ) )
			{
				glBlendFunc( GL_SRC_COLOR, GL_ONE );
				*m_renderFlag |= PROP_BLEND_ADD;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_BLEND_ADD )
			{
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				*m_renderFlag &= ~PROP_BLEND_ADD;
			}
		}
	}

	if ( renderXorFlag & PROP_BLEND_TEV )
	{
		if ( renderFlag & PROP_BLEND_TEV )
		{
			if ( !( *m_renderFlag & PROP_BLEND_TEV ) )
			{
				glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
				*m_renderFlag |= PROP_BLEND_TEV;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_BLEND_TEV )
			{
				glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				*m_renderFlag &= ~PROP_BLEND_TEV;
			}
		}
	}

	if ( renderXorFlag & PROP_FLAT_SHADED )
	{
		if ( renderFlag & PROP_FLAT_SHADED )
		{
			if ( !( *m_renderFlag & PROP_FLAT_SHADED ) )
			{
				glShadeModel( GL_FLAT );
				*m_renderFlag |= PROP_FLAT_SHADED;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_FLAT_SHADED )
			{
				glShadeModel( GL_SMOOTH );
				*m_renderFlag &= ~PROP_FLAT_SHADED;
			}
		}
	}

	if ( renderXorFlag & PROP_TEXTURED )
	{
		if ( renderFlag & PROP_TEXTURED )
		{
			if ( !( *m_renderFlag & PROP_TEXTURED ) )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glEnable( GL_TEXTURE_2D );
				*m_renderFlag |= PROP_TEXTURED;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_TEXTURED )
			{
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glDisable( GL_TEXTURE_2D );
				*m_renderFlag &= ~PROP_TEXTURED;
			}
		}
	}

	if ( renderXorFlag & PROP_MULTI_TEXTURED )
	{
		if ( renderFlag & PROP_MULTI_TEXTURED )
		{
			if ( !( *m_renderFlag & PROP_MULTI_TEXTURED ) )
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glEnable( GL_TEXTURE_2D );

				*m_renderFlag |= PROP_TEXTURED;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_MULTI_TEXTURED )
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glDisable( GL_TEXTURE_2D );

				*m_renderFlag &= ~PROP_TEXTURED;
			}
		}
//		glActiveTextureARB(GL_TEXTURE0_ARB);
	}

	if ( renderXorFlag & PROP_ZBUFFER_OFF )
	{
		if ( renderFlag & PROP_ZBUFFER_OFF )	// zbuffer off polygon case
		{
			if ( !( *m_renderFlag & PROP_ZBUFFER_OFF ) )
			{
				glDisable( GL_DEPTH_TEST );
				*m_renderFlag |= PROP_ZBUFFER_OFF;
			}
		}
		else												// zbuffer on case
		{
			if ( *m_renderFlag & PROP_ZBUFFER_OFF )
			{
				glEnable( GL_DEPTH_TEST );
				*m_renderFlag &= ~PROP_ZBUFFER_OFF;
			}
		}
	}

	if ( renderXorFlag & PROP_TWO_SIDED )
	{
		if ( renderFlag & PROP_TWO_SIDED )
		{
			if ( !( *m_renderFlag & PROP_TWO_SIDED ) )
			{
				glDisable( GL_CULL_FACE );
				*m_renderFlag |= PROP_TWO_SIDED;
			}
		}
		else
		{
			if ( *m_renderFlag & PROP_TWO_SIDED )
			{
				glEnable( GL_CULL_FACE );
				*m_renderFlag &= ~PROP_TWO_SIDED;
			}
		}
	}

	if ( renderXorFlag & PROP_POINT_SMOOTH )				// PROP_POINT_SMOOTH 가 변화
	{
		if ( renderFlag & PROP_POINT_SMOOTH )				// PROP_POINT_SMOOTH 를 켜야되는데 
		{
			if ( !( *m_renderFlag & PROP_POINT_SMOOTH ) )	// 안 켜있으면
			{
				glEnable( GL_POINT_SMOOTH );				// 켜고
				glEnable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				*m_renderFlag |= ( PROP_POINT_SMOOTH | PROP_TRANSPARENT );		// 업데이트하고
				*m_renderFlag &= ~PROP_BLEND_ADD;
				glHint( GL_POINT_SMOOTH_HINT, GL_DONT_CARE );
			}
		}
		else												// 꺼야되는데
		{
			if ( *m_renderFlag & PROP_POINT_SMOOTH )		// 켜있으면
			{
				glDisable( GL_POINT_SMOOTH );				// 끈다
				glDisable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				glPointSize( 1.0f );
				*m_renderFlag &= ~( PROP_POINT_SMOOTH | PROP_TRANSPARENT | PROP_BLEND_ADD );		// 업데이트하고
			}
		}
	}
}

void
Model::RenderLightPoints()
{
	LGTPNT*			lp;
	LGTPNT**		lpp;
	int				v;
	unsigned int	renderFlag, renderXorFlag;
	int				multiTexturedPolyExist;
	double			ex, ey, ez;
	double			dx, dy, dz;
	VTXLGT*			vc;
	LGTPNT_APPEAR*	apprPtr;
	LGTPNT_ANIM*	animPtr;
	double			lightIntensity;
	float			lptSize, len;;
	BYTE			ubIntensity;
	double			clock;
	PLANE*			pp;
	EXTDEF_LGT*		extDefPtr;
	float			tmpLgtPntIntensity;

//	lpp		= m_lgtPntVisible;
//	for ( int l = 0; l < m_nofRenderedLightPoint; l++, lpp++ )
//	{
//		lp		= *lpp;

	lp = m_lgtPnt;
	for ( int l = 0; l < m_nofLgtPnt; l++, lp++ )
	{
		if ( lp->rendered )
		{
			cLog.LogExit( "Duplicated lgtpnt render!\n" );
		}

		lp->rendered	= true;

		apprPtr	= lp->apprPtr;

		if ( *m_currentTimeOfDay == 3 && apprPtr->lpTOD & TOD_HIDE_ON_DARK )		// night
				continue;
		else if ( (*m_currentTimeOfDay == 2 || *m_currentTimeOfDay == 0) && apprPtr->lpTOD & TOD_HIDE_ON_DUSK )		// dusk
				continue;
		else if ( *m_currentTimeOfDay == 1 && apprPtr->lpTOD & TOD_HIDE_ON_DAY )		// dusk
				continue;

		animPtr	= lp->animPtr;

		ex		= m_modelEyePos[0];
		ey		= m_modelEyePos[1];
		ez		= m_modelEyePos[2];

		renderFlag = lp->renderFlag;

		if ( renderFlag & PROP_MULTI_TEXTURED )
			multiTexturedPolyExist = true;

		renderXorFlag = ( *m_renderFlag ^ renderFlag ) & ~( PROP_MULTI_TEXTURED | PROP_MULTI_TEXTURED1 | PROP_MULTI_BLEND_ADD | PROP_MULTI_LIGHTED | PROP_MULTI_REFLECTIVE );

		if ( *m_oneShotFlag )
		{
			cLog.Log( "LgtPnt : renderFlag %X xor=%X\n", renderFlag, renderXorFlag );
		}

		if ( renderXorFlag )
			PolygonSWHandler( renderXorFlag, renderFlag );	// rendering environment setting

		vc	= (VTXLGT*)lp->vtxLink;

		for ( v = 0; v < lp->nofVtx; v++, vc++ )
		{
			dx	= vc->vtx[0] - ex;
			dy	= vc->vtx[1] - ey;
			dz	= vc->vtx[2] - ez;
			len	= (float)sqrt( dx*dx + dy*dy + dz*dz );					// 눈에서부터 거리

			switch( lp->lgtType )
			{
			case DEFAULT_LGT:										// not special light must be omni directional light
				if ( len > apprPtr->lpVisibilityRange )				// light point is too far away to render
					continue;

				if ( apprPtr->lpDirectionalityType )
				{
					cLog.LogExit( "Default light %s (appr %d) has directionality!\n", lp->linkname, lp->apprNo );
				}

/*				if ( animPtr )		// STROBE / REIL light On/Off animation ------------------------------
				{
					clock = fmod( *m_timeElapsed, animPtr->lpaPeriod * 1000 ) / 1000.0;
					if ( !( clock-animPtr->lpaTimeOn < animPtr->lpaPeriod - animPtr->lpaPhaseDelay && clock-animPtr->lpaTimeOn > animPtr->lpaPeriod - (animPtr->lpaPhaseDelay+animPtr->lpaTimeOn) ) )
						continue;
				}

				if ( len < 100.0 )
					len = len;

				lptSize = 2000.0f / len * apprPtr->lpActualPixelSize;

				if ( lptSize < apprPtr->lpMinPixelSize )
					lptSize = apprPtr->lpMinPixelSize;
				else if ( lptSize > apprPtr->lpMaxPixelSize )
					lptSize = apprPtr->lpMaxPixelSize;

				ubIntensity	= (BYTE)( 255 * m_defaltLgtPntIntensity );
*/
				// ---------- lightpoint size 결정 ----------------
				lptSize = 2000.0f / len * apprPtr->lpActualPixelSize;

				if ( lptSize < apprPtr->lpMinPixelSize )
					lptSize = apprPtr->lpMinPixelSize;
				else if ( lptSize > apprPtr->lpMaxPixelSize )
					lptSize = apprPtr->lpMaxPixelSize;

				if ( lp->lgtType & APPROACH_LGT )
					ubIntensity	= (BYTE)( 255 * m_approachLgtIntersity );
				else if ( lp->lgtType & RUNWAY_LGT )
					ubIntensity	= (BYTE)( 255 * m_rwyLgtIntersity );
				else if ( lp->lgtType & TAXIWAY_LGT )
					ubIntensity	= (BYTE)( 255 * m_taxiwayLgtIntersity );
				else
					ubIntensity	= 255;

				// ------------- Light rendering -------------------
				glPointSize( lptSize );
				glEnable( GL_BLEND );
				glColor4ub( vc->color[0], vc->color[1], vc->color[2], ubIntensity );

				if ( lp->lgtType == REIL_LGT )
				{
					RenderTexturedLight( vc->vtx, lptSize, m_lgtTexID );
				}
				else
				{
					glBegin( GL_POINTS );
						glVertex3dv( vc->vtx );
					glEnd();
				}

				m_nofRenderedLgtPnt++;
				break;

			case REIL_LGT:
				if ( animPtr )		// STROBE / REIL light On/Off animation ------------------------------
				{
					clock = fmod( *m_timeElapsed, animPtr->lpaPeriod * 1000 ) / 1000.0;
					if ( !( clock-animPtr->lpaTimeOn < animPtr->lpaPeriod - animPtr->lpaPhaseDelay && clock-animPtr->lpaTimeOn > animPtr->lpaPeriod - (animPtr->lpaPhaseDelay+animPtr->lpaTimeOn) ) )
						continue;
				}

				if ( !m_reilLgtSW )
					continue;

				extDefPtr = lp->extDefPtr;

				// ----------- 시계에 대한 On/Off test --------------
				if ( len > extDefPtr->visibility )					// light point is too far away to render
					continue;										// apprPtr->lpVisibilityRange 는 override 됨 

				// ----------- 방향성에 대한 On/Off test --------------
				if ( !( *m_dispSW & DISP_LIGHT_NORMAL ) )
				{
					pp		= vc->plane;

					for ( int p = 0; p < vc->nofPlane; p++, pp++ )
					{
						if ( ex * pp->a + ey * pp->b + ez * pp->c + pp->d > 0 )
							break;
					}

					if ( p < vc->nofPlane )
						continue;
				}

				// ---------- lightpoint size 결정 ----------------
				if ( len < 600.0 )
					lptSize = 4.8f * extDefPtr->actPntSize;
				else
					lptSize = 0.008f * len * extDefPtr->actPntSize;

				ubIntensity	= 255;									// 이들 light는 항상 최대 밝기로 놓음
				// ------------- Light rendering -------------------
				glPointSize( lptSize );
				glEnable( GL_BLEND );
				glColor4ub( vc->color[0], vc->color[1], vc->color[2], ubIntensity );

				RenderTexturedLight( vc->vtx, lptSize, m_lgtTexID );

				m_nofRenderedLgtPnt++;
				break;

			case STROBE_LGT:
				if ( animPtr )		// STROBE / REIL light On/Off animation ------------------------------
				{
					clock = fmod( *m_timeElapsed, animPtr->lpaPeriod * 1000 ) / 1000.0;
					if ( !( clock-animPtr->lpaTimeOn < animPtr->lpaPeriod - animPtr->lpaPhaseDelay && clock-animPtr->lpaTimeOn > animPtr->lpaPeriod - (animPtr->lpaPhaseDelay+animPtr->lpaTimeOn) ) )
						continue;
				}

				if ( !m_strobeSW )
					continue;

				extDefPtr = lp->extDefPtr;

				// ----------- 시계에 대한 On/Off test --------------
				if ( len > extDefPtr->visibility )					// light point is too far away to render
					continue;										// apprPtr->lpVisibilityRange 는 override 됨 

				// ----------- 방향성에 대한 On/Off test --------------
				if ( !( *m_dispSW & DISP_LIGHT_NORMAL ) )
				{
					pp		= vc->plane;

					for ( int p = 0; p < vc->nofPlane; p++, pp++ )
					{
						if ( ex * pp->a + ey * pp->b + ez * pp->c + pp->d > 0 )
							break;
					}

					if ( p < vc->nofPlane )
						continue;
				}

				// ---------- lightpoint size 결정 ----------------
				// ------------- Light rendering -------------------
				if ( len < 600.0 )
				{
					if ( len < 600.0 )
						lptSize = 2.4f * extDefPtr->actPntSize;
					else
						lptSize = 0.004f * len * extDefPtr->actPntSize;

					ubIntensity	= 255;									// 이들 light는 항상 최대 밝기로 놓음

					glColor3ub( vc->color[0], vc->color[1], vc->color[2] );

					RenderTexturedLight( vc->vtx, lptSize, m_lgtTexID );
				}
				else
				{
					lptSize = 2000.0f / len * apprPtr->lpActualPixelSize;

					if ( lptSize < apprPtr->lpMinPixelSize )
						lptSize = apprPtr->lpMinPixelSize;
					else if ( lptSize > apprPtr->lpMaxPixelSize )
						lptSize = apprPtr->lpMaxPixelSize;

					glPointSize( lptSize );
					glEnable( GL_BLEND );

					glColor3ub( vc->color[0], vc->color[1], vc->color[2] );

					glBegin( GL_POINTS );
						glVertex3dv( vc->vtx );
					glEnd();
				}

				m_nofRenderedLgtPnt++;
				break;

			case VASI_PAPI_LGT:
				if ( lp->lgtType == VASI_PAPI_LGT && !m_papiSW )
					continue;

				extDefPtr = lp->extDefPtr;

				// ----------- 시계에 대한 On/Off test --------------
				if ( len > extDefPtr->visibility )					// light point is too far away to render
					continue;										// apprPtr->lpVisibilityRange 는 override 됨 

				// ----------- 방향성에 대한 On/Off test --------------
				if ( !( *m_dispSW & DISP_LIGHT_NORMAL ) )
				{
					pp		= vc->plane;

					for ( int p = 0; p < vc->nofPlane; p++, pp++ )
					{
						if ( ex * pp->a + ey * pp->b + ez * pp->c + pp->d > 0 )
							break;
					}

					if ( p < vc->nofPlane )
						continue;
				}

				// ---------- lightpoint size 결정 ----------------
				lptSize = 2000.0f / len * extDefPtr->actPntSize;

				if ( lptSize < extDefPtr->minPntSize )
				{
					lptSize = extDefPtr->minPntSize;
				}
				else if ( lptSize > extDefPtr->maxPntSize )
				{
					lptSize = extDefPtr->maxPntSize;
				}

				ubIntensity	= 255;									// 이들 light는 항상 최대 밝기로 놓음

				// ------------- Light rendering -------------------
				glPointSize( lptSize );
				glEnable( GL_BLEND );
				glColor4ub( vc->color[0], vc->color[1], vc->color[2], ubIntensity );

				glBegin( GL_POINTS );
					glVertex3dv( vc->vtx );
				glEnd();

				m_nofRenderedLgtPnt++;
				break;

			case APPROACH_LGT:
			case RUNWAY_LGT:
			case TAXIWAY_LGT:
				// ----------- 시계에 대한 On/Off test --------------
				if ( len > apprPtr->lpVisibilityRange )					// light point is too far away to render
					continue;

				// ----------- 방향성에 대한 On/Off test --------------
				if ( apprPtr->lpDirectionalityType )				// 지향성 ?
				{
					if ( !( *m_dispSW & DISP_LIGHT_NORMAL ) )
					{
						pp		= vc->plane;

						for ( int p = 0; p < vc->nofPlane; p++, pp++ )
						{
							if ( ex * pp->a + ey * pp->b + ez * pp->c + pp->d > 0 )
								break;
						}

						if ( p < vc->nofPlane )
							continue;
					}
				}

				// ---------- lightpoint size 결정 ----------------
				lptSize = 2000.0f / len * apprPtr->lpActualPixelSize;

				if ( lptSize < apprPtr->lpMinPixelSize )
					lptSize = apprPtr->lpMinPixelSize;
				else if ( lptSize > apprPtr->lpMaxPixelSize )
					lptSize = apprPtr->lpMaxPixelSize;

				if ( lp->lgtType & APPROACH_LGT )
					ubIntensity	= (BYTE)( 255 * m_approachLgtIntersity );
				else if ( lp->lgtType & RUNWAY_LGT )
					ubIntensity	= (BYTE)( 255 * m_rwyLgtIntersity );
				else if ( lp->lgtType & TAXIWAY_LGT )
					ubIntensity	= (BYTE)( 255 * m_taxiwayLgtIntersity );
				else
					ubIntensity	= 255;

				// ------------- Light rendering -------------------
				glPointSize( lptSize );
				glEnable( GL_BLEND );
				glColor4ub( vc->color[0], vc->color[1], vc->color[2], ubIntensity );

				if ( lp->lgtType == REIL_LGT )
				{
					RenderTexturedLight( vc->vtx, lptSize, m_lgtTexID );
				}
				else
				{
					glBegin( GL_POINTS );
						glVertex3dv( vc->vtx );
					glEnd();
				}

				m_nofRenderedLgtPnt++;
				break;

			default:
				cLog.LogExit( "Illegal lgt intensity bit pattern %x in lgtpnt %s\n", lp->lgtType, lp->linkname );
			}

			if ( apprPtr->lpDirectionalityType && *m_dispSW & DISP_LIGHT_NORMAL )
			{
				glBegin( GL_LINE_LOOP );
				for ( int i = 0; i < 4; i++ )
				{
					glVertex3dv( vc->coneVtx[i] );
				}
				glEnd();

				glBegin( GL_LINES );
				for ( i = 0; i < 4; i++ )
				{
					glVertex3dv( vc->vtx );
					glVertex3dv( vc->coneVtx[i] );
				}

				glColor3ub( 0, 0, 0 );

				glVertex3dv( vc->vtx );
				glVertex3dv( vc->coneVtx[i] );

				glEnd();
			}
		}
	}
}

// ============================ (( Transparent 1st Pass Render )) ==================================
//	Transparent : on
//	Backfaceing : off
//	Trace		: EnvMapped, Light on/off 변화 체크함
//
//	node의 Abs/Rel coord상태에 따라 x-from 또는 Abs coord를 사용하며 
//	Multi-textured polygon이 존재하면 polygon단위로 즉시 multi-texture를 overlap시켜주어야 한다.
// ==================================================================================================
void
Model::RenderTransparentPolygon()
{
	MESH*		mp;
	int			p;
	VTXCOMBO*	vc;

	glPushAttrib( GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_CURRENT_BIT );

	// -------- ( Always Transparent On ) --------------
	glEnable( GL_BLEND );
	*m_renderFlag |= PROP_TRANSPARENT;
	
	// -------- ( Initially EnvMapped Off ) ----------------------
	glDisable( GL_TEXTURE_GEN_S );
	glDisable( GL_TEXTURE_GEN_T );
	*m_renderFlag &= ~PROP_REFLECTIVE;

	// -------- ( Tev Blend Off => Modulate ) ----------
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	*m_renderFlag &= ~PROP_BLEND_TEV;

	// -------- ( Texture On ) ----------
	glEnable( GL_TEXTURE_2D );
	*m_renderFlag |= PROP_TEXTURED;

	glDisable( GL_CULL_FACE );

	// ============================================== TranSort handler =================================================
	for ( int t = 0; t < m_nofTransPoly; t++ )
	{
//		mp = m_transPoly[ m_tranSortIdx[t] ].mp;
		mp = m_transPoly[ t ].meshPtr;

		RenderTransMesh( NODE_IS_MESH, mp );
	}

	glPopAttrib();
}

void
Model::SetConrolSW( int* renderFlag, int* oneShotFlag, int* prevMatID, int* prevTexID, int* prevMultiTexID, int* dispSW, int* currentTimeOfDay, TIMEOFDAY* todPtr, double* timeElapsed )
{
	m_renderFlag		= renderFlag;
	m_oneShotFlag		= oneShotFlag;
	m_prevMatID			= prevMatID;
	m_prevTexID			= prevTexID;
	m_prevMultiTexID	= prevMultiTexID;
	m_dispSW			= dispSW;
	m_timeElapsed		= timeElapsed;
	m_currentTimeOfDay	= currentTimeOfDay;
	m_timeOfDay			= todPtr;
}
/*
struct	GEO_BUFF
{
	NODE_HEADER		headerNode;

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

	int				nofMesh;
	MESH*			mesh;

	int				nofLgtPnt;
	LGTPNT*			lgtPnt;

	int				nofVtxCombo;
	VTXCOMBO*		vtxCombo;
};
*/
void
Model::SetGeoBuffer( GEO_BUFF* geoBuffPtr )
{
	m_nofHeaderNode	= geoBuffPtr->nofHeaderNode;
	m_headerNode	= geoBuffPtr->headerNode;

	m_nofExtRefNode	= geoBuffPtr->nofExtRefNode;
	m_extRefNode	= geoBuffPtr->extRefNode;

	m_nofGroupNode	= geoBuffPtr->nofGroupNode;
	m_groupNode		= geoBuffPtr->groupNode;
	
	m_nofLODNode	= geoBuffPtr->nofLODNode;
	m_lodNode		= geoBuffPtr->lodNode;
	
	m_nofDOFNode	= geoBuffPtr->nofDOFNode;
	m_dofNode		= geoBuffPtr->dofNode;
	
	m_nofBSPNode	= geoBuffPtr->nofBSPNode;
	m_bspNode		= geoBuffPtr->bspNode;
	
	m_nofObjNode	= geoBuffPtr->nofObjNode;
	m_objNode		= geoBuffPtr->objNode;
	
	m_nofSwitchNode	= geoBuffPtr->nofSwitchNode;
	m_switchNode	= geoBuffPtr->switchNode;
	
	m_nofMesh		= geoBuffPtr->nofMesh;
	m_mesh			= geoBuffPtr->mesh;
	
	m_nofLgtPnt		= geoBuffPtr->nofLgtPnt;
	m_lgtPnt		= geoBuffPtr->lgtPnt;
	
	m_nofVtxCombo	= geoBuffPtr->nofVtxCombo;
	m_vtxCombo		= geoBuffPtr->vtxCombo;

	m_nofVtxLgt		= geoBuffPtr->nofVtxLgt;
	m_vtxLgt		= geoBuffPtr->vtxLgt;

	m_defaultMatID	= geoBuffPtr->defaultMatID;

	m_nofMaterial	= geoBuffPtr->nofMaterial;
	m_matList	= geoBuffPtr->matList;

	m_nofTexture	= geoBuffPtr->nofTexture;
	m_texList	= geoBuffPtr->texList;

	m_noflpApprList	= geoBuffPtr->noflpApprList;
	m_lpApprList	= geoBuffPtr->lpApprList;

	m_noflpAnimList	= geoBuffPtr->noflpAnimList;
	m_lpAnimList	= geoBuffPtr->lpAnimList;

	m_maxTransPoly	= geoBuffPtr->maxTransPoly;
//	m_nofTransPoly	= geoBuffPtr->nofTransPoly;					// 복사 대상이 아님 runtime variable임 
	m_transPoly	= geoBuffPtr->transPoly;

	m_maxTransVtxCombo	= geoBuffPtr->maxTransVtxCombo;
//	m_nofTransVtxCombo	= geoBuffPtr->nofTransVtxCombo;			// 복사 대상이 아님 runtime variable임 
	m_transVtxCombo	= geoBuffPtr->transVtxCombo;

	if ( m_lgtPntVisible )
		free( m_lgtPntVisible );

	if ( ( m_lgtPntVisible = (LGTPNT**)malloc( sizeof(LGTPNT*) * m_nofLgtPnt * 2 ) ) == NULL )
	{
		cLog.LogExit( "Cannot alloc m_lgtPntVisible!\n" );
	}
}

float	circ[36][2];

void
Model::RenderCircle( float x, float y, float z, float r1, float* colorPtr )
{
	static int	first = true;

	glPushMatrix();
	glPushAttrib( GL_ENABLE_BIT );

	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );

	glColor3fv( colorPtr );

	if ( first )
	{
		for ( int i = 0; i < 36; i++ )
		{
			circ[i][0]	= (float)cos(D2R*i*10);
			circ[i][1]	= (float)sin(D2R*i*10);
		}

		first = false;
	}

	glTranslatef( x, y, z );
	glScalef( r1, r1, r1 );

	glBegin( GL_LINE_LOOP );
	for ( int i = 0; i < 36; i++ )
	{
		glVertex2fv( circ[i] );
	}
	glEnd();

	glPopAttrib();
	glPopMatrix();
}
/*
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
*/

NODE*
Model::GetNodeID( char* nodeName, int nodeType, int nofList, NODE* nodeList )
{
	NODE_HEADER*	nhp;
	NODE_EXTREF*	nxp;
	NODE_GROUP*		ngp;
	NODE_LOD*		nlp;
	NODE_DOF*		ndp;
	NODE_BSP*		nbp;
	NODE_SWITCH*	nsp;
	NODE_OBJ*		nop;
	MESH*			mp;
	LGTPNT*			lp;

	NODE*			np	= nodeList;

	switch( nodeType)
	{
	case NODE_IS_HEADER:
		nhp		= (NODE_HEADER*)nodeList;
		break;
	case NODE_IS_EXTREF:
		nxp		=(NODE_EXTREF*)nodeList;
		break;
	case NODE_IS_GROUP:
		ngp		=(NODE_GROUP*)nodeList;
		break;
	case NODE_IS_LOD:
		nlp		=(NODE_LOD*)nodeList;
		break;
	case NODE_IS_DOF:
		ndp		=(NODE_DOF*)nodeList;
		break;
	case NODE_IS_BSP:
		nbp		=(NODE_BSP*)nodeList;
		break;
	case NODE_IS_SWITCH:
		nsp		=(NODE_SWITCH*)nodeList;
		break;
	case NODE_IS_OBJ:
		nop		=(NODE_OBJ*)nodeList;
		break;
	case NODE_IS_MESH:
		mp		=(MESH*)nodeList;
		break;
	case NODE_IS_LGTPNT:
		lp		=(LGTPNT*)nodeList;
		break;
	}

	for ( int i = 0; i < nofList; i++ )
	{
		if ( strcmp( np->linkname, nodeName ) == 0 )
			return np;

		switch( nodeType)
		{
		case NODE_IS_HEADER:
			np	= (NODE*)++nhp;
			break;
		case NODE_IS_EXTREF:
			np	= (NODE*)++nxp;
			break;
		case NODE_IS_GROUP:
			np	= (NODE*)++ngp;
			break;
		case NODE_IS_LOD:
			np	= (NODE*)++nlp;
			break;
		case NODE_IS_DOF:
			np	= (NODE*)++ndp;
			break;
		case NODE_IS_BSP:
			np	= (NODE*)++nbp;
			break;
		case NODE_IS_SWITCH:
			np	= (NODE*)++nsp;
			break;
		case NODE_IS_OBJ:
			np	= (NODE*)++nop;
			break;
		case NODE_IS_MESH:
			np	= (NODE*)++mp;
			break;
		case NODE_IS_LGTPNT:
			np	= (NODE*)++lp;
			break;
		}
	}

	return NULL;
}

NODE*
Model::FindNode( char* nodeName, int nodeType )
{
	NODE*	np;

	if ( nodeType > -1 )
	{
		switch( nodeType)
		{
		case NODE_IS_HEADER:
			return GetNodeID( nodeName, NODE_IS_HEADER,	m_nofHeaderNode,	(NODE*)m_headerNode );

		case NODE_IS_EXTREF:
			return GetNodeID( nodeName, NODE_IS_EXTREF,	m_nofExtRefNode,	(NODE*)m_extRefNode );

		case NODE_IS_GROUP:
			return GetNodeID( nodeName, NODE_IS_GROUP,	m_nofGroupNode,		(NODE*)m_groupNode );

		case NODE_IS_LOD:
			return GetNodeID( nodeName, NODE_IS_LOD,	m_nofLODNode,		(NODE*)m_lodNode );

		case NODE_IS_DOF:
			return GetNodeID( nodeName, NODE_IS_DOF,	m_nofDOFNode,		(NODE*)m_dofNode );

		case NODE_IS_BSP:
			return GetNodeID( nodeName, NODE_IS_BSP,	m_nofBSPNode,		(NODE*)m_bspNode );

		case NODE_IS_SWITCH:
			return GetNodeID( nodeName, NODE_IS_SWITCH,	m_nofSwitchNode,	(NODE*)m_switchNode );

		case NODE_IS_OBJ:
			return GetNodeID( nodeName, NODE_IS_OBJ,	m_nofObjNode,		(NODE*)m_objNode );

		case NODE_IS_MESH:
			return GetNodeID( nodeName, NODE_IS_MESH,	m_nofMesh,			(NODE*)m_mesh );

		case NODE_IS_LGTPNT:
			return GetNodeID( nodeName, NODE_IS_LGTPNT,	m_nofLgtPnt,		(NODE*)m_lgtPnt );

		default:
			cLog.LogExit( "Attempt to get illegal NODE*(type %d) of %s\n", nodeType, nodeName );
		}
	}
	else
	{
		if ( ( np = GetNodeID( nodeName, NODE_IS_HEADER,	m_nofHeaderNode,	(NODE*)m_headerNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_EXTREF,	m_nofExtRefNode,	(NODE*)m_extRefNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_GROUP,		m_nofGroupNode,		(NODE*)m_groupNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_LOD,		m_nofLODNode,		(NODE*)m_lodNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_DOF,		m_nofDOFNode,		(NODE*)m_dofNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_BSP,		m_nofBSPNode,		(NODE*)m_bspNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_SWITCH,	m_nofSwitchNode,	(NODE*)m_switchNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_OBJ,		m_nofObjNode,		(NODE*)m_objNode ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_MESH,		m_nofMesh,			(NODE*)m_mesh ) ) != NULL )
			return np;

		if ( ( np = GetNodeID( nodeName, NODE_IS_LGTPNT,	m_nofLgtPnt,		(NODE*)m_lgtPnt ) ) != NULL )
			return np;

		cLog.LogExit( "Attempt to get illegal NODE*(type %d) of %s\n", nodeType, nodeName );
	}

	return NULL;
}

int
Model::TraverseModel( NODE* np, int nodeSP, int nodeStatus )
{
	NODE_HEADER*	nhp;
	NODE_GROUP*		ngp;
	NODE_LOD*		nlp;
	NODE_DOF*		ndp;
	NODE_BSP*		nbp;
	NODE_OBJ*		nop;
	NODE_SWITCH*	nsp;
	NODE*			tmpNp;

	int				i;
	double			dx, dy, dz, len;

	static double	eyePos[3];

	if ( nodeSP == 0 )
	{
		m_MVM.LoadIdentity();
		m_nodeSP = 0;

		m_nofRenderedPolygon		= 0;
		m_nofRenderedMesh			= 0;
		m_nofRenderedLightPoint		= 0;
		m_nofSwInLOD				= 0;
		m_nofSwOutLOD				= 0;
		m_nofVisibleGroup			= 0;

		m_nofTransPoly				= 0;
		m_nofTransVtxCombo			= 0;

		eGL	tmpGL;

		tmpGL.LoadIdentity();
		tmpGL.Rotated( -m_modelAirport->rotZ, 'z' );
		tmpGL.Translated( -m_modelAirport->xlat[0], -m_modelAirport->xlat[1], -m_modelAirport->xlat[2] );

		tmpGL.PassMVMdv( m_modelEyePos, eyePos );
	}

	if ( !np )
		return NULL;

	// ========================== (( Opaque 1st Pass Render )) ==========================
	while( 1 )			// next sibling loop
	{
		if ( np->type != NODE_IS_MESH && np->type != NODE_IS_LGTPNT && np->nofXform ) //np->status & NODE_XFORMED )
		{
			glPushMatrix();

			for ( int i = 0; i < np->nofXform; i++ )
			{
				if ( np->xformType[i] == NODE_XLATED )
				{
					glTranslated( np->xlat[0], np->xlat[1], np->xlat[2] );
				}
				else if ( np->xformType[i] == NODE_ROTATED )
				{
					glTranslated( np->rotCenter[0], np->rotCenter[1], np->rotCenter[2] );
					glRotated( np->rot[0], np->rot[1], np->rot[2], np->rot[3] );
					glTranslated( -np->rotCenter[0], -np->rotCenter[1], -np->rotCenter[2] );
				}
				else if ( np->xformType[i] == NODE_SCALED )
				{
					glTranslated( np->scaleCenter[0], np->scaleCenter[1], np->scaleCenter[2] );
					glScaled( np->scale[0], np->scale[1], np->scale[2] );
					glTranslated( -np->scaleCenter[0], -np->scaleCenter[1], -np->scaleCenter[2] );
				}
			}
		}

		if ( np )
			(*m_traverseCallBack)( np );

		switch( np->type )
		{
		case NODE_IS_HEADER:
			nhp = (NODE_HEADER*)np;
			if ( np->child )
				TraverseModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_EXTREF:
			ngp = (NODE_GROUP*)np;
			if ( np->child )
				TraverseModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_GROUP:
			ngp = (NODE_GROUP*)np;
			m_nofVisibleGroup++;

			if ( np->child )
				TraverseModel( (NODE*)np->child, nodeSP+1 );

			break;

		case NODE_IS_LOD:
			nlp = (NODE_LOD*)np;

			dx = nlp->cx - m_modelEyePos[0];
			dy = nlp->cy - m_modelEyePos[1];
			dz = nlp->cz - m_modelEyePos[2];

			len = (float)sqrt( dx*dx + dy*dy + dz*dz );			// lod node중심 까지의 거리

			if ( *m_oneShotFlag )
			{
				cLog.Log( "LOD %s : (%.2f ~ %.2f) len = %.2f\n", nlp->linkname, nlp->swIn, nlp->swOut, len );
			}
			
			if ( *m_dispSW & DISP_LOD_CIRCLE )
				RenderCircle( nlp->cx, nlp->cy, nlp->cz, nlp->swIn+2.0f, swInColor );

			if ( !( *m_dispSW & DISP_ALL_LOD ) )
			if ( nlp->swIn < len || nlp->swOut > len ) 		// lod descendants를 그리지 않는다.
			{
				m_nofSwOutLOD++;
				break;
			}

			if ( *m_dispSW & DISP_LOD_CIRCLE )
				RenderCircle( nlp->cx, nlp->cy, nlp->cz, nlp->swOut+2.0f, swOutColor );

			m_nofSwInLOD++;
				
			TraverseModel( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_DOF:
			ndp = (NODE_DOF*)np;

			glPushMatrix();
			m_MVM.PushMatrix();

			glTranslated(		ndp->dofXlat[0], ndp->dofXlat[1], ndp->dofXlat[2] );
			m_MVM.Translated(	ndp->dofXlat[0], ndp->dofXlat[1], ndp->dofXlat[2] );

			glTranslated(		ndp->dofRotCenter[0], ndp->dofRotCenter[1], ndp->dofRotCenter[2] );
			m_MVM.Translated(	ndp->dofRotCenter[0], ndp->dofRotCenter[1], ndp->dofRotCenter[2] );

			glRotated(			ndp->dofRotAngle, ndp->dofRotNorm[0], ndp->dofRotNorm[1], ndp->dofRotNorm[2] );
			m_MVM.RotAxisd(		ndp->dofRotAngle, ndp->dofRotNorm[0], ndp->dofRotNorm[1], ndp->dofRotNorm[2] );

			glTranslated(		-ndp->dofRotCenter[0], -ndp->dofRotCenter[1], -ndp->dofRotCenter[2] );
			m_MVM.Translated(	-ndp->dofRotCenter[0], -ndp->dofRotCenter[1], -ndp->dofRotCenter[2] );

//			glScaled(			ndp->dofScale[0], ndp->dofScale[1], ndp->dofScale[2] );
//			m_MVM.Scaled(		ndp->dofScale[0], ndp->dofScale[1], ndp->dofScale[2] );

			TraverseModel( (NODE*)np->child, nodeSP+1 );

			m_MVM.PopMatrix();
			glPopMatrix();

			break;

		case NODE_IS_BSP:
			nbp = (NODE_BSP*)np;

			len = nbp->a * m_modelEyePos[0]
				+ nbp->b * m_modelEyePos[1]
				+ nbp->c * m_modelEyePos[2]
				+ nbp->d;

			if ( len < 0.0 )
			{
				TraverseModel( (NODE*)np->child, nodeSP+1, NODE_CHILD_OF_BSP );
			}
			else
			{
				tmpNp	= (NODE*)np->child;
				tmpNp	= (NODE*)tmpNp->right;
				tmpNp	= (NODE*)tmpNp->right;

				TraverseModel( (NODE*)( ( (np->child)->right)->right), nodeSP+1, NODE_CHILD_OF_BSP | NODE_REV_DIRECTION );
			}

			break;

		case NODE_IS_SWITCH:
			nsp		= (NODE_SWITCH*)np;
			tmpNp	= (NODE*)np->child;

			for ( i = 0; i < nsp->currentMask; i++ )
			{
				tmpNp	= (NODE*)tmpNp->right;
			}

			TraverseModel( tmpNp, nodeSP+1, NODE_CHILD_OF_SWITCH );

			break;

		case NODE_IS_OBJ:
			nop = (NODE_OBJ*)np;

			if ( !( nop->todSW & TOD_HIDE_ON_DAY ) )
				TraverseModel( (NODE*)np->child, nodeSP+1 );
			break;

		case NODE_IS_MESH:
			if ( !( nodeStatus & NODE_CHILD_OF_BSP ) || *m_dispSW & DISP_BSP_PLANE )
			{
//				RenderMesh( GL_POLYGON, (MESH*)np );
				m_nofRenderedPolygon++;
			}
			break;

		case NODE_IS_LGTPNT:
			*m_lgtPntVisible++	= (LGTPNT*)np;
			m_nofRenderedLightPoint++;
			break;
		}

		if ( np->status & NODE_XFORMED )
			glPopMatrix();

		if ( nodeStatus & NODE_CHILD_OF_SWITCH )
			return NULL;

		if ( nodeStatus & NODE_REV_DIRECTION )
			np = (NODE*)np->left;
		else
			np = (NODE*)np->right;

		if ( !np )
			return NULL;
	}

	return NULL;
}
/*
#define	ONOFF_DEFAULT_LGT_INTENSITY	0x00000001
#define	APPROACH_LGT_INTENSITY		0x00000002
#define	RUNWAY_LGT_INTENSITY		0x00000004
#define	TAXIWAY_INTENSITY			0x00000008

// for intersity control
#define	ONOFF_REIL_LGT				0x00010000
#define	ONOFF_VASI_PAPI				0x00020000
#define	ONOFF_STROBE				0x00040000
*/
void
Model::SetLgtPntIntensity( int categoryID, float intensity )
{
	if ( categoryID == DEFAULT_LGT )
	{
		m_defaltLgtPntIntensity		= intensity;
	}
	else if ( categoryID & APPROACH_LGT )
	{
		m_approachLgtIntersity		= intensity;
	}
	else if ( categoryID & RUNWAY_LGT )
	{
		m_rwyLgtIntersity			= intensity;
	}
	else if ( categoryID & TAXIWAY_LGT )
	{
		m_taxiwayLgtIntersity		= intensity;
	}
}

void
Model::SetLgtPntSwitch( int swbit, bool swVal )
{
	if ( swbit & REIL_LGT )
	{
		m_reilLgtSW		= swVal;
	}
	else if ( swbit & VASI_PAPI_LGT )
	{
		m_papiSW		= swVal;
	}
	else if ( swbit & STROBE_LGT )
	{
		m_strobeSW		= swVal;
	}
}

int
Model::IsLgtPntSwitchOn( int swbit )
{
	if ( swbit & REIL_LGT )
	{
		return m_reilLgtSW;
	}
	else if ( swbit & VASI_PAPI_LGT )
	{
		return m_papiSW;
	}
	else if ( swbit & STROBE_LGT )
	{
		return m_strobeSW;
	}

	return false;
}

void
Model::RenderTexturedLight( double* pos, float size, int texID )
{
	double	az, in;
	double	dx, dy, dz, len;
	double	visibility;
	BYTE	transparency;					// fogged textured light point는 fog를 끄고 그려야 하므로 transparency로 사라지게 한다.

	dx	= pos[0]-m_modelEyePos[0];
	dy	= pos[1]-m_modelEyePos[1];
	dz	= pos[2]-m_modelEyePos[2];

	len	= sqrt( dx*dx + dy*dy );

	visibility		= m_timeOfDay[*m_currentTimeOfDay].fogVisibility;

	if ( visibility < len )
		transparency	= 0;
	else
		transparency	= BYTE( ( visibility - len ) * 255 / len );

	az	= atan2( dy, dx ) * R2D;
	in	= atan2( dz , len ) * R2D;


	glPushMatrix();
	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT  );

	glDisable( GL_FOG );
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_COLOR, GL_ONE );

	glTranslated( pos[0], pos[1], pos[2] );
	glRotated( az, 0.0, 0.0, 1.0 );
	glRotated( -in, 1.0, 0.0, 0.0 );
	glColor4ub( 255, 255, 255, transparency );
	glScalef( size, size, size );

	glBindTexture( GL_TEXTURE_2D, texID );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glBegin( GL_POLYGON );
		glTexCoord2f( 0.0, 1.0 );		glVertex3f( 0.0, -0.5f,  0.5f );
		glTexCoord2f( 0.0, 0.0 );		glVertex3f( 0.0, -0.5f, -0.5f );
		glTexCoord2f( 1.0, 0.0 );		glVertex3f( 0.0,  0.5f, -0.5f );
		glTexCoord2f( 1.0, 1.0 );		glVertex3f( 0.0,  0.5f,  0.5f );
	glEnd();

	glPopAttrib();
	glPopMatrix();
}

void
Model::WriteInsideLandingLightRegion()
{
	// 구멍이 뚫린 부분만 beam을 다시 그린다.
//	glDisable( GL_DEPTH_TEST );
	glColorMask(1,1,1,1);							// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glEnable( GL_STENCIL_TEST );					// Enable Stencil Buffer For "marking" The Floor
	glStencilFunc(GL_EQUAL, 1, 1);					// We Draw Only Where The Stencil Is 1
													// (I.E. Where The Floor Was Drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// Don't Change The Stencil Buffer
}

void
Model::WriteOutSideLandingLightRegion()
{
	glColorMask(1,1,1,1);							// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glEnable( GL_STENCIL_TEST );					// Enable Stencil Buffer For "marking" The Floor
	glStencilFunc(GL_NOTEQUAL, 1, 1);					// We Draw Only Where The Stencil Is 0
													// (I.E. Where The Floor Was Drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// Don't Change The Stencil Buffer
}

void
Model::DisableLandingLightResion()
{
//	glDisable(GL_STENCIL_TEST);						// Disable stencil test
}

void
Model::MakeLandingLightHole()
{
	// stencil buffer를 사용하여 화면중 beam이 그려지는 부분만 구멍을 뚫는다.

//	glDisable( GL_DEPTH_TEST );
	glEnable(GL_STENCIL_TEST);						// Enable Stencil Buffer For "marking" The Floor
	glColorMask(0,0,0,0);							// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glStencilFunc(GL_ALWAYS, 1, 1);					// Always Passes, 1 Bit Plane, 1 As Mask
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);		// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
													// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
													// Replace If Test Passes
}
/*
	int				m_nofGroupNode;
	NODE_GROUP*		m_groupNode;
*/

float	bvColor[30][3] =
{
	1.0f, 0.0f, 0.0f,
	0.9f, 0.1f, 0.0f,
	0.8f, 0.2f, 0.0f,
	0.7f, 0.3f, 0.0f,
	0.6f, 0.4f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.4f, 0.6f, 0.0f,
	0.3f, 0.7f, 0.0f,
	0.2f, 0.8f, 0.0f,
	0.1f, 0.9f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.9f, 0.1f,
	0.0f, 0.8f, 0.2f,
	0.0f, 0.7f, 0.3f,
	0.0f, 0.6f, 0.4f,
	0.0f, 0.5f, 0.5f,
	0.0f, 0.4f, 0.6f,
	0.0f, 0.3f, 0.7f,
	0.0f, 0.2f, 0.8f,
	0.0f, 0.1f, 0.9f,
	0.0f, 0.0f, 1.0f,
	0.1f, 0.0f, 0.9f,
	0.2f, 0.0f, 0.8f,
	0.3f, 0.0f, 0.7f,
	0.4f, 0.0f, 0.6f,
	0.5f, 0.0f, 0.5f,
	0.6f, 0.0f, 0.4f,
	0.7f, 0.0f, 0.3f,
	0.8f, 0.0f, 0.2f,
	0.9f, 0.0f, 0.1f,
};

float	bvColor1[3] = { 0.4f, 0.4f, 0.4f };

void
Model::RenderBV( int depth, char* name )
{
	NODE_GROUP*		ngp = m_groupNode;

	for ( int g = 0; g < m_nofGroupNode; g++, ngp++ )
	{
		if ( ngp->depth <= depth )
		{
			if ( name )
			{
				if ( _stricmp( ngp->linkname, name) != 0 )
					continue;
			}
			if ( ngp->depth <= 30 )
				RenderCircle( ngp->bv[0], ngp->bv[1], ngp->bv[2], ngp->bv[3], bvColor[ngp->depth] );
			else
				RenderCircle( ngp->bv[0], ngp->bv[1], ngp->bv[2], ngp->bv[3], bvColor1 );
		}
	}

	NODE_OBJ*		nop = m_objNode;

	for ( int o = 0; o < m_nofObjNode; o++, nop++ )
	{
		if ( nop->depth <= depth )
		{
			if ( name )
			{
//				cLog.Log( "obj[%d] : %s\n", o, nop->linkname );
				
				if ( _stricmp( nop->linkname, name) != 0 )
					continue;
			}
			if ( ngp->depth <= 30 )
				RenderCircle( nop->bv[0], nop->bv[1], nop->bv[2], nop->bv[3], bvColor[nop->depth] );
			else
				RenderCircle( nop->bv[0], nop->bv[1], nop->bv[2], nop->bv[3], bvColor1 );
		}
	}

	//if ( name )
	//	exit(0);
}
