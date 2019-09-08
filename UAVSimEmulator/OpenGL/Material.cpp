#include "stdafx.h"
#include "Material.h"

Material::Material()
{
	m_nofMaterial		= 0;
	m_maxNofMaterial	= 0;

	m_material			= NULL;
}

Material::~Material()
{
	if (m_material != NULL)
	{
		delete[] m_material;
		m_material = NULL;
	}
}

void
Material::InitMaterial( int nofMaxMaterial )
{
	if ( ( m_material = new MATERIAL[ nofMaxMaterial] ) == NULL )
	{
		MessageBox( NULL, "Cannot alloc material buffer!", "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	memset( m_material, 0, nofMaxMaterial * sizeof(MATERIAL) );

	m_maxNofMaterial = nofMaxMaterial;
}

int
Material::MaterialName2ID( char* name )
{
	for ( int i = 0; i < m_maxNofMaterial; i++ )
	{
		if ( strcmp( m_material[i].name, name ) == 0 )
			return i;
	}

	return -1;
}

int
Material::NewMaterial()
{
	for ( int i = 0; i < m_maxNofMaterial; i++ )
	{
		if ( !m_material[i].boundID )
			return i;
	}

	return -1;
}

int
Material::AddMaterial( char* name, MATERIAL* mat )
{
	int		matID;
	char	tmpStr[128];

	if ( MaterialName2ID( name ) != -1 )
	{
		sprintf( tmpStr, "Material %s already exits\n", name );
		MessageBox( NULL, tmpStr, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	if ( ( matID = NewMaterial() ) == -1 )
	{
		sprintf( tmpStr, "OpenGL Material overflows : %s\n", name );
		MessageBox( NULL, tmpStr, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	strcpy( m_material[matID].name, name );

	glNewList( m_material[matID].boundID = glGenLists( 1 ), GL_COMPILE );
		glMaterialfv( GL_FRONT, GL_AMBIENT,   mat->ambient );
		glMaterialfv( GL_FRONT, GL_DIFFUSE,   mat->diffuse );
		glMaterialfv( GL_FRONT, GL_SPECULAR,  mat->specular );
		glMaterialf(  GL_FRONT, GL_SHININESS, mat->shineness );
	glEndList();

	return m_material[matID].boundID;
}

int
Material::RemoveMaterial( char* name )
{
	int		matID;
	char	tmpStr[128];


	if ( ( matID = MaterialName2ID( name ) ) == -1 )
	{
		sprintf( tmpStr, "Cannot remove material %s it's not exits\n", name );
		MessageBox( NULL, tmpStr, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		return false;
	}

	glDeleteLists( m_material[matID].boundID, 1 );

	memset( &m_material[matID], 0, sizeof( MATERIAL ) );

	return true;
}

void
Material::RemoveAllMaterials()
{
	for ( int i = 0; i < m_maxNofMaterial; i++ )
	{
		if ( m_material[i].name )
		{
			glDeleteLists( m_material[i].boundID, 1 );
			memset( &m_material[i], 0, sizeof( MATERIAL ) );
		}
	}
}