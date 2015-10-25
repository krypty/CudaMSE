#ifndef MANDELBROTBASE_MATH_H_
#define MANDELBROTBASE_MATH_H_

#include <math.h>
#include "ColorTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMathBase
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	MandelbrotMathBase(int n)
	    {
	    this->n = n;
	    }

	__device__
	virtual ~MandelbrotMathBase(void)
	    {
	    //nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, double x, double y)
	    {
	    int k = getK(x, y);

	    if (k <= this->n)
		{
		// on scale le k sur la plage du hue [0, 1]. Similaire à un calibreur
		float hue01 = (1.0 / this->n) * k;

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

    protected:

	__device__
	virtual int getK(float x, float y)=0;

	__device__
	bool isDivergent(float a, float b)
	    {
	    return (a * a + b * b) > 4;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	int n;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
