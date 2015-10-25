#include <assert.h>

#include "Mandelbrot.h"
#include "Device.h"
#include "MathTools.h"

using cpu::IntervalI;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void mandelbrot(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n);

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

Mandelbrot::Mandelbrot(int w, int h, int nMin, int nMax) :
	variateurN(IntervalI(nMin, nMax), 1)
    {
    // Inputs
    this->w = w;
    this->h = h;

    //this->ptrDomaineMathInit=DomaineMath(-2.1, -1.3, 0.8, 1.3); // Mandelbrot
    this->ptrDomaineMathInit = new DomaineMath(-1.3, -1.4, 1.4, 1.3); // Julia

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser

    //Outputs
    this->title = "Mandelbrot_CUDA (Zoomable)";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    }

Mandelbrot::~Mandelbrot()
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
void Mandelbrot::process(uchar4* ptrDevPixels, int w, int h, const DomaineMath& domaineMath)
    {
mandelbrot<<<dg,db>>>(ptrDevPixels,w,h,domaineMath, n);
}

/**
 * Override
 * Call periodicly by the API
 */
void Mandelbrot::animationStep()
{
this->n = variateurN.varierAndGet(); // in [0,2pi]
}

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* Mandelbrot::getDomaineMathInit(void)
{
return ptrDomaineMathInit;
}

/**
 * Override
 */
float Mandelbrot::getAnimationPara(void)
{
return n;
}

/**
 * Override
 */
int Mandelbrot::getW(void)
{
return w;
}

/**
 * Override
 */
int Mandelbrot::getH(void)
{
return h;
}

/**
 * Override
 */
string Mandelbrot::getTitle(void)
{
return title;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

