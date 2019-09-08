// CLog.cpp: implementation of the CLog class.
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
#include "Log.h"

CLog		cLog;
CLog		gLog;
CLog		aLog;

//////////////////////////////////////////////////////////////////////

void __stdcall XVDebugMessage(char* format, ...)
{
	FILE* file = ::fopen( ".\\debug.log", "a+" );

	if ( file == NULL )
		return;

	char szBuff[1024];

	va_list argList;

	va_start( argList, format );
		_vstprintf( szBuff, format, argList );
	va_end( argList );

	::fputs( szBuff, file );

	::fclose( file );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CLog::CLog( char* filename )
{
	time_t	aclock;
	char	strFileName[64];
	
	m_fp	= NULL;
	m_logOn = true;

	if ( filename )
	{
		strcpy( m_logFileName, filename );
	}
	else
	{
		time( &aclock );
		strftime( strFileName, sizeof(strFileName), "%m%d%H%M.log", localtime( &aclock ) );
		
		strcpy( m_logFileName, strFileName );	//strcpy( m_logFileName, "log.txt" );
	}
}

CLog::~CLog()
{
	if ( m_fp )
		fclose( m_fp );
}

//////////////////////////////////////////////////////////////////////

void
CLog::Log( char* format, ... )
{
	if ( !m_logOn )
		return;

	if ( m_fp == NULL )
	{
		m_fp = fopen( m_logFileName, "wt" );
	}
	if ( m_fp == NULL )
		return;

	va_list argList;

	va_start( argList, format );
	char szBuff[1024];
		_vstprintf( szBuff, format, argList );
	va_end( argList );

	fprintf( m_fp, "%s", szBuff );
}

void
CLog::LogExit( char* format, ... )
{
	if ( !m_logOn )
		return;

	va_list argList;

	va_start( argList, format );
		char szBuff[200];
		_vstprintf( szBuff, format, argList );
	va_end( argList );

	char errorMsg[1024] = "";

	Log( "%s: %s", errorMsg, szBuff );
	
	exit(1);
}

void
CLog::LogClose()
{
	if ( m_fp )
		fclose( m_fp );
}
