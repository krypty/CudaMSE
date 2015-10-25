#include <assert.h>

#include "Newton.h"
#include "Device.h"
#include "MathTools.h"

using cpu::IntervalI;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void newton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Newton::Newton(int w, int h, int nMin, int nMax) :
	variateurN(IntervalI(nMin, nMax), 1)
    {
    // Inputs
    this->w = w;
    this->h = h;

    this->ptrDomaineMathInit = new DomaineMath(-1.3, -1.4, 1.4, 1.3);

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser

    //Outputs
    this->title = "Newton_CUDA (Zoomable)";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    }

Newton::~Newton()
    {
    delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void Newton::process(uchar4* ptrDevPixels, int w, int h, const DomaineMath& domaineMath)
    {
newton<<<dg,db>>>(ptrDevPixels,w,h,domaineMath, n);
}

/**
 * Override
 * Call periodicly by the API
 */
void Newton::animationStep()
{
this->n = variateurN.varierAndGet(); // in [0,2pi]
}

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* Newton::getDomaineMathInit(void)
{
return ptrDomaineMathInit;
}

/**
 * Override
 */
float Newton::getAnimationPara(void)
{
return n;
}

/**
 * Override
 */
int Newton::getW(void)
{
return w;
}

/**
 * Override
 */
int Newton::getH(void)
{
return h;
}

/**
 * Override
 */
string Newton::getTitle(void)
{
return title;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
