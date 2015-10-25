#ifndef JULIA_MATH_H_
#define JULIA_MATH_H_

#include <math.h>
#include "ColorTools.h"
#include "MandelbrotMathBase.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class JuliaMath: public MandelbrotMathBase
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
    JuliaMath(int n, float c1, float c2) :
		MandelbrotMathBase(n)
	    {
	    this->c1 = c1;
	    this->c2 = c2;
	    }

	__device__
    virtual ~JuliaMath(void)
	    {
	    // nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    protected:

	__device__
	virtual int getK(float x, float y)
	    {
	    float a = x;
	    float b = y;

	    int k = 0;

	    while (!isDivergent(a, b) && k <= this->n)
		{
		float aCopy = a;
		a = (aCopy * aCopy - b * b) + c1;
		b = 2.0 * aCopy * b + c2;

		k++;
		}

	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	float c1;
	float c2;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
