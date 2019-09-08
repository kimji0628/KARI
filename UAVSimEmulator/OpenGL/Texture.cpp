#include "stdafx.h"
#include "Texture.h"

// OpenGL extention call for texture compression
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	glCompressedTexImage2DARB = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEasyTexture::CEasyTexture()
{
	m_nofTexture		= 0;
	m_maxNofTexture		= 0;

	m_texture			= NULL;
}

CEasyTexture::~CEasyTexture()
{
	RemoveAllTexture();

	if (m_texture != NULL)
	{
		delete[] m_texture;
		m_texture = NULL;
	}
}

void
CEasyTexture::InitTexture( int maxTex )
{
	if ( ( m_texture = new sTEXTURE[ maxTex ] ) == NULL )
	{
		MessageBox( NULL, "Cannot alloc texture memory.", "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	m_maxNofTexture = maxTex;

	for ( int texID = 0; texID < maxTex; texID++ )
	{
		m_texture[texID].texImageBuffer	= NULL;
		m_texture[texID].texFileName[0]	= '\0';
		m_texture[texID].texName[0]		= '\0';
		m_texture[texID].imgSize		= 0;
		m_texture[texID].boundID		= 0;
		m_texture[texID].textureUsed	= false;
	}

	glCompressedTexImage2DARB = ( PFNGLCOMPRESSEDTEXIMAGE2DARBPROC )wglGetProcAddress( "glCompressedTexImage2DARB" );
}

///////////////////////////////////////////////////////////////
//	Private methods from here
///////////////////////////////////////////////////////////////
int
CEasyTexture::TexName2ID( char* texName )
{
	for ( int i = 0; i < m_nofTexture; i++ )
	{
		if ( strcmp( m_texture[i].texName, texName ) == 0 )
			return i;
	}

	return -1;
}

///////////////////////////////////////////////////////////////
//	Private methods from here
///////////////////////////////////////////////////////////////
int
CEasyTexture::TexName2BoundTexID( char* texName )
{
	for ( int i = 0; i < m_nofTexture; i++ )
	{
		if ( strcmp( m_texture[i].texName, texName ) == 0 )
			return m_texture[i].boundID;
	}

	return -1;
}

int
CEasyTexture::IsThisTextureTranprent( char* texName )
{
	for ( int i = 0; i < m_nofTexture; i++ )
	{
		if ( strcmp( m_texture[i].texName, texName ) == 0 )
			return m_texture[i].transparent;
	}

	return -1;
}

int
CEasyTexture::ReadImageData( int texID )
{
	FILE*			fp;
	unsigned char	hd[54];
	char*			filename = m_texture[texID].texFileName;
	char			strTmp[128];

	if ( ( fp = fopen( filename, "rb" ) ) == NULL )
	{
		sprintf( strTmp, "Texture file(%s) not found!", filename );
//		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		return -1;
	}

	if ( _stricmp( &filename[ strlen(filename)-3 ], "bmp" ) == 0 )
	{
		if ( fread( &hd, sizeof(unsigned char), 54, fp ) != 54 )
			return -1;

		m_texture[texID].texComponent	= hd[28];
		m_texture[texID].format			= 0;

		if ( hd[28] == 24 )
			m_texture[texID].texComponent = 3;
		else
		{
			sprintf( strTmp, "Bmp image %s cannot has 32 bit depth", filename );
			MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
			return -1;
		}

		m_texture[texID].texWidth	= hd[19] * 256 + hd[18];
		m_texture[texID].texHeight	= hd[23] * 256 + hd[22];

		m_texture[texID].imgSize	= m_texture[texID].texHeight * m_texture[texID].texWidth * m_texture[texID].texComponent;

		if ( ( m_texture[texID].texImageBuffer = (unsigned char*)malloc( m_texture[texID].imgSize ) ) == NULL )
			return -1;

		if ( fread( m_texture[texID].texImageBuffer, sizeof(unsigned char), m_texture[texID].imgSize, fp ) != m_texture[texID].imgSize )
			return -1;

		fclose( fp );

		m_texture[texID].texComponent = 3;
	}
	else if ( _stricmp( &filename[ strlen(filename)-3 ], "tga" ) == 0 )
	{
		if ( fread( &hd, sizeof(unsigned char), 18, fp ) != 18 )
			return -1;

		m_texture[texID].texComponent	= 4;		// currently tga file uses 32bit color of image in this game !!!!!!!!
		m_texture[texID].format			= 0;

		m_texture[texID].texWidth		= hd[12] + hd[13]*256;
		m_texture[texID].texHeight		= hd[14] + hd[15]*256;

		m_texture[texID].imgSize		= m_texture[texID].texHeight * m_texture[texID].texWidth * m_texture[texID].texComponent;

		if ( ( m_texture[texID].texImageBuffer = (unsigned char*)malloc( m_texture[texID].imgSize ) ) == NULL )
			return -1;

		if ( fread( m_texture[texID].texImageBuffer, sizeof(unsigned char), m_texture[texID].imgSize, fp ) != m_texture[texID].imgSize )
			return -1;

		fclose( fp );
		m_texture[texID].texComponent = 4;
	}
	else if ( _stricmp( &filename[ strlen(filename)-3 ], "dds" ) == 0 )
	{
		DDSURFACEDESC2 ddsd;
		char filecode[4];

		/* verify the type of file */
		fread( filecode, 1, 4, fp );

		if ( strncmp( filecode, "DDS ", 4 ) != 0 )
		{
			fclose(fp);
			return NULL;
		}

		/* get the surface desc */
		fread(&ddsd, sizeof(ddsd), 1, fp);

		/* how big is it going to be including all mipmaps? */
		m_texture[texID].imgSize = ddsd.dwMipMapCount > 1 ? ddsd.dwLinearSize * 2 : ddsd.dwLinearSize;

		if ( ( m_texture[texID].texImageBuffer = (unsigned char*)malloc( m_texture[texID].imgSize ) ) == NULL )
			return -1;

		fread( m_texture[texID].texImageBuffer, 1, m_texture[texID].imgSize, fp );

		/* close the file pointer */
		fclose(fp);

		m_texture[texID].texWidth			= ddsd.dwWidth;
		m_texture[texID].texHeight			= ddsd.dwHeight;
		m_texture[texID].texComponent		= (ddsd.ddpfPixelFormat.dwFourCC == FOURCC_DXT1) ? 3 : 4;
		m_texture[texID].texLevel			= ddsd.dwMipMapCount;

		switch( ddsd.ddpfPixelFormat.dwFourCC )
		{
			case FOURCC_DXT1:
				m_texture[texID].format	= GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;

			case FOURCC_DXT3:
				m_texture[texID].format	= GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;

			case FOURCC_DXT5:
				m_texture[texID].format	= GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;

			default:
				return NULL;
		}
	}
	else
	{
//		cLog.Log( "Not supported image format %s\n", filename );
		return -1;
	}

	return	m_texture[texID].imgSize;
}

int
CEasyTexture::AddTexture( char* texName, char* filename, int mipmap )
{
	int		texID;
	char	strTmp[128];

	if ( m_nofTexture >= m_maxNofTexture )
	{
		sprintf( strTmp, "Tex buffer overflows while adding %s", texName );
		MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
	}

	texID = m_nofTexture++;

	strcpy( m_texture[texID].texName,		texName );
	strcpy(	m_texture[texID].texFileName,	filename );
	m_texture[texID].mipmap = mipmap;

	// Load Image .......................................

	if ( ReadImageData( texID ) == -1 )
	{
		return -1;
	}

	// Bind Texture .....................................
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	
	glGenTextures( 1, &m_texture[texID].boundID );

	glBindTexture(   GL_TEXTURE_2D, m_texture[texID].boundID );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//---------------------
	if ( m_texture[texID].format )
	{
		if ( glCompressedTexImage2DARB == NULL )
		{
			sprintf( strTmp, "This system doest not support glCompressedTexImage2DARB!" );
			MessageBox( NULL, strTmp, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		}

		int				offset   = 0;
		unsigned int	blockSize = ( m_texture[texID].format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ) ? 8 : 16;
		unsigned int	size;

		if( m_texture[texID].mipmap )
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		else
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		for ( int i = 0; i < m_texture[texID].texLevel && ( m_texture[texID].texWidth || m_texture[texID].texHeight); ++i )
		{
			if( i && !m_texture[texID].mipmap )
			{
				break;
			}
			if (m_texture[texID].texWidth == 0)
				m_texture[texID].texWidth = 1;

			if (m_texture[texID].texHeight == 0)
				m_texture[texID].texHeight = 1;

			size = ( (m_texture[texID].texWidth+3) / 4 ) * ( (m_texture[texID].texHeight+3) / 4 ) * blockSize;

			glCompressedTexImage2DARB( GL_TEXTURE_2D, i, m_texture[texID].format,      m_texture[texID].texWidth, m_texture[texID].texHeight, 0, size, m_texture[texID].texImageBuffer + offset );

			offset += size;
			m_texture[texID].texWidth  >>= 1;
			m_texture[texID].texHeight >>= 1;
		}
	}
	//---------------------
	else
	{
		if( m_texture[texID].mipmap )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			switch ( m_texture[texID].texComponent )
			{
			case 3:
				gluBuild2DMipmaps( GL_TEXTURE_2D, GL_COMPRESSED_RGB_ARB, m_texture[texID].texWidth, m_texture[texID].texHeight, 
					GL_BGR_EXT, GL_UNSIGNED_BYTE, m_texture[texID].texImageBuffer ); 
				break;
			case 4:
				gluBuild2DMipmaps( GL_TEXTURE_2D, GL_COMPRESSED_RGBA_ARB, m_texture[texID].texWidth, m_texture[texID].texHeight, 
					GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_texture[texID].texImageBuffer ); 
				break;
			}
		}
		else
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			switch ( m_texture[texID].texComponent )
			{
			case 3:
				glTexImage2D( GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_ARB, m_texture[texID].texWidth, m_texture[texID].texHeight, 
					0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_texture[texID].texImageBuffer ); 
				break;
			case 4:
				glTexImage2D( GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_ARB, m_texture[texID].texWidth, m_texture[texID].texHeight, 
					0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_texture[texID].texImageBuffer ); 
				break;
			}
		}
	}

	free( m_texture[texID].texImageBuffer );
	
	m_texture[texID].texImageBuffer	= NULL;

	m_texture[texID].bound = true;
	
	return	m_texture[texID].boundID;			// non zero value for glBindTexture
}

int
CEasyTexture::RemoveTexture( char* texName )
{
	int	texID = TexName2ID( texName );
	unsigned int texList[1];

	if ( texID == -1 )
		return -1;

	if ( m_texture[texID].texImageBuffer )
		free( m_texture[texID].texImageBuffer );

	if ( glIsTexture( m_texture[texID].boundID ) )
	{
		texList[0] = m_texture[texID].boundID;
		glDeleteTextures( 1, texList );
	}

	m_texture[texID].texImageBuffer	= NULL;
	m_texture[texID].texFileName[0]	= '\0';
	m_texture[texID].texName[0]		= '\0';
	m_texture[texID].imgSize		= 0;
	m_texture[texID].boundID		= 0;
	m_texture[texID].bound			= false;
	m_texture[texID].textureUsed	= false;

	return true;
}

void
CEasyTexture::RemoveAllTexture()
{
	unsigned int	texName[1];

	for ( int texID = 0; texID < m_nofTexture; texID++ )
	{
		if ( m_texture[texID].texImageBuffer )
		{
			free( m_texture[texID].texImageBuffer );
		}

		if ( glIsTexture( m_texture[texID].boundID ) )
		{
			texName[0] = m_texture[texID].boundID;
			glDeleteTextures( 1, texName );
		}

		m_texture[texID].texImageBuffer	= NULL;
		m_texture[texID].texFileName[0]	= '\0';
		m_texture[texID].texName[0]		= '\0';
		m_texture[texID].imgSize		= 0;
		m_texture[texID].boundID		= 0;
		m_texture[texID].textureUsed	= false;
	}

	m_nofTexture = 0;
}

sTEXTURE*
CEasyTexture::TexPtr( char* texName )
{
	int	texID = TexName2ID( texName );

	if ( texID == -1 )
		return NULL;

	return &m_texture[texID];
}

/*

GLuint png_texture_load(const char * file_name, int * width, int * height)
{
    png_byte header[8];

    FILE *fp = fopen(file_name, "rb");
    if (fp == 0)
    {
        perror(file_name);
        return 0;
    }

    // read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", file_name);
        fclose(fp);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return 0;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    if (width){ *width = temp_width; }
    if (height){ *height = temp_height; }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte * image_data;
    image_data = malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep * row_pointers = malloc(temp_height * sizeof(png_bytep));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    int i;
    for (i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // Generate the OpenGL texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, temp_width, temp_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);
    return texture;
*/