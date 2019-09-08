// FileName.cpp: implementation of the FileName class.
//
//////////////////////////////////////////////////////////////////////
/*
#include <math.h>		// Header File For Windows
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>		// Header File For Variable Argument Routines	( ADD )
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glaux.h>		// Header File For The Glaux Library
#include <tchar.h>
*/
#include "stdafx.h"
#include "FileName.h"
#include "Log.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

FileName::FileName()
{
}

FileName::~FileName()
{
}



// nOption = 1, 절대경로 
// nOption = 0, 상대경로 -> 현재 시스템이 파악하고 있는 디렉트리 파일 열기를 다른 디랙토리에서 하게 되면 변할 수 있다.
void
FileName::SetWorkingDirectory( char* path )
{
	if ( path == NULL )
	{
		GetCurrentDirectory( 256, m_workingDirectory );
	}
	else
	{
		strcpy( m_workingDirectory, path );
	}
}

void
FileName::InitPathStack( char* pathStr )
{
	int		len	= strlen(pathStr);
	
	m_pathSP	= 0;

	strcpy( m_pathStack[m_pathSP], pathStr );

	if ( m_pathStack[m_pathSP][len-1] != '/' && m_pathStack[m_pathSP][len-1] != '\\' )
	{
		m_pathStack[m_pathSP][len]	= '/';
		m_pathStack[m_pathSP][len+1]	= '\0';
	}
}

void
FileName::PushPath( char* pathStr )
{
	if ( ++m_pathSP >= MAX_FILENAME_STACK_DEPTH )
		cLog.LogExit( "Path stack Overflows at %s!\n", pathStr );

	strcpy( m_pathStack[m_pathSP], m_pathStack[m_pathSP-1] );

	int		len	= strlen(m_pathStack[m_pathSP]);

	if ( m_pathStack[m_pathSP][len-1] != '/' && m_pathStack[m_pathSP][len-1] != '\\' )
	{
		m_pathStack[m_pathSP][len]	= '/';
		m_pathStack[m_pathSP][len+1]		= '\0';
	}

	if ( pathStr )
		strcat( m_pathStack[m_pathSP], pathStr );
}

void
FileName::PopPath()
{
	if ( --m_pathSP < 0 )
		cLog.LogExit( "Path stack Underflows!\n" );
}

char*
FileName::CurrentPath()
{
	return m_pathStack[m_pathSP];
}

char*
FileName::MakeFullPathFilename( char* filename )
{
	char	tmpStr[256];

	if ( filename[0] == '.' )		// ./ 로 시작하면
		strcpy( tmpStr, &filename[2] );
	else
		strcpy( tmpStr, filename );

	strcpy( m_tmpFullPathFileName, CurrentPath() );

	if ( m_tmpFullPathFileName[strlen(m_tmpFullPathFileName)-1] == '/' ||		// 끝이 '/'나 '\'로 끝나는 경우
		 m_tmpFullPathFileName[strlen(m_tmpFullPathFileName)-1] == '\\' )
	{
		strcat( m_tmpFullPathFileName, tmpStr );
	}
	else
	{
		strcat( m_tmpFullPathFileName, "/" );
		strcat( m_tmpFullPathFileName, tmpStr );
	}
	
	return m_tmpFullPathFileName;
}


//////////////////////////////////////////
//	C:/a/b/c.flt		=>	C:/a/b/
//	./a/b/c.flt			=>  ./a/b/
//	c.flt				=>	NULL
//	./c.flt				=>	./
//////////////////////////////////////////
char*
FileName::ExtractPathOnly( char* pathFileName )
{
	char*	slashPosition;

	strcpy( m_tmpPathStr, pathFileName );

	if ( !strchr( m_tmpPathStr, '/' ) && !strchr( m_tmpPathStr, '\\' ) )		// path char '/'나 '\'이 들어있지 않은 경우
		return NULL;

	if ( (slashPosition = strrchr( m_tmpPathStr, '/') ) == NULL )
	{
		slashPosition = strrchr( m_tmpPathStr, '\\');
	}

	slashPosition[1] = '\0';

	return m_tmpPathStr;
}

//////////////////////////////////////////
//	C:/a/b/c.flt		=>	c.flt
//	./a/b/c.flt			=>  c.lflt
//	c.flt				=>	c.flt
//	./c.flt				=>	c.flt
//////////////////////////////////////////
char*
FileName::ExtractFileNameOnly( char* pathFileName )
{
	char*	slashPosition;

	if ( !(slashPosition=strrchr( pathFileName, '/') ) )
	{
		if ( !(slashPosition=strrchr( pathFileName, '\\') ) )
		{
			strcpy( m_tmpPathStr, pathFileName );
			return m_tmpPathStr;
		}
	}

	strcpy( m_tmpPathStr, slashPosition+1 );

	return m_tmpPathStr;
}

//////////////////////////////////////////
//	C:/a/b/c.flt		=>	C:/a/b/			c.flt
//	./a/b/c.flt			=>  ./a/b/			c.lflt
//	c.flt				=>	NULL			c.flt
//////////////////////////////////////////
void
FileName::SeperatePathAndFileName( char* pathFileName, char* pathStr, char* filename )
{
	char*	slashPosition;

	strcpy( m_tmpPathStr, pathFileName );

	if ( !(slashPosition=strrchr( m_tmpPathStr, '/') ) )
	{
		if ( !(slashPosition=strrchr( m_tmpPathStr, '\\') ) )
		{	// path가 들어있지 않은 경우
			pathStr[0]	= '\0';							// path = NULL
			strcpy( filename, m_tmpPathStr );			// filename only
			return;
		}
	}

	slashPosition[1] = '\0';
	strcpy( pathStr, m_tmpPathStr );

	strcpy( m_tmpPathStr, slashPosition+1 );
}
