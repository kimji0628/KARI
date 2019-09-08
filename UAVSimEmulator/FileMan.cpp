// FileMan.cpp: implementation of the CFileMan class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
// 파일읽기 
#include "FileMan.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileMan::CFileMan()
{

}

CFileMan::~CFileMan()
{

}


int	CFileMan::get_line(char *src_ptr, char line_ptr[])
{
	int	numberOfTotalCharacter = 0;
	while(*src_ptr !='\n')
	{
		line_ptr[numberOfTotalCharacter] = (*src_ptr);
		numberOfTotalCharacter ++;
		src_ptr++;
	}
	line_ptr[numberOfTotalCharacter] ='\0';
	return (numberOfTotalCharacter + 1);
}

void	CFileMan::read_file(char fileName[], char **ptr_file, int *file_size)
{
	FILE	*fp;
	char	*buffer;
	char	str[64];
	int		size;

	if ( (fp = fopen(fileName, "rb"))==NULL) 
	{
		sprintf(str,"cannot find %s ",fileName); 
		return;
	}
    fseek(fp, 0, SEEK_END);
    size=ftell(fp);
    if( (buffer=(char *)malloc(sizeof(char) * size))==NULL) {
		sprintf(str," Can not alloc memory for %s ",fileName); 
		return;

	}
    rewind(fp);
    fread(buffer, sizeof(char), size, fp);
	(*ptr_file) = buffer;
	(*file_size) = size;
	fclose(fp);
}
