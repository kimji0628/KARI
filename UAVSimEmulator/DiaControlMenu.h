#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDiaControlMenu 대화 상자입니다.

class CDiaControlMenu : public CDialog
{
	DECLARE_DYNAMIC(CDiaControlMenu)

public:
	CDiaControlMenu(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDiaControlMenu();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CONTROL_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDron_1;
	CString m_strDron_2;
	CString m_strDron_3;
	CString m_strMsnValue_1;
	CString m_strMsnValue_2;
	CString m_strMsnValue_3;
	CString m_strWindDir_1;
	CString m_strWindDir_2;
	CString m_strWindDir_3;
	CString m_strWindSpeed_1;
	CString m_strWindSpeed_2;
	afx_msg void OnEnChangeEditWindSpeed3();
	CString m_strWindSpeed_3;
	afx_msg void OnEnChangeEditWindSpeed1();
	afx_msg void OnEnChangeEditAltUp();
	CString m_strAltUp;
	CString m_strAltDown;
	CString m_strStartTime;
	CString m_strEndTime;
	afx_msg void OnBnClickedRadioMsnValue();
	afx_msg void OnBnClickedRadioWind();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonConform();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnEnChangeEditEndTime();
	afx_msg void OnNMCustomdrawSliderSymbolSize(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditAllWindSpeed();
	afx_msg void OnEnChangeEditAllWindDir();
	CString m_strAllWindDir;
	CString m_strAllWindSpeed;
	afx_msg void OnBnClickedCheckAllWind();
	afx_msg void OnEnChangeEditWindDir1();
	afx_msg void OnBnClickedCheck2Arrow();
	afx_msg void OnBnClickedCheckSphere();
	afx_msg void OnNMCustomdrawSliderTimeSpan(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strTimeSpan;
	int m_nRunTime;
	int m_nTimeEnd;
	int	m_nOffsetTime;
	afx_msg void OnNMCustomdrawSliderRunTotalTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckValue();
	afx_msg void OnBnClickedCheckFlightPath();
	afx_msg void OnBnClickedCheckDisplayCurrentPosition();
	afx_msg void OnBnClickedCheckDisplayAllRangeSphere();
	CButton m_chkBtnCurrentData;
	afx_msg void OnNMCustomdrawSliderSymbolSize2(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_sliderSymbolSize;
	CSliderCtrl m_sliderTimeSpan;
	CSliderCtrl m_sliderRunTotalTime;
	CSliderCtrl m_sliderSphereSymbolSize;
	afx_msg void OnEnChangeEditRunTotalTime();
	CSliderCtrl m_sliderAltTop;
	CSliderCtrl m_sliderAltBtm;
	afx_msg void OnEnChangeEditAltBtm();
	afx_msg void OnEnChangeEditAltTop();
	afx_msg void OnEnChangeEdit2();

	afx_msg void OnNMCustomdrawSliderAltTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAltBtm(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strMissionData;
	afx_msg void OnBnClickedCheckDisplayMap();
	afx_msg void OnBnClickedRadio2d();
	afx_msg void OnBnClickedRadio2d2();
	afx_msg void OnBnClickedButtonReset();
	CSliderCtrl m_sliderOffsetTime;
	afx_msg void OnNMCustomdrawSliderOffsetTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckAltDisplay();
};
