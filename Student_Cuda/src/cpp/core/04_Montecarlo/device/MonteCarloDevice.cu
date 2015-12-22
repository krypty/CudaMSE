#include "ReductionTools.h"
#include <stdio.h>
#include <limits.h>
#include "curandTools.h"
#include "Device.h"

#ifndef SRC_CPP_CORE_03_MONTECARLO_DEVICE_MONTECARLO_CU_
#define SRC_CPP_CORE_03_MONTECARLO_DEVICE_MONTECARLO_CU_


/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

__global__ void monteCarloDevice(int* ptrDevResult, curandState* ptrDevTabGeneratorThread, int nbDarts, int n);
__device__ void initSharedMemory(int* tabSM, int n);
__device__ void peuplerSharedMemory(int* tabSM, curandState* ptrDevTabGeneratorThread, int nbDarts);

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

__global__ void monteCarloDevice(int* ptrDevResult, curandState* ptrDevTabGeneratorThread,  int nbDarts, int n)
{
        extern __shared__ int tabSM[];

        ReductionTools<int, int> reductionTools = ReductionTools<int, int>(n);
        initSharedMemory(tabSM, n);
        __syncthreads();
        peuplerSharedMemory(tabSM, ptrDevTabGeneratorThread, nbDarts);
        __syncthreads();
        reductionTools.reduction(tabSM, ptrDevResult);
        __syncthreads();
        const int TID = Indice1D::tid();
}

__device__ void initSharedMemory(int* tabSM, int n)
{
        const int TID_LOCAL = Indice1D::tidLocal();
        const int NB_THREAD_LOCAL= Indice1D::nbThreadBlock();
        int s = TID_LOCAL;
        while(s < n)
        {
                tabSM[s] = 0;
                s += NB_THREAD_LOCAL;
        }
}
__device__ void peuplerSharedMemory(int* tabSM, curandState* ptrDevTabGeneratorThread, int nbDarts)
{
        const int NB_THREAD = Indice1D::nbThread();
        const int TID = Indice1D::tid();
        const int TID_LOCAL = Indice1D::tidLocal();
        float s = TID;

        int somme = 0;
        curandState localState = ptrDevTabGeneratorThread[TID];
        int tid = Indice1D::tid();

        while (s < nbDarts)
        {
                float x = curand_uniform(&localState);
                float y = curand_uniform(&localState);
                float z = 1.0f / (1.0f + x * x);
                if (y < z)
                {
                        somme += 1;
                }
                s += NB_THREAD;
        }
        tabSM[TID_LOCAL] = somme;
}

#endif

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
