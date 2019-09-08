// eGL.cpp: implementation of the eGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "eGL.h"

/*----------------------------------------------
	GL Emulator
					1999. 10. 14	C.C.I
-----------------------------------------------*/

/*==========================< System Matrix >===============================*/
Matrix tM = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

eGL::eGL()
{
	m_SP = 0;							/* matrix stack pointer */
	gmatrixcpy( m_IM, tM );
}

eGL::~eGL()
{
}

void
eGL::LoadMatrix( double* m )
{
	gmatrixcpy( m_MVM, m );
}

void
eGL::LoadIdentity()
{
	m_SP = 0;							/* matrix stack pointer */
	gmatrixcpy(m_MVM, m_IM);
}

void
eGL::GetMatrix( double* m )
{
	gmatrixcpy(m, m_MVM);
}

void
eGL::PushMatrix(void)
{
	if ( m_SP >= 49 )
	{
		printf("GL Error : Too many matrix pushed into stack !\007\n");
		return;
	}
	gmatrixcpy( m_SM[m_SP], m_MVM );
	m_SP++;
}

void
eGL::PopMatrix(void)
{
	if ( m_SP <= 0 ) {
		printf("GL Error : Too many matrix poped from stack !\007\n");
		m_SP = 0;
		return;
	}
	m_SP--;
	gmatrixcpy( m_MVM, m_SM[m_SP] );
}

void
eGL::Translatef(float dx, float dy, float dz)
{
	Matrix s;

	gmatrixcpy(s, m_MVM);
	m_MVM[3][0] = s[0][0]*dx + s[1][0]*dy + s[2][0]*dz + s[3][0];
	m_MVM[3][1] = s[0][1]*dx + s[1][1]*dy + s[2][1]*dz + s[3][1];
	m_MVM[3][2] = s[0][2]*dx + s[1][2]*dy + s[2][2]*dz + s[3][2];
	m_MVM[3][3] = s[0][3]*dx + s[1][3]*dy + s[2][3]*dz + s[3][3];
}

void
eGL::Translated(double dx, double dy, double dz)
{
	Matrix s;

	gmatrixcpy(s, m_MVM);
	m_MVM[3][0] = s[0][0]*dx + s[1][0]*dy + s[2][0]*dz + s[3][0];
	m_MVM[3][1] = s[0][1]*dx + s[1][1]*dy + s[2][1]*dz + s[3][1];
	m_MVM[3][2] = s[0][2]*dx + s[1][2]*dy + s[2][2]*dz + s[3][2];
	m_MVM[3][3] = s[0][3]*dx + s[1][3]*dy + s[2][3]*dz + s[3][3];
}

void
eGL::Rotatef(float a, char axis)
{
	switch(axis) {
		case 'x':
			grotx(m_MVM, (float)sin(a*D2R), (float)cos(a*D2R));
			break;
		case 'y':
			groty(m_MVM, (float)sin(a*D2R), (float)cos(a*D2R));
			break;
		case 'z':
			grotz(m_MVM, (float)sin(a*D2R), (float)cos(a*D2R));
			break;
		default:
			printf("VGL Error : unknown axis name '%c'.\n",axis);
			break;
	}
}

void
eGL::Rotated(double a, char axis)
{
	switch(axis) {
		case 'x':
			grotx(m_MVM, sin(a*D2R), cos(a*D2R));
			break;
		case 'y':
			groty(m_MVM, sin(a*D2R), cos(a*D2R));
			break;
		case 'z':
			grotz(m_MVM, sin(a*D2R), cos(a*D2R));
			break;
		default:
			printf("VGL Error : unknown axis name '%c'.\n",axis);
			break;
	}
}

void
eGL::RotAxisf(float a, float x, float y, float z )
{
	double	sinph, cosph;
	double	sinth, costh;
	double	d1, d2;

	if ( y == 0.0 && z == 0.0 )
	{
		if( x == -1.0f )
		{
			x *= -1.0f;
			a *= -1.0f;
		}
		grotx( m_MVM,  sin(a*D2R),	cos(a*D2R) );
		return;
	}
	else if ( x == 0.0 && z == 0.0 )
	{
		if( y == -1.0f )
		{
			y *= -1.0f;
			a *= -1.0f;
		}
		groty( m_MVM,  sin(a*D2R),	cos(a*D2R) );
		return;
	}
/*	else if ( x == 0.0 && y == 0.0 )
	{
		grotz( m_MVM, -sin(a*D2R),	cos(a*D2R) );
		return;
	}
*/
	d1 = sqrt( y*y + z*z );
	d2 = sqrt( x*x + y*y + z*z );

	sinph = y / d1;
	cosph = z / d1;

	sinth = x / d2;
	costh = d1 / d2;

	grotx( m_MVM, -sinph,		cosph );
	groty( m_MVM,  sinth,		costh );
	grotz( m_MVM,  sin(a*D2R),	cos(a*D2R) );
	groty( m_MVM, -sinth,		costh );
	grotx( m_MVM,  sinph,		cosph );
}

void
eGL::RotAxisd(double a, double x, double y, double z )
{
	double	sinph, cosph;
	double	sinth, costh;
	double	d1, d2;

	if ( y == 0.0 && z == 0.0 )
	{
		if( x == -1.0f )
		{
			x *= -1.0f;
			a *= -1.0f;
		}
		grotx( m_MVM,  sin(a*D2R),	cos(a*D2R) );
		return;
	}
	else if ( x == 0.0 && z == 0.0 )
	{
		if( y == -1.0f )
		{
			y *= -1.0f;
			a *= -1.0f;
		}
		groty( m_MVM,  sin(a*D2R),	cos(a*D2R) );
		return;
	}

	d1 = sqrt( y*y + z*z );
	d2 = sqrt( x*x + y*y + z*z );

	sinph = y / d1;
	cosph = z / d1;

	sinth = x / d2;
	costh = d1 / d2;

	grotx( m_MVM, -sinph,		cosph );
	groty( m_MVM,  sinth,		costh );
	grotz( m_MVM,  sin(a*D2R),	cos(a*D2R) );
	groty( m_MVM, -sinth,		costh );
	grotx( m_MVM,  sinph,		cosph );
}

void
eGL::Scalef(float x, float y, float z)
{
	static Matrix src ={ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	Matrix	s;

	memcpy( s, src, sizeof(Matrix) );

	s[0][0] = x;	s[1][1] = y;	s[2][2] = z;
	gmatrixmul(s, m_MVM);
	gmatrixcpy(m_MVM, s);
}

void
eGL::Scaled(double x, double y, double z)
{
	static Matrix src ={ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	Matrix	s;

	memcpy( s, src, sizeof(Matrix) );

	s[0][0] = x;	s[1][1] = y;	s[2][2] = z;
	gmatrixmul(s, m_MVM);
	gmatrixcpy(m_MVM, s);
}

void
eGL::gmatrixmul( Matrix t, Matrix s)
{
	int i,j;
	Matrix tmp;

	gmatrixcpy(tmp,t);
	for ( i=0; i<4; i++)
	{
		for ( j=0; j<4; j++) 
		{
			t[i][j] = tmp[i][0] * s[0][j] + tmp[i][1] * s[1][j] + \
				tmp[i][2] * s[2][j] + tmp[i][3] * s[3][j];
		}
	}
}

void
eGL::grotate(int m0, int m1, int m2, int m3, int m4, int m5, double sinth, double costh)
{
	Matrix s;

	gmatrixcpy( s, m_MVM);

	m_MVM[m0][0] = s[m1][0]*costh+s[m2][0]*sinth;
	m_MVM[m0][1] = s[m1][1]*costh+s[m2][1]*sinth;
	m_MVM[m0][2] = s[m1][2]*costh+s[m2][2]*sinth;
	m_MVM[m0][3] = s[m1][3]*costh+s[m2][3]*sinth;

	m_MVM[m3][0] = -s[m4][0]*sinth+s[m5][0]*costh;
	m_MVM[m3][1] = -s[m4][1]*sinth+s[m5][1]*costh;
	m_MVM[m3][2] = -s[m4][2]*sinth+s[m5][2]*costh;
	m_MVM[m3][3] = -s[m4][3]*sinth+s[m5][3]*costh;
}

void
eGL::grotx(Matrix m, double sinth, double costh)
{
	Matrix s;

	gmatrixcpy(s, m);
	
	m[1][0] = s[1][0]*costh+s[2][0]*sinth;
	m[1][1] = s[1][1]*costh+s[2][1]*sinth;
	m[1][2] = s[1][2]*costh+s[2][2]*sinth;
	m[1][3] = s[1][3]*costh+s[2][3]*sinth;

	m[2][0] = -s[1][0]*sinth+s[2][0]*costh;
	m[2][1] = -s[1][1]*sinth+s[2][1]*costh;
	m[2][2] = -s[1][2]*sinth+s[2][2]*costh;
	m[2][3] = -s[1][3]*sinth+s[2][3]*costh;
}

void
eGL::groty(Matrix m, double sinth, double costh)
{
	Matrix s;

	gmatrixcpy(s, m);
	
	m[0][0] = s[0][0]*costh-s[2][0]*sinth;
	m[0][1] = s[0][1]*costh-s[2][1]*sinth;
	m[0][2] = s[0][2]*costh-s[2][2]*sinth;
	m[0][3] = s[0][3]*costh-s[2][3]*sinth;

	m[2][0] = s[0][0]*sinth+s[2][0]*costh;
	m[2][1] = s[0][1]*sinth+s[2][1]*costh;
	m[2][2] = s[0][2]*sinth+s[2][2]*costh;
	m[2][3] = s[0][3]*sinth+s[2][3]*costh;
}

void
eGL::grotz(Matrix m, double sinth, double costh)
{
	Matrix s;

	gmatrixcpy(s, m);
	
	m[0][0] = s[0][0]*costh+s[1][0]*sinth;
	m[0][1] = s[0][1]*costh+s[1][1]*sinth;
	m[0][2] = s[0][2]*costh+s[1][2]*sinth;
	m[0][3] = s[0][3]*costh+s[1][3]*sinth;

	m[1][0] = -s[0][0]*sinth+s[1][0]*costh;
	m[1][1] = -s[0][1]*sinth+s[1][1]*costh;
	m[1][2] = -s[0][2]*sinth+s[1][2]*costh;
	m[1][3] = -s[0][3]*sinth+s[1][3]*costh;
}

void
eGL::gxlat(Matrix m, double tx, double ty, double tz)
{
	Matrix s;

	gmatrixcpy(s, m);
	
	m[3][0] = s[0][0]*tx + s[1][0]*ty + s[2][0]*tz + s[3][0];
	m[3][1] = s[0][1]*tx + s[1][1]*ty + s[2][1]*tz + s[3][1];
	m[3][2] = s[0][2]*tx + s[1][2]*ty + s[2][2]*tz + s[3][2];
	m[3][3] = s[0][3]*tx + s[1][3]*ty + s[2][3]*tz + s[3][3];
}

void
eGL::PassMVMfv( float *o, float *w )
{
	w[0] = (float)( m_MVM[0][0]*o[0] +m_MVM[1][0]*o[1] +m_MVM[2][0]*o[2] +m_MVM[3][0] );
	w[1] = (float)( m_MVM[0][1]*o[0] +m_MVM[1][1]*o[1] +m_MVM[2][1]*o[2] +m_MVM[3][1] );
	w[2] = (float)( m_MVM[0][2]*o[0] +m_MVM[1][2]*o[1] +m_MVM[2][2]*o[2] +m_MVM[3][2] );
}

void
eGL::PassMVMf( float ox, float oy, float oz, float *w )
{
	w[0] = (float)( m_MVM[0][0]*ox +m_MVM[1][0]*oy +m_MVM[2][0]*oz +m_MVM[3][0] );
	w[1] = (float)( m_MVM[0][1]*ox +m_MVM[1][1]*oy +m_MVM[2][1]*oz +m_MVM[3][1] );
	w[2] = (float)( m_MVM[0][2]*ox +m_MVM[1][2]*oy +m_MVM[2][2]*oz +m_MVM[3][2] );
}

void
eGL::PassMVMdv( double *o, double *w )
{
	w[0] = m_MVM[0][0]*o[0] +m_MVM[1][0]*o[1] +m_MVM[2][0]*o[2] +m_MVM[3][0];
	w[1] = m_MVM[0][1]*o[0] +m_MVM[1][1]*o[1] +m_MVM[2][1]*o[2] +m_MVM[3][1];
	w[2] = m_MVM[0][2]*o[0] +m_MVM[1][2]*o[1] +m_MVM[2][2]*o[2] +m_MVM[3][2];
}

void
eGL::PassMVMd( double ox, double oy, double oz, double *w )
{
	w[0] = m_MVM[0][0]*ox +m_MVM[1][0]*oy +m_MVM[2][0]*oz +m_MVM[3][0];
	w[1] = m_MVM[0][1]*ox +m_MVM[1][1]*oy +m_MVM[2][1]*oz +m_MVM[3][1];
	w[2] = m_MVM[0][2]*ox +m_MVM[1][2]*oy +m_MVM[2][2]*oz +m_MVM[3][2];
}

eGL::IsBackfacef( float* v1, float* v2, float* v3 )
{
	float w[3][3];
	float xa, ya, xb, yb;

	PassMVMfv( v1, w[0] );
	PassMVMfv( v2, w[1] );
	PassMVMfv( v3, w[2] );

	xa = w[1][0] - w[0][0];
	ya = w[1][1] - w[0][1];

	xb = w[2][0] - w[0][0];
	yb = w[2][1] - w[0][1];

	if ( xa*yb - xb*ya > 0.0f )
		return 1;		//TRUE;
	else
		return 0;		//FALSE;
}
