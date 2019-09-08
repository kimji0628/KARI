// FileMan.h: interface for the CFileMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMAN_H__E3EEDE3B_9B9B_447A_8C92_1931E04E12DD__INCLUDED_)
#define AFX_FILEMAN_H__E3EEDE3B_9B9B_447A_8C92_1931E04E12DD__INCLUDED_

// FileMan.h: interface for the CFileMan class.
//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileMan  
{

public:
	CFileMan();
	virtual ~CFileMan();

	void	read_file(char	fileName[], char **ptr_file, int *file_size);
	int		get_line(char *src_ptr, char line_ptr[]);

};

#endif // !defined(AFX_FILEMAN_H__E3EEDE3B_9B9B_447A_8C92_1931E04E12DD__INCLUDED_)
