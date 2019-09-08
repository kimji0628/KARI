#if !defined(_TEXTURE_H_INCLUDED_)
#define _TEXTURE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>		// Header File For Windows
#include <dinput.h>
#include <ddraw.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glaux.h>	// Header File For The Glaux Library
#include <gl/glext.h>

// #include "OpenGL/Log.h"

//////////////////////////////////////////////////////////////////////
struct	sTEXTURE
{
	char			texName[256];
	char			texFileName[256];
	unsigned char*	texImageBuffer;
	int				bound;
	int				texLevel;
	unsigned int	imgSize;
	int				mipmap;
	int				staticTex;
	unsigned int	boundID;			// used for glBindTexture
	int				format;			// 0: Normal Texture, non-zero: Compressed Texture
	int				transparent;

	int				texWidth;
	int				texHeight;
	int				texComponent;
	int				textureUsed;
};


class CEasyTexture
{
protected:			// private method 만 ID로 호출함
	int				ReadImageData( int texID );
	
	int				m_maxNofTexture;
	int				m_nofTexture;	
	sTEXTURE*		m_texture;

public:				// public method는 texName으로 interface됨
	CEasyTexture();
	~CEasyTexture();

	void			InitTexture( int maxTex );
	int				AddTexture( char* texName, char* filename, int mipmap );			// return true if success, if fail return false
	int				RemoveTexture( char* texName );
	void			RemoveAllTexture();
	int				TexName2BoundTexID( char* texName );
	int				TexName2ID( char* texName );
	int				IsThisTextureTranprent( char* texName );
	sTEXTURE*		TexPtr( char* texName );
};

//////////////////////////////////////////////////////////////////////

#endif // !defined(_TEXTURE_H_INCLUDED_)

//////////////////////////////////////////////////////////////////////
