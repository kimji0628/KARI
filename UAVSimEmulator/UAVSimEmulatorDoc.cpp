
// UAVSimEmulatorDoc.cpp : CUAVSimEmulatorDoc Ŭ������ ����
//

#include "stdafx.h"
#include "UAVSimEmulator.h"

#include "UAVSimEmulatorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAVSimEmulatorDoc

IMPLEMENT_DYNCREATE(CUAVSimEmulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CUAVSimEmulatorDoc, CDocument)
END_MESSAGE_MAP()


// CUAVSimEmulatorDoc ����/�Ҹ�

CUAVSimEmulatorDoc::CUAVSimEmulatorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CUAVSimEmulatorDoc::~CUAVSimEmulatorDoc()
{
}

BOOL CUAVSimEmulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CUAVSimEmulatorDoc serialization

void CUAVSimEmulatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CUAVSimEmulatorDoc ����

#ifdef _DEBUG
void CUAVSimEmulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUAVSimEmulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUAVSimEmulatorDoc ���
