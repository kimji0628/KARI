#include "stdafx.h"
#include "Font.h"

MyFont	cFont;

MyFont::MyFont()
{
}

MyFont::MyFont( HDC hDC, char* fontName )
{
	BuildFont( hDC, fontName );
}

MyFont::~MyFont()
{
	KillFont();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//	Font system modules (Start)
int
MyFont::BuildFont( HDC hDC, char* fontName, int height, int weight, DWORD italic )				// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	char*	defaultFontName = "Tahoma";
	GLuint	base;

	if ( !fontName )
		fontName	= defaultFontName;

	if ((base = glGenLists(96)) == 0)
		return 0;

	if (stricmp(fontName, "symbol") == 0)
	{
		font = CreateFont(	height,							// Height Of Font
							0,								// Width Of Font
							0,								// Angle Of Escapement
							0,								// Orientation Angle
							weight,							// Font Weight
							italic,							// Italic
							FALSE,							// Underline
							FALSE,							// Strikeout
							SYMBOL_CHARSET,					// Character Set Identifier
							OUT_TT_PRECIS,					// Output Precision
							CLIP_DEFAULT_PRECIS,			// Clipping Precision
							ANTIALIASED_QUALITY,			// Output Quality
							FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
							fontName );						// Font Name
	}
	else
	{
		font = CreateFont(	height,							// Height Of Font
							0,								// Width Of Font
							0,								// Angle Of Escapement
							0,								// Orientation Angle
							weight,							// Font Weight
							italic,							// Italic
							FALSE,							// Underline
							FALSE,							// Strikeout
							ANSI_CHARSET,					// Character Set Identifier
							OUT_TT_PRECIS,					// Output Precision
							CLIP_DEFAULT_PRECIS,			// Clipping Precision
							ANTIALIASED_QUALITY,			// Output Quality
							FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
							fontName );						// Font Name
	}

	SelectObject(hDC, font);							// Selects The Font We Want

	m_fontBase	= base;

	wglUseFontBitmaps(hDC, 32, 96, m_fontBase);		// Builds 96 Characters Starting At Character 32

	return (base);
}

void
MyFont::KillFont(void)									// Delete The Font
{
	glDeleteLists(m_fontBase, 96);							// Delete All 96 Characters
}

void
MyFont::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(m_fontBase - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

void
MyFont::OutTextXY( int x, int y, double* color, const char *fmt, ... )	// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	glPushAttrib( GL_ENABLE_BIT | GL_LIST_BIT | GL_CURRENT_BIT );

	glColor4dv( color );
	glRasterPos2i( x, y );

	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	glDisable( GL_BLEND );

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glListBase(m_fontBase - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text

	glPopAttrib();										// Pops The Display List Bits
}

//	Font system modules (End)
/////////////////////////////////////////////////////////////////////////////////////////////////////

