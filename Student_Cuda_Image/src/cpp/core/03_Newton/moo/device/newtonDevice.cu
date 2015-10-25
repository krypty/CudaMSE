#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "NewtonMath.h"
#include "JuliaMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void newton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n);

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

__global__ void newton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n)
    {
    float epsilon = 0.1f;
    NewtonMath newtonMath = NewtonMath(epsilon, n);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH = w * h;

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

	newtonMath.colorXY(&color, x, y); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}

    // must be present !
    //delete newtonMath;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
