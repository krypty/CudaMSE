#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "MandelbrotMath.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels,int w, int h,DomaineMath domaineMath, int n,float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n)
    {
    MandelbrotMath mandelbrotMath(n);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    double x;
    double y;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	// (i,j) domaine ecran
	// (x,y) domaine math
	domaineMath.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)


	mandelbrotMath.colorXY(&color, x, y, domaineMath, n); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

