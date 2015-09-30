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
	MandelbrotMath() :
		calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    //this->n = n;
	    }

	virtual ~MandelbrotMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, const int N)
	    {
	    int k = f(x, y, N);

	    if(k <= N)
		{
		// on scale le k sur la plage du hue [0, 1]. Siimilaire à un calibreur
		float hue01 = (1.0/N) * k;

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    ptrColor->w = 255; // opaque
	    }

    private:

	bool isDivergent(float a, float b)
	    {
	    return (a*a + b*b) > 4;
	    }

	int f(double x, double y, int N)
	    {
	    float a = 0;
	    float b = 0;

	    int k = 0;

	    while(!isDivergent(a, b) && k <= N)
		{
		float aCopy = a;
		a = (aCopy*aCopy - b*b) + x;
		b = 2.0 * aCopy * b + y;

		k++;
		}

	    return k;
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
