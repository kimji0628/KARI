
// UAVSimEmulatorDoc.h : CUAVSimEmulatorDoc Ŭ������ �������̽�
//


#pragma once


class CUAVSimEmulatorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CUAVSimEmulatorDoc();
	DECLARE_DYNCREATE(CUAVSimEmulatorDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CUAVSimEmulatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


