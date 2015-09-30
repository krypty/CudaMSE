#ifndef MANDELBROT_MATH_H_
#define MANDELBROT_MATH_H_

#include "CalibreurF.h"
#include "ColorTools.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class MandelbrotMath
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
	MandelbrotMath(int n) :
		calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    }

	virtual ~MandelbrotMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, double t)
	    {
	    float z = f(x, y, t);

	    calibreur.calibrer(z);
	    float hue01 = z;

	    ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

	    ptrColor->w = 255; // opaque
	    }

    private:

	double f(double x, double y, double t)
	    {
	    return sin(x * n + t) * cos(y * n + t); // t para animation
	    }

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;

	// Tools
	CalibreurF calibreur;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
