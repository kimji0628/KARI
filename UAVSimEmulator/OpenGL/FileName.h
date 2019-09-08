// XRLog.h: interface for the XRLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FILENAME_H_INCLUDED_)
#define _FILENAME_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines	( ADD )
#include <time.h>

//////////////////////////////////////////////////////////////////////
#define		MAX_FILENAME_STACK_DEPTH	50

class FileName
{
private:
	char			m_workingDirectory[256];
	int			m_pathSP;
	char			m_pathStack[MAX_FILENAME_STACK_DEPTH][256];
	char			m_tmpFullPathFileName[256];
	char			m_tmpPathStr[256];
	char			m_tmpFileName[128];

public:
					FileName();
	virtual			~FileName();

	void			InitPathStack( char* pathStr );
	void			PushPath( char* pathStr );
	void			PopPath();
	char*			CurrentPath();
	char*			MakeFullPathFilename( char* filename );
	char*			ExtractPathOnly( char* pathFileName );
	char*			ExtractFileNameOnly( char* pathFileName );
	void			SeperatePathAndFileName( char* pathFileName, char* pathStr, char* filename );

	void			ResetSP()		{ m_pathSP = 0; }

	void			SetWorkingDirectory( char* path = NULL );
	char*			GetWorkingDirectory()	{ return m_workingDirectory; }
};

//////////////////////////////////////////////////////////////////////

#endif // !defined(_FILENAME_H_INCLUDED_)
