#pragma once


class CEasyMouse
{
public:
	bool			m_RightMouseDown;
	bool			m_LeftMouseDown;

	int				m_nWinOrgX;
    int				m_nWinOrgY;


    int				m_nWinWidth;
    int				m_nWinHeight;


	float			m_fWheel;
	float			m_fDistance;
	float			m_fAzimuth;
	float			m_fIncidence;
	float			m_fZoom; // wheel ¿¡ ¿¬µ¿ 

	float			m_fPanX;
	float			m_fPanY;
	float			m_fPrePanX;
	float			m_fPrePanY;
	float			m_fScale;

	float			m_fPan3DX;
	float			m_fPan3DY;
	float			m_fPan3DXRotate;
	float			m_fPan3DYRotate;
	float			m_fPrePan3DX;
	float			m_fPrePan3DY;

 
	float			m_pickPosX;
	float			m_pickPosY;

	float			m_fPressedX;
	float			m_fPressedY;

	float			m_fReleasedX;
	float			m_fReleasedY;

	float			m_fPosX;
	float			m_fPosY;

	float			m_fPrePosX;
	float			m_fPrePosY;

	int				m_nShiftKey;
	int				m_nCtrlKey;


	int				m_nUpKey;
	int				m_nDownKey;
	int				m_nLeftKey;
	int				m_nRightKey;




	
public:
	CEasyMouse(void);
	~CEasyMouse(void);
};
