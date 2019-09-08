
// UAVSimEmulatorView.cpp : CUAVSimEmulatorView Ŭ������ ����
//

#include "stdafx.h"
#include "UAVSimEmulator.h"

#include "UAVSimEmulatorDoc.h"
#include "UAVSimEmulatorView.h"

#include "EasyOpenGL.h"
#include "CASSGL.h"

#include "GL_IntruderFlight.h"

CGL_IntruderFlight  gGL_IntruderFlight;
CGL_FlightTrack		gGL_FLightPath;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAVSimEmulatorView

IMPLEMENT_DYNCREATE(CUAVSimEmulatorView, CView)

BEGIN_MESSAGE_MAP(CUAVSimEmulatorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUAVSimEmulatorView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_2D_DISPLAY, &CUAVSimEmulatorView::On2dDisplay)
	ON_COMMAND(ID_3D_DISPLAY, &CUAVSimEmulatorView::On3dDisplay)
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CUAVSimEmulatorView ����/�Ҹ�

CUAVSimEmulatorView::CUAVSimEmulatorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CUAVSimEmulatorView::~CUAVSimEmulatorView()
{
}

BOOL CUAVSimEmulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.















	return CView::PreCreateWindow(cs);
}

// CUAVSimEmulatorView �׸���

void CUAVSimEmulatorView::OnDraw(CDC* /*pDC*/)
{
	CUAVSimEmulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	gGL_FLightPath.Server();





}


// CUAVSimEmulatorView �μ�


void CUAVSimEmulatorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CUAVSimEmulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CUAVSimEmulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CUAVSimEmulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}



void CUAVSimEmulatorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CUAVSimEmulatorView ����

#ifdef _DEBUG
void CUAVSimEmulatorView::AssertValid() const
{
	CView::AssertValid();
}

void CUAVSimEmulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUAVSimEmulatorDoc* CUAVSimEmulatorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUAVSimEmulatorDoc)));
	return (CUAVSimEmulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CUAVSimEmulatorView �޽��� ó����

void CUAVSimEmulatorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	RECT winRect;
	GetClientRect(&winRect);

	if( cx > 100 &&  cy > 100)
	{
		gGL_FLightPath.SetCanvas(&winRect);
		gGL_FLightPath.ResizeRC( cx, cy );
	}
}

int CUAVSimEmulatorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	gGL_FLightPath.KCEICreate(m_hWnd);

	wglMakeCurrent(gGL_FLightPath.m_hGLDC, gGL_FLightPath.m_hGLRC);

		gGL_FLightPath.m_CMyTexture.InitTexture( MAX_TEXTURE );
		gGL_FLightPath.m_CDDSTexture.InitTexture( MAX_TEXTURE );
		gGL_FLightPath.ReadDyanamicMapTextureFile("DataFileList/dynamicMap.txt");
	// �������� �������� ������ ���� ������ �б� 
		gGL_FLightPath.ReadDDSTextureFile("DataFileList/ddsmap.txt" );
	
		gGL_FLightPath.LoadTexture();



	wglMakeCurrent(gGL_FLightPath.m_hGLDC, NULL);
	



	m_DiaControlMenu.Create(IDD_DIALOG_CONTROL_MENU, this);
	m_DiaControlMenu.ShowWindow(SW_SHOW);

	SetTimer(0,66,NULL);

	return 0;
}

void CUAVSimEmulatorView::On2dDisplay()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	gGL_FLightPath.m_nDrawType = 0;
}

void CUAVSimEmulatorView::On3dDisplay()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		gGL_FLightPath.m_nDrawType = 1;

}

void CUAVSimEmulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(FALSE);	
	CView::OnTimer(nIDEvent);
}


BOOL CUAVSimEmulatorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	float	fWheelValue;
		gGL_FLightPath.EasyMouse.m_fWheel += (float)(zDelta/12.0f);
		if( gGL_FLightPath.EasyMouse.m_fWheel < 0.01f) gGL_FLightPath.EasyMouse.m_fWheel = 0.01f;
		if( gGL_FLightPath.EasyMouse.m_fWheel > 1000.0f) gGL_FLightPath.EasyMouse.m_fWheel = 1000.0f;

		fWheelValue = (float)(zDelta/120.0f);


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CUAVSimEmulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	gGL_FLightPath.EasyMouse.m_fPressedX = point.x;
	gGL_FLightPath.EasyMouse.m_fPressedY = point.y;
	gGL_FLightPath.EasyMouse.m_LeftMouseDown = 1;

	CView::OnLButtonDown(nFlags, point);
}

void CUAVSimEmulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	gGL_FLightPath.EasyMouse.m_fReleasedX = point.x;
	gGL_FLightPath.EasyMouse.m_fReleasedY = point.y;
	
	// Mouse Panning
	gGL_FLightPath.EasyMouse.m_LeftMouseDown = 0;
	if(gGL_FLightPath.m_nDrawType == 0)
	{
		gGL_FLightPath.EasyMouse.m_fPrePanX =gGL_FLightPath.EasyMouse.m_fPanX;
		gGL_FLightPath.EasyMouse.m_fPrePanY =gGL_FLightPath.EasyMouse.m_fPanY;
	}
	else
	{
		gGL_FLightPath.EasyMouse.m_fPrePan3DX = gGL_FLightPath.EasyMouse.m_fPan3DX;
		gGL_FLightPath.EasyMouse.m_fPrePan3DY = gGL_FLightPath.EasyMouse.m_fPan3DY;
	}
	// Draw type select
	if( point.y > 0 && point.y < 25 )
	{
		if( point.x > 10 && point.x < 70)
		{
			gGL_FLightPath.m_nDrawType = 0;
		}
		else if( point.x > 80 &&  point.x < 140 )
		{
			gGL_FLightPath.m_nDrawType = 1;
		}

	}
	CView::OnLButtonUp(nFlags, point);
}

void CUAVSimEmulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		gGL_FLightPath.EasyMouse.m_fPosX = point.x;
		gGL_FLightPath.EasyMouse.m_fPosY = point.y;


		if( gGL_FLightPath.EasyMouse.m_fPrePosX !=gGL_FLightPath. EasyMouse.m_fPosX || gGL_FLightPath.EasyMouse.m_fPrePosY != gGL_FLightPath.EasyMouse.m_fPosY)
		{
			if (gGL_FLightPath.EasyMouse.m_LeftMouseDown == TRUE)
			{
				if(gGL_FLightPath.m_nViewMode == ORTHO_MODE)
				{
					gGL_FLightPath.EasyMouse.m_fPanX =gGL_FLightPath.EasyMouse.m_fPrePanX+ (gGL_FLightPath.EasyMouse.m_fPosX - gGL_FLightPath.EasyMouse.m_fPressedX);
					gGL_FLightPath.EasyMouse.m_fPanY =gGL_FLightPath.EasyMouse.m_fPrePanY+ (gGL_FLightPath.EasyMouse.m_fPosY - gGL_FLightPath.EasyMouse.m_fPressedY);
				}
				else
				{
					if( gGL_FLightPath.EasyMouse.m_nShiftKey == 0 )
					{
						gGL_FLightPath.EasyMouse.m_fAzimuth+=((gGL_FLightPath.EasyMouse.m_fPrePosX - gGL_FLightPath.EasyMouse.m_fPosX)*0.1f);
						if( gGL_FLightPath.EasyMouse.m_fAzimuth > 360.0f) gGL_FLightPath.EasyMouse.m_fAzimuth-=360.0f;


						gGL_FLightPath.EasyMouse.m_fIncidence+=((gGL_FLightPath.EasyMouse.m_fPrePosY - gGL_FLightPath.EasyMouse.m_fPosY)*0.1);

						if( gGL_FLightPath.EasyMouse.m_fIncidence > 90.0f) gGL_FLightPath.EasyMouse.m_fIncidence = 90.0f;
						if( gGL_FLightPath.EasyMouse.m_fIncidence < 5.0f) gGL_FLightPath.EasyMouse.m_fIncidence = 5.0f;
					}
					else
					{
						gGL_FLightPath.EasyMouse.m_fPan3DX =gGL_FLightPath.EasyMouse.m_fPrePan3DX+ (gGL_FLightPath.EasyMouse.m_fPosX - gGL_FLightPath.EasyMouse.m_fPressedX);
						gGL_FLightPath.EasyMouse.m_fPan3DY =gGL_FLightPath.EasyMouse.m_fPrePan3DY+ (gGL_FLightPath.EasyMouse.m_fPosY - gGL_FLightPath.EasyMouse.m_fPressedY);


					}
				}
			}
			if( gGL_FLightPath.EasyMouse.m_RightMouseDown == TRUE)
			{
				if(gGL_FLightPath.EasyMouse.m_fPrePosY > gGL_FLightPath.EasyMouse.m_fPosY)
				{
					gGL_FLightPath.EasyMouse.m_fDistance/=1.05f;
					if ( gGL_FLightPath.EasyMouse.m_fDistance < 1.0f) gGL_FLightPath.EasyMouse.m_fDistance = 1.0f;
				}
				else 
				{
					gGL_FLightPath.EasyMouse.m_fDistance*=1.05f;
					if ( gGL_FLightPath.EasyMouse.m_fDistance > 160000.0f) gGL_FLightPath.EasyMouse.m_fDistance = 160000.0f;
				}

			}
			gGL_FLightPath.EasyMouse.m_fPrePosX = gGL_FLightPath.EasyMouse.m_fPosX;
			gGL_FLightPath.EasyMouse.m_fPrePosY = gGL_FLightPath.EasyMouse.m_fPosY;
		}
	CView::OnMouseMove(nFlags, point);
}

void CUAVSimEmulatorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		gGL_FLightPath.EasyMouse.m_RightMouseDown = true;

	CView::OnRButtonDown(nFlags, point);
}

void CUAVSimEmulatorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		gGL_FLightPath.EasyMouse.m_RightMouseDown = false;

	CView::OnRButtonUp(nFlags, point);
}



void CUAVSimEmulatorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	switch(nChar)
	{
	case 16 : //shift key
		gGL_FLightPath.EasyMouse.m_nShiftKey = 0;
		break;

	case 37 : //Left key
		gGL_FLightPath.EasyMouse.m_nLeftKey = 0;
		break;
	case 38 : //Up key
		gGL_FLightPath.EasyMouse.m_nUpKey = 0;
		break;
	case 39 : //Right key
		gGL_FLightPath.EasyMouse.m_nRightKey = 0;
		break;
	case 40 : //Down key
		gGL_FLightPath.EasyMouse.m_nDownKey = 0;
		break;
	case 112 :
		gGL_FLightPath.m_nDrawType = 0;
		break;
	case 113 :
		gGL_FLightPath.m_nDrawType = 1;
		break;
	default :
	//	gGL_FLightPath.m_nDrawType = 0;
		break;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CUAVSimEmulatorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(nChar)
	{
	case 16 : //shift key
		gGL_FLightPath.EasyMouse.m_nShiftKey = 1;
		break;
	case 37 : //Left key
		gGL_FLightPath.EasyMouse.m_nLeftKey = 1;
		break;
	case 38 : //Up key
		gGL_FLightPath.EasyMouse.m_nUpKey = 1;
		break;
	case 39 : //Right key
		gGL_FLightPath.EasyMouse.m_nRightKey = 1;
		break;
	case 40 : //Down key
		gGL_FLightPath.EasyMouse.m_nDownKey = 1;
		break;








	default :
	//	gGL_FLightPath.m_nDrawType = 0;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
