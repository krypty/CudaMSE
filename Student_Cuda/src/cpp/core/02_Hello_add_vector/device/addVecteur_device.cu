#include "Indice2D.h"
#include "cudaTools.h"

#include <stdio.h>



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void addVecteurGPU(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


static __device__ void secondaire(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void addVecteurGPU(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n)
    {
    secondaire(ptrDevV1, ptrDevV2, ptrDevW, n); // pas necessaire, just for fun
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


__device__ void secondaire(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n)
    {
    const int NB_THREAD=Indice2D::nbThread();
    const int TID=Indice2D::tid();

    // Debug
    if (TID==0)
	{
	printf("Coucou from device tid&d",TID); //required   Device::synchronize(); after the call of kernel
	}

   //TODO pattern entrelacement
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

