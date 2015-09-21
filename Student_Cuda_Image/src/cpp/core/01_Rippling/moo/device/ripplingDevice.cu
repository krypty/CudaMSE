#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools.h"

#include "RipplingMath.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

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

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t)
    {
    RipplingMath ripplingMath = RipplingMath(w, h);

    // TODO pattern entrelacement

    const int NB_THREAD = Indice2D::nbThread();

    int TID = Indice2D::tid();
    int s = TID;
    const int WH = w*h;

    while(s < WH)
	{
	int i = 0;
	int j = 0;
	uchar4 color;

	IndiceTools::toIJ(s, w, &i, &j);

	ripplingMath.colorIJ(i, j, t, &color);
	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

