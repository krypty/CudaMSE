#ifndef MANDELBROT_MATH_H_
#define MANDELBROT_MATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(int n) :
		calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, const int N)
	    {
	    int k = getK(x, y, N);

	    if (k <= N)
		{
		// on scale le k sur la plage du hue [0, 1]. Similaire à un calibreur
		float hue01 = (1.0 / N) * k;

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

	__device__
	int getK(double x, double y, int N)
	    {
	    float a = 0;
	    float b = 0;

	    int k = 0;

	    while (!isDivergent(a, b) && k <= N)
		{
		float aCopy = a;
		a = (aCopy * aCopy - b * b) + x;
		b = 2.0 * aCopy * b + y;

		k++;
		}

	    return k;
	    }

	__device__
	bool isDivergent(float a, float b)
	    {
	    return (a * a + b * b) > 4;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

	// Tools
	CalibreurF calibreur;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
