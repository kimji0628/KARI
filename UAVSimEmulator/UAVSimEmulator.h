
// UAVSimEmulator.h : UAVSimEmulator ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CUAVSimEmulatorApp:
// �� Ŭ������ ������ ���ؼ��� UAVSimEmulator.cpp�� �����Ͻʽÿ�.
//

class CUAVSimEmulatorApp : public CWinAppEx
{
public:
	CUAVSimEmulatorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUAVSimEmulatorApp theApp;
