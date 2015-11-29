#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools.h"

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

__global__ void diffusion(float* ptrImageInput, float* ptrImageOutput, int w, int h);

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

__device__ float D_operator(float* ptrImage, int s, int w)
    {
    float k = 0.2;
    return ptrImage[s] + k * (ptrImage[s + w] + ptrImage[s - w] + ptrImage[s + 1] + ptrImage[s - 1] - 4 * ptrImage[s]);
    }

__global__ void diffusion(float* ptrImageInput, float* ptrImageOutput, int w, int h)
    {
    const int WH = w * h;

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    int s = TID;

    while (s < WH)
	{
	// on n'applique pas la diffusion sur les bords
	if(s > w && s < WH-w && (w-1)%s != 0 && w%s != 0 )
	    ptrImageOutput[s] = D_operator(ptrImageInput, s, w);

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

