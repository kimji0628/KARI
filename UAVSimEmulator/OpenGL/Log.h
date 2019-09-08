// XRLog.h: interface for the XRLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LOG_H_INCLUDED_)
#define _LOG_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines	( ADD )
#include <time.h>

void __stdcall XVDebugMessage(char* format, ...);

//////////////////////////////////////////////////////////////////////

class CLog  
{
	int		m_logOn;
	FILE*	m_fp;
	char	m_logFileName[50];

public:
	CLog( char* filename = NULL );
	virtual	~CLog();

	void	Log( char* format, ... );
	void	LogExit( char* format, ... );
	void	LogClose();
};

//////////////////////////////////////////////////////////////////////

extern	CLog cLog;
extern	CLog gLog;
extern	CLog aLog;
//////////////////////////////////////////////////////////////////////

#endif // !defined(_LOG_H_INCLUDED_)
