#include <iostream>

#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools.h"

#include "RipplingMath.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
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

        // Indice2D
        const int NB_THREAD = Indice2D::nbThread();
        int TID = Indice2D::tid();

//// Indice1D
//    const int NB_THREAD = Indice1D::nbThread();
//    int TID = Indice1D::tid();

//// 1-1
//    const int NB_THREAD = (64*16) * (64*16);

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


//	uchar4 color;
//	int i = threadIdx.y  + blockIdx.y * blockDim.y;
//	int j = threadIdx.x  + blockIdx.x * blockDim.x;
//
//	int s = i * w + j;
//	ripplingMath.colorIJ(i, j, t, &color);
//	ptrDevPixels[s] = color;
}


/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
