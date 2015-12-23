#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "MandelbrotMath.h"
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

__global__ void mandelbrot(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n);

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
    // hiérarchie de classe et polymorphisme (donc en utilisant des pointeurs) fonctionnels

    float c1 = -0.12;
    float c2 = 0.85;

    //TODO PROF: commenter ou décommenter pour passer de Mandelbrot à Julia ou vice versa
    //TODO PROF: voir version OpenMP pour tous les autres représentations de fractales
//    MandelbrotMathBase* mandelbrotMath = new JuliaMath(n, c1, c2);
    MandelbrotMathBase* mandelbrotMath = new MandelbrotMath(n);

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

	mandelbrotMath->colorXY(&color, x, y); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}

    // must be present !
    delete mandelbrotMath;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
