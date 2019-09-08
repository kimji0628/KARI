#if !defined(_MATERIAL_H_INCLUDED_)
#define _MATERIAL_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl/gl.h>		// Header File For The GLu32 Library

#ifndef _MATERIAL_
#define _MATERIAL_
struct MATERIAL
{
	float		ambient[4];
	float		diffuse[4];
	float		specular[4];
	float		shineness;
	char		name[64];
	int			boundID;
};

#endif

class Material
{
private:
	int			m_nofMaterial;
	int			m_maxNofMaterial;
	MATERIAL*	m_material;

	int			NewMaterial();

public:
	Material();
	~Material();

	void		InitMaterial( int nofMaxMaterial );
	int			MaterialName2ID( char* name );
	int			AddMaterial( char* name, MATERIAL* mat );
	int			RemoveMaterial( char* name );
	void		RemoveAllMaterials();
};

//////////////////////////////////////////////////////////////////////

#endif // !defined(_MATERIAL_H_INCLUDED_)

//////////////////////////////////////////////////////////////////////
