// DiaControlMenu.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "UAVSimEmulator.h"
#include "DiaControlMenu.h"




// CDiaControlMenu 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDiaControlMenu, CDialog)

CDiaControlMenu::CDiaControlMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaControlMenu::IDD, pParent)

	, m_strDron_1(_T("0"))
	, m_strDron_2(_T("1"))
	, m_strDron_3(_T("2"))
	, m_strMsnValue_1(_T("0"))
	, m_strMsnValue_2(_T("0"))
	, m_strMsnValue_3(_T("0"))
	, m_strWindDir_1(_T("0"))
	, m_strWindDir_2(_T("0"))
	, m_strWindDir_3(_T("0"))
	, m_strWindSpeed_1(_T("0"))
	, m_strWindSpeed_2(_T("0"))
	, m_strWindSpeed_3(_T("0"))
	, m_strAltUp(_T("1000"))
	, m_strAltDown(_T("0"))
	, m_strStartTime(_T("0"))
	, m_strEndTime(_T("7200"))
	, m_strAllWindDir(_T("40"))
	, m_strAllWindSpeed(_T("10"))
	, m_strTimeSpan(_T(""))
	, m_nRunTime(0)
	, m_nTimeEnd(0)
	, m_strMissionData(_T(""))
{
	g_Interface.m_nDron_1 = atoi(m_strDron_1.GetBuffer());
	g_Interface.m_nDron_2= atoi(m_strDron_2.GetBuffer());
	g_Interface.m_nDron_3= atoi(m_strDron_3.GetBuffer());
	g_Interface.m_nMsnValue_1= atoi(m_strMsnValue_1.GetBuffer());
	g_Interface.m_nMsnValue_2= atoi(m_strMsnValue_2.GetBuffer());
	g_Interface.m_nMsnValue_3= atoi(m_strMsnValue_3.GetBuffer());
	g_Interface.m_nWindDir_1= atoi(m_strWindDir_1.GetBuffer());
	g_Interface.m_nWindDir_2= atoi(m_strWindDir_2.GetBuffer());
	g_Interface.m_nWindDir_3= atoi(m_strWindDir_3.GetBuffer());
	g_Interface.m_nWindSpeed_1= atoi(m_strWindSpeed_1.GetBuffer());
	g_Interface.m_nWindSpeed_2= atoi(m_strWindSpeed_2.GetBuffer());
	g_Interface.m_nWindSpeed_3= atoi(m_strWindSpeed_3.GetBuffer());
	g_Interface.m_nAltUp= atoi(m_strAltUp.GetBuffer());
	g_Interface.m_nAltDown= atoi(m_strAltDown.GetBuffer());
	g_Interface.m_fAllWindDir= atoi(m_strAllWindDir.GetBuffer());
	g_Interface.m_fAllWindSpeed= atoi(m_strAllWindSpeed.GetBuffer());


	m_strStartTime.Format("%.0f", g_Interface.m_fStartTime);

	m_strEndTime.Format("%.0f",g_Interface.m_fEndTime);





}

 
CDiaControlMenu::~CDiaControlMenu()
{
}

void CDiaControlMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SELECT_DRON_1, m_strDron_1);
	DDX_Text(pDX, IDC_EDIT_SELECT_DRON_2, m_strDron_2);
	DDX_Text(pDX, IDC_EDIT_SELECT_DRON_3, m_strDron_3);
	DDX_Text(pDX, IDC_EDIT_MSN_VALUE_1, m_strMsnValue_1);
	DDX_Text(pDX, IDC_EDIT_MSN_VALUE_2, m_strMsnValue_2);
	DDX_Text(pDX, IDC_EDIT_MSN_VALUE_3, m_strMsnValue_3);
	DDX_Text(pDX, IDC_EDIT_WIND_DIR_1, m_strWindDir_1);
	DDX_Text(pDX, IDC_EDIT_WIND_DIR_2, m_strWindDir_2);
	DDX_Text(pDX, IDC_EDIT_WIND_DIR_3, m_strWindDir_3);
	DDX_Text(pDX, IDC_EDIT_WIND_SPEED_1, m_strWindSpeed_1);
	DDX_Text(pDX, IDC_EDIT_WIND_SPEED_2, m_strWindSpeed_2);
	DDX_Text(pDX, IDC_EDIT_WIND_SPEED_3, m_strWindSpeed_3);
	DDX_Text(pDX, IDC_EDIT_ALT_UP, m_strAltUp);
	DDX_Text(pDX, IDC_EDIT_ALT_DN, m_strAltDown);
	DDX_Text(pDX, IDC_EDIT_START_TIME, m_strStartTime);
	DDX_Text(pDX, IDC_EDIT_END_TIME, m_strEndTime);
	DDX_Control(pDX, IDC_SLIDER_SYMBOL_SIZE, m_sliderSymbolSize);
	DDX_Text(pDX, IDC_EDIT_ALL_WIND_DIR, m_strAllWindDir);
	DDX_Text(pDX, IDC_EDIT_ALL_WIND_SPEED, m_strAllWindSpeed);
	DDX_Control(pDX, IDC_SLIDER_TIME_SPAN, m_sliderTimeSpan);
	DDX_Text(pDX, IDC_EDIT_TIME_SPAN, m_strTimeSpan);
	DDX_Text(pDX, IDC_EDIT_RUN_TOTAL_TIME, m_nRunTime);
	DDX_Text(pDX, IDC_EDIT_TIME_END, m_nTimeEnd);
	DDX_Control(pDX, IDC_SLIDER_RUN_TOTAL_TIME, m_sliderRunTotalTime);
	DDX_Control(pDX, IDC_CHECK_DISPLAY_CURRENT_POSITION, m_chkBtnCurrentData);
	DDX_Control(pDX, IDC_SLIDER_SYMBOL_SIZE2, m_sliderSphereSymbolSize);
	DDX_Control(pDX, IDC_SLIDER_ALT_TOP, m_sliderAltTop);
	DDX_Control(pDX, IDC_SLIDER_ALT_BTM, m_sliderAltBtm);
	DDX_Text(pDX, IDC_EDIT_ALL_MISSION_DATA, m_strMissionData);
	DDX_Control(pDX, IDC_SLIDER_OFFSET_TIME, m_sliderOffsetTime);
}


BEGIN_MESSAGE_MAP(CDiaControlMenu, CDialog)
	ON_EN_CHANGE(IDC_EDIT_WIND_SPEED_3, &CDiaControlMenu::OnEnChangeEditWindSpeed3)
	ON_EN_CHANGE(IDC_EDIT_WIND_SPEED_1, &CDiaControlMenu::OnEnChangeEditWindSpeed1)
	ON_EN_CHANGE(IDC_EDIT_ALT_UP, &CDiaControlMenu::OnEnChangeEditAltUp)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CONFORM, &CDiaControlMenu::OnBnClickedButtonConform)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDiaControlMenu::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDiaControlMenu::OnBnClickedButtonPause)
	ON_EN_CHANGE(IDC_EDIT_END_TIME, &CDiaControlMenu::OnEnChangeEditEndTime)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SYMBOL_SIZE, &CDiaControlMenu::OnNMCustomdrawSliderSymbolSize)
	ON_EN_CHANGE(IDC_EDIT_ALL_WIND_SPEED, &CDiaControlMenu::OnEnChangeEditAllWindSpeed)
	ON_EN_CHANGE(IDC_EDIT_ALL_WIND_DIR, &CDiaControlMenu::OnEnChangeEditAllWindDir)
	ON_BN_CLICKED(IDC_CHECK_ALL_WIND, &CDiaControlMenu::OnBnClickedCheckAllWind)
	ON_EN_CHANGE(IDC_EDIT_WIND_DIR_1, &CDiaControlMenu::OnEnChangeEditWindDir1)
	ON_BN_CLICKED(IDC_CHECK2_ARROW, &CDiaControlMenu::OnBnClickedCheck2Arrow)
	ON_BN_CLICKED(IDC_CHECK_SPHERE, &CDiaControlMenu::OnBnClickedCheckSphere)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TIME_SPAN, &CDiaControlMenu::OnNMCustomdrawSliderTimeSpan)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RUN_TOTAL_TIME, &CDiaControlMenu::OnNMCustomdrawSliderRunTotalTime)
	ON_BN_CLICKED(IDC_CHECK_VALUE, &CDiaControlMenu::OnBnClickedCheckValue)
	ON_BN_CLICKED(IDC_CHECK_FLIGHT_PATH, &CDiaControlMenu::OnBnClickedCheckFlightPath)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_CURRENT_POSITION, &CDiaControlMenu::OnBnClickedCheckDisplayCurrentPosition)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_ALL_RANGE_SPHERE, &CDiaControlMenu::OnBnClickedCheckDisplayAllRangeSphere)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SYMBOL_SIZE2, &CDiaControlMenu::OnNMCustomdrawSliderSymbolSize2)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALT_TOP, &CDiaControlMenu::OnNMCustomdrawSliderAltTop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALT_BTM, &CDiaControlMenu::OnNMCustomdrawSliderAltBtm)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_MAP, &CDiaControlMenu::OnBnClickedCheckDisplayMap)
	ON_BN_CLICKED(IDC_RADIO_2D, &CDiaControlMenu::OnBnClickedRadio2d)
	ON_BN_CLICKED(IDC_RADIO_2D2, &CDiaControlMenu::OnBnClickedRadio2d2)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDiaControlMenu::OnBnClickedButtonReset)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_OFFSET_TIME, &CDiaControlMenu::OnNMCustomdrawSliderOffsetTime)
	ON_BN_CLICKED(IDC_CHECK_ALT_DISPLAY, &CDiaControlMenu::OnBnClickedCheckAltDisplay)
END_MESSAGE_MAP()



void CDiaControlMenu::OnEnChangeEditWindSpeed3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnEnChangeEditWindSpeed1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnEnChangeEditAltUp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnBnClickedRadioMsnValue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nSymbolType = 0;
	

}

void CDiaControlMenu::OnBnClickedRadioWind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nSymbolType = 1;

}

void CDiaControlMenu::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	



	//UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}

void CDiaControlMenu::OnBnClickedButtonConform()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);

	g_Interface.m_nDron_1 = atoi(m_strDron_1.GetBuffer());
	g_Interface.m_nDron_2= atoi(m_strDron_2.GetBuffer());
	g_Interface.m_nDron_3= atoi(m_strDron_3.GetBuffer());
	g_Interface.m_nMsnValue_1= atoi(m_strMsnValue_1.GetBuffer());
	g_Interface.m_nMsnValue_2= atoi(m_strMsnValue_2.GetBuffer());
	g_Interface.m_nMsnValue_3= atoi(m_strMsnValue_3.GetBuffer());
	g_Interface.m_nWindDir_1= atoi(m_strWindDir_1.GetBuffer());
	g_Interface.m_nWindDir_2= atoi(m_strWindDir_2.GetBuffer());
	g_Interface.m_nWindDir_3= atoi(m_strWindDir_3.GetBuffer());
	g_Interface.m_nWindSpeed_1= atoi(m_strWindSpeed_1.GetBuffer());
	g_Interface.m_nWindSpeed_2= atoi(m_strWindSpeed_2.GetBuffer());
	g_Interface.m_nWindSpeed_3= atoi(m_strWindSpeed_3.GetBuffer());
	g_Interface.m_nAltUp= atoi(m_strAltUp.GetBuffer());
	g_Interface.m_nAltDown= atoi(m_strAltDown.GetBuffer());


	g_Interface.m_fAllWindDir= atoi(m_strAllWindDir.GetBuffer());
	g_Interface.m_fAllWindSpeed= atoi(m_strAllWindSpeed.GetBuffer());

	g_Interface.m_fAllMissionData= atoi(m_strMissionData.GetBuffer());


}

void CDiaControlMenu::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nStatus  = 1;
	g_UAVTimer.SetPlay();
}

void CDiaControlMenu::OnBnClickedButtonPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nStatus  = 0;
	g_UAVTimer.SetPause();
}



void CDiaControlMenu::OnEnChangeEditEndTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CDiaControlMenu::OnNMCustomdrawSliderSymbolSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	g_Interface.m_fSymbolSize = (float) (m_sliderSymbolSize.GetPos()/100.0f);



	UpdateData(false);



	*pResult = 0;
}

BOOL CDiaControlMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderSymbolSize.SetRange(10,100,0);
	m_sliderTimeSpan.SetRange(0,1000,0);
	m_sliderRunTotalTime.SetRange(0,7,0);
	m_sliderOffsetTime.SetRange(0,999,0);
	m_sliderSphereSymbolSize.SetRange(10,100,0);
	m_sliderAltTop.SetRange(1,5000,0);
	m_sliderAltBtm.SetRange(0,2000,0);


	//m_sliderRunTotalTime.SetRange(0,m_nRunTime,0);


	m_nRunTime = (int) g_Interface.m_fTotalRunTime;



	// 체크 버튼 초기화
	CButton* pButton = (CButton*)GetDlgItem(IDC_CHECK_DISPLAY_CURRENT_POSITION);
	pButton->SetCheck(true); 
	m_chkBtnCurrentData.SetCheck(BST_CHECKED);
	
	pButton = (CButton*)GetDlgItem(IDC_CHECK_SPHERE);
	pButton->SetCheck(true); 
//	m_chkBtnCurrentData.SetCheck(BST_CHECKED);
	SetTimer(0, 100,NULL);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDiaControlMenu::OnEnChangeEditAllWindSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnEnChangeEditAllWindDir()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnBnClickedCheckAllWind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	g_Interface.m_nAllWIndChange = 1 - g_Interface.m_nAllWIndChange;
}

void CDiaControlMenu::OnEnChangeEditWindDir1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnBnClickedCheck2Arrow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nOnArrowSymbol= 1 - g_Interface.m_nOnArrowSymbol;
	
}

void CDiaControlMenu::OnBnClickedCheckSphere()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	g_Interface.m_nOnSphereSymbol =  1 - g_Interface.m_nOnSphereSymbol;



}

void CDiaControlMenu::OnNMCustomdrawSliderTimeSpan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	g_Interface.m_fTimeSpan = m_sliderTimeSpan.GetPos();

	g_Interface.m_fStartTime = g_Interface.m_fEndTime - g_Interface.m_fTimeSpan;
	if( g_Interface.m_fStartTime < 0.0f)
	{
		g_Interface.m_fStartTime = 0.0f;
	}

//	g_Interface.m_fStartTime= atoi(GetBuffer());

	m_strTimeSpan.Format("%.0f", g_Interface.m_fTimeSpan);
	m_strStartTime.Format("%.0f", g_Interface.m_fStartTime);
	UpdateData(false);


//	g_Interface.m_fEndTime= atoi(m_strEndTime.GetBuffer());

	*pResult = 0;
}


void CDiaControlMenu::OnNMCustomdrawSliderRunTotalTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float	fStartTime; 
	float	fOffsetTime;

	// 최종 수신 시간에서 부터의 Offset 시간

	g_Interface.m_fOffset100Digit = m_sliderRunTotalTime.GetPos();


    m_nOffsetTime = g_Interface.m_fOffset100Digit * 1000 +  g_Interface.m_fOffsetDigit;


	m_nTimeEnd = m_nOffsetTime;

	g_Interface.m_fOffsetTime = m_nOffsetTime;


	UpdateData(false); 

	*pResult = 0;
}




void CDiaControlMenu::OnBnClickedCheckValue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nDigitalValueData = 1 - g_Interface.m_nDigitalValueData ;
}

void CDiaControlMenu::OnBnClickedCheckFlightPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nFlightPathLine =  1 - g_Interface.m_nFlightPathLine;
	
}

void CDiaControlMenu::OnBnClickedCheckDisplayCurrentPosition()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nCurrentReceiveData = 1 - g_Interface.m_nCurrentReceiveData;
}

void CDiaControlMenu::OnBnClickedCheckDisplayAllRangeSphere()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nAllReange = 1 - g_Interface.m_nAllReange;
}


// Mission Data 값 표시 심볼 크기 조종
void CDiaControlMenu::OnNMCustomdrawSliderSymbolSize2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	g_Interface.m_nSphereSymbolSize = (float) (m_sliderSphereSymbolSize.GetPos()/10.0f);

	UpdateData(false);



	*pResult = 0;
}

void CDiaControlMenu::OnEnChangeEditRunTotalTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




void CDiaControlMenu::OnEnChangeEditAltTop()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDiaControlMenu::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDiaControlMenu::OnNMCustomdrawSliderAltTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	g_Interface.m_nAltUp =  m_sliderAltTop.GetPos();

	m_strAltUp.Format("%d", g_Interface.m_nAltUp);
	UpdateData(false);


	*pResult = 0;
}


void CDiaControlMenu::OnNMCustomdrawSliderAltBtm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	g_Interface.m_nAltDown = m_sliderAltBtm.GetPos();
	m_strAltDown.Format("%d", g_Interface.m_nAltDown);

	UpdateData(false);
	*pResult = 0;
}

void CDiaControlMenu::OnBnClickedCheckDisplayMap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	g_Interface.m_nMapDisplay = 1 - g_Interface.m_nMapDisplay;

}

void CDiaControlMenu::OnBnClickedRadio2d()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	gGL_FLightPath.m_nDrawType = 0;

}

void CDiaControlMenu::OnBnClickedRadio2d2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	gGL_FLightPath.m_nDrawType = 1;


}

void CDiaControlMenu::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i =0;

	for(i=0;i<MAX_DRON;i++)
	{
		g_Interface.RingBufUDP_IGS[i].nFront = 0;
		g_Interface.RingBufUDP_IGS[i].nRear = 0;

	}
	g_UAVTimer.SetElapseTime(0.0);
	g_UAVTimer.SetPause();
	g_Interface.m_nStatus  = 0;

}

void CDiaControlMenu::OnNMCustomdrawSliderOffsetTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_fOffsetDigit = m_sliderOffsetTime.GetPos();

    m_nOffsetTime = g_Interface.m_fOffset100Digit * 1000 +  g_Interface.m_fOffsetDigit;


	m_nTimeEnd = m_nOffsetTime;

	g_Interface.m_fOffsetTime = m_nOffsetTime;

	UpdateData(false); 
	*pResult = 0;
}

void CDiaControlMenu::OnBnClickedCheckAltDisplay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_Interface.m_nDisplayAltRange = 1 - g_Interface.m_nDisplayAltRange;
}
