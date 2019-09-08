// XRGL.h: interface for the XRGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EGL_H_INCLUDED_)
#define _EGL_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef	_D2R_DEFINED_
#define	_D2R_DEFINED_
#define D2R							(3.14159265358979323846264338327950288419716939937510 / 180.0 )
#endif

#ifndef	_R2D_DEFINED_
#define	_R2D_DEFINED_
#define R2D							( 180.0 / 3.14159265358979323846264338327950288419716939937510 )
#endif

#ifndef	_PI_DEFINED_
#define	_PI_DEFINED_
#define PI							3.14159265358979323846264338327950288419716939937510
#endif

#ifndef _MATRIX_DEFINED_
#define	_MATRIX_DEFINED_
typedef	double	Matrix[4][4];
#endif

#define	gmatrixcpy(x, y) memcpy(x, y, sizeof(Matrix))

class eGL  
{
private:
	Matrix  m_MVM;							/* model view matrix */
	Matrix  m_SM[50];						/* matrix stack */
	int	  	m_SP;							/* matrix stack pointer */
	Matrix	m_IM;

	void	gmatrixmul( Matrix t, Matrix s);
	void	grotate(int m0, int m1, int m2, int m3, int m4, int m5, double sinth, double costh);
	void	grotx(Matrix m, double sinth, double costh);
	void	groty(Matrix m, double sinth, double costh);
	void	grotz(Matrix m, double sinth, double costh);
	void	gxlat(Matrix m, double tx, double ty, double tz);

public:
	eGL();
	virtual ~eGL();

	void	PushMatrix(void);
	void	PopMatrix(void);
	void	FlushMatrixStack() { m_SP = 0; };

	void	LoadMatrix(double* m);
	void	LoadIdentity();
	void	GetMatrix(double* m);

	/////////// float func ///////////
	void	Translatef(float dx, float dy, float dz);
	void	Rotatef(float a, char axis);
	void	RotAxisf(float a, float x, float y, float z );
	void	Scalef(float x, float y, float z);

	void	PassMVMfv(float *o, float *w);
	void	PassMVMf(float ox, float oy, float oz, float *w);

	/////////// double func ///////////
	void	Translated(double dx, double dy, double dz);
	void	Rotated(double a, char axis);
	void	RotAxisd(double a, double x, double y, double z );
	void	Scaled(double x, double y, double z);

	void	PassMVMdv(double *o, double *w);
	void	PassMVMd(double ox, double oy, double oz, double *w);

	int		IsBackfacef( float* v1, float* v2, float* v3 );
};

#endif // !defined(_EGL_H_INCLUDED_)
