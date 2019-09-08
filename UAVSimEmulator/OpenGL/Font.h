#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl/gl.h>			// Header File For The OpenGL32 Library

#if !defined(_FONT_H_INCLUDED_)
#define _FONT_H_INCLUDED_

class	MyFont
{
private:
public:
	int		m_fontBase;

public:
	MyFont();
	MyFont( HDC hDC, char* fontName = NULL );
	~MyFont();

	int		BuildFont( HDC hDC, char* fontName = NULL, int height = -12, int weight = FW_REGULAR, DWORD italic = false );		// Build Our Bitmap Font
	void	KillFont();											// Delete The Font
	void	SelectFontSet( int fontBase )		{ m_fontBase = fontBase; }
	void	glPrint(const char *fmt, ...);						// Custom GL "Print" Routine
	void	OutTextXY( int x, int y, double* color, const char *fmt, ... );	// Custom GL "Print" Routine
};

extern	MyFont	cFont;
#endif		// _FONT_H_INCLUDED_