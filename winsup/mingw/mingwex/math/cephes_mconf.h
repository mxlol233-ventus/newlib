#include <math.h>
#include <errno.h>


#define IBMPC 1
#define ANSIPROT 1
#define MINUSZERO 1
#define INFINITIES 1
#define NANS 1
#define DENORMAL 1
#define VOLATILE
#define mtherr(fname, code) 
#define XPD 0,

#ifdef _CEPHES_USE_ERRNO
#define _SET_ERRNO(x) errno = (x)
#else
#define _SET_ERRNO(x)
#endif

/* constants used by cephes functions */

/* double */
#define MAXNUM	1.7976931348623158E308
#define MAXLOG	7.09782712893383996843E2
#define MINLOG	-7.08396418532264106224E2
#define LOGE2	6.93147180559945309417E-1
#define LOG2E	1.44269504088896340736
#define PI	3.14159265358979323846
#define PIO2	1.57079632679489661923
#define PIO4	7.85398163397448309616E-1

#define NEGZERO (-0.0)
extern double __INF;
#undef INFINITY
#define INFINITY (__INF)
extern double __QNAN;
#undef NAN
#define NAN (__QNAN)


/*long double*/
#define MAXNUML 1.189731495357231765021263853E4932L
#define MAXLOGL	1.1356523406294143949492E4L
#define MINLOGL	-1.13994985314888605586758E4L
#define LOGE2L	6.9314718055994530941723E-1L
#define LOG2EL	1.4426950408889634073599E0L
#define PIL	3.1415926535897932384626L
#define PIO2L	1.5707963267948966192313L
#define PIO4L	7.8539816339744830961566E-1L

#define isfinitel isfinite
#define isinfl isinf
#define isnanl isnan
#define signbitl signbit

#define NEGZEROL (-0.0L)
extern long double __INFL;
#define INFINITYL (__INFL)
extern long double __QNANL;
#define NANL (__QNANL)

/* float */

#define MAXNUMF	3.4028234663852885981170418348451692544e38F
#define MAXLOGF	88.72283905206835F
#define MINLOGF	-103.278929903431851103F /* log(2^-149) */
#define LOG2EF	1.44269504088896341F
#define LOGE2F	0.693147180559945309F
#define PIF	3.141592653589793238F
#define PIO2F	1.5707963267948966192F
#define PIO4F	0.7853981633974483096F

#define isfinitef isfinite
#define isinff isinf
#define isnanf isnan
#define signbitf signbit

#define NEGZEROF (-0.0F)
extern float __INFF;
#define INFINITYF (__INFF)
extern float __QNANF;
#define NANF (__QNANF)


/* double */

/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/


/*							polevl.c
 *							p1evl.c
 *
 *	Evaluate polynomial
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * double x, y, coef[N+1], polevl[];
 *
 * y = polevl( x, coef, N );
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates polynomial of degree N:
 *
 *                     2          N
 * y  =  C  + C x + C x  +...+ C x
 *        0    1     2          N
 *
 * Coefficients are stored in reverse order:
 *
 * coef[0] = C  , ..., coef[N] = C  .
 *            N                   0
 *
 *  The function p1evl() assumes that coef[N] = 1.0 and is
 * omitted from the array.  Its calling arguments are
 * otherwise the same as polevl().
 *
 *
 * SPEED:
 *
 * In the interest of speed, there are no checks for out
 * of bounds arithmetic.  This routine is used by most of
 * the functions in the library.  Depending on available
 * equipment features, the user may wish to rewrite the
 * program in microcode or assembly language.
 *
 */

/* Polynomial evaluator:
 *  P[0] x^n  +  P[1] x^(n-1)  +  ...  +  P[n]
 */
static  __inline__ double polevl( x, p, n )
double x;
const void *p;
int n;
{
register double y;
register double *P = (double *)p;

y = *P++;
do
	{
	y = y * x + *P++;
	}
while( --n );
return(y);
}



/* Polynomial evaluator:
 *  x^n  +  P[0] x^(n-1)  +  P[1] x^(n-2)  +  ...  +  P[n]
 */
static __inline__  double p1evl( x, p, n )
double x;
const void *p;
int n;
{
register double y;
register double *P = (double *)p;

n -= 1;
y = x + *P++;
do
	{
	y = y * x + *P++;
	}
while( --n );
return( y );
}


/* long double */
/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/


/*							polevll.c
 *							p1evll.c
 *
 *	Evaluate polynomial
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * long double x, y, coef[N+1], polevl[];
 *
 * y = polevll( x, coef, N );
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates polynomial of degree N:
 *
 *                     2          N
 * y  =  C  + C x + C x  +...+ C x
 *        0    1     2          N
 *
 * Coefficients are stored in reverse order:
 *
 * coef[0] = C  , ..., coef[N] = C  .
 *            N                   0
 *
 *  The function p1evll() assumes that coef[N] = 1.0 and is
 * omitted from the array.  Its calling arguments are
 * otherwise the same as polevll().
 *
 *
 * SPEED:
 *
 * In the interest of speed, there are no checks for out
 * of bounds arithmetic.  This routine is used by most of
 * the functions in the library.  Depending on available
 * equipment features, the user may wish to rewrite the
 * program in microcode or assembly language.
 *
 */

/* Polynomial evaluator:
 *  P[0] x^n  +  P[1] x^(n-1)  +  ...  +  P[n]
 */
static  __inline__ long double polevll( x, p, n )
long double x;
const void *p;
int n;
{
register long double y;
register long double *P = (long double *)p;

y = *P++;
do
	{
	y = y * x + *P++;
	}
while( --n );
return(y);
}



/* Polynomial evaluator:
 *  x^n  +  P[0] x^(n-1)  +  P[1] x^(n-2)  +  ...  +  P[n]
 */
static __inline__ long double p1evll( x, p, n )
long double x;
const void *p;
int n;
{
register long double y;
register long double *P = (long double *)p;

n -= 1;
y = x + *P++;
do
	{
	y = y * x + *P++;
	}
while( --n );
return( y );
}

