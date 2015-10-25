#ifndef NEWTON_MATH_H_
#define NEWTON_MATH_H_

#include <math.h>
#include <cfloat>
#include "ColorTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class NewtonMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	NewtonMath(float epsilon, int n)
	    {
        this->epsilon = epsilon;
	    this->n = n;
	    this->colorFactor = 25; // used to force to update the color

	    XA1 = 1;
	    XA2 = 0;

	    XB1 = -0.5f;
	    XB2 = sqrtf(3) / 2.0f;

	    XC1 = -0.5f;
	    XC2 = -sqrtf(3) / 2.0f;
	    }

	__device__
	virtual ~NewtonMath(void)
	    {
	    //nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x1, float x2)
	    {
        int i = 0;
	    bool converged = false;

	    float x1Copy = x1;
	    float x2Copy = x2;

	    do
		{
		computeNextStep(x1Copy, x2Copy, &x1, &x2);
		x1Copy = x1;
		x2Copy = x2;
		converged = hasConverged(x1, x2);
		}
	    while (i++ <= this->n && !converged);

	    if (converged)
		{
		float distSolA = getNorme(x1 - XA1, x2 - XA2);
		float distSolB = getNorme(x1 - XB1, x2 - XB2);
		float distSolC = getNorme(x1 - XC1, x2 - XC2);

		float colorEasing = ((i * this->colorFactor) % 255);

		if (distSolA < distSolB && distSolA < distSolC)
		    {
		    // solA est la plus proche
		    ptrColor->x = 255 - colorEasing;
		    ptrColor->y = 0;
		    ptrColor->z = 0;
		    }
		else if (distSolB < distSolC)
		    {
		    // solB est la plus proche
		    ptrColor->x = 0;
		    ptrColor->y = 255 - colorEasing;
		    ptrColor->z = 0;
		    }
		else
		    {
		    //solC est la plus proche
		    ptrColor->x = 0;
		    ptrColor->y = 0;
		    ptrColor->z = 255 - colorEasing;
		    }
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;

		}
	    ptrColor->w = 255;
	    }

    private:

    // Méthode choisie: (S1) page 6, à savoir: On s'arrete lorsqu'on est suffisament proche d'une solution.
    __device__
    bool hasConverged(float x1, float x2)
        {
        return isSolutionConverged(x1, x2, XA1, XA2) || isSolutionConverged(x1, x2, XB1, XB2) || isSolutionConverged(x1, x2, XC1, XC2);
        }
    __device__
    bool isSolutionConverged(float x1, float x2, float x1Sol, float x2Sol)
        {
        return (getNorme(x1 - x1Sol, x2 - x2Sol) / getNorme(x1Sol, x2Sol)) < this->epsilon;
        }
    __device__
    float getNorme(float x, float y)
        {
        return sqrtf(x * x + y * y);
        }

    /// FONCTIONS NEWTON
    __device__
    float f1(float x1, float x2)
        {
        return x1 * x1 * x1 - 3.0f * x1 * x2 * x2 - 1.0f;
        }

    __device__
    float f2(float x1, float x2)
        {
        return x2 * x2 * x2 - 3.0f * x1 * x1 * x2;
        }

    __device__
    float d1f1(float x1, float x2)
        {
        return 3.0f * (x1 * x1 - x2 * x2);
        }

    __device__
    float d2f1(float x1, float x2)
        {
        return -6.0f * x1 * x2;
        }

    __device__
    float d1f2(float x1, float x2)
        {
        return d2f1(x1, x2);
        }

    __device__
    float d2f2(float x1, float x2)
        {
        return 3.0f * (x2 * x2 - x1 * x1);
        }

    __device__
    void computeNextStep(float x1, float x2, float* outX1, float* outX2)
        {
        float a = d1f1(x1, x2);
        float b = d1f2(x1, x2);
        float c = d2f1(x1, x2);
        float d = d2f2(x1, x2);

        float inversedJacobian = 1.0f / (a * d - b * c);

        float sa = inversedJacobian * d;
        float sb = -inversedJacobian * c;
        float sc = -inversedJacobian * b;
        float sd = inversedJacobian * a;

        *outX1 = x1 - (sa * f1(x1, x2) + sc * f2(x1, x2));
        *outX2 = x2 - (sb * f1(x1, x2) + sd * f2(x1, x2));
        }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

 private:
     // Inputs
     int n;
     float epsilon;

     // Tools
     int colorFactor;

     float XA1;
     float XA2;

     float XB1;
     float XB2;

     float XC1;
     float XC2;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
