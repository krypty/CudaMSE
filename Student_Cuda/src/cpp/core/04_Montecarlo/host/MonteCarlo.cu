#include "MonteCarlo.h"
#include "ReductionTools.h"
#include <iostream>
#include <stdlib.h>
#include "Device.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

extern __global__ void monteCarloDevice(float* ptrDevResult,curandState* ptrDevTabGeneratorThread,int nbDarts,int n);
extern __global__ void setup_kernel_rand(curandState* ptrDevTabGeneratorThread, int deviceId);

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

MonteCarlo::MonteCarlo(int nbDarts)
{
        this->nbDarts = nbDarts;
        this->n = 1;
        this->sizeSM = n*sizeof(float);
        memoryManagement();
        this->dg = dim3(64,1,1);
        this->db = dim3(1,1,1);

        ptrDevTabGeneratorThread = new curandState*[Device::getDeviceCount()];
        ptrDevResult = new float*[Device::getDeviceCount()];

        size_t generatorSize = sizeof(curandState) * n;
        for(int i = 0; i < Device::getDeviceCount(); i++)
        {
                HANDLE_ERROR(cudaSetDevice(i));
                HANDLE_ERROR(cudaMalloc(&ptrDevResult[i], sizePI));
                HANDLE_ERROR(cudaMemset(ptrDevResult[i], 0, sizePI));

                HANDLE_ERROR(cudaMalloc(&ptrDevTabGeneratorThread[i], generatorSize));
                setup_kernel_rand<<<dg, db>>>(ptrDevTabGeneratorThread[i], Device::getDeviceId());
        }
}
MonteCarlo::~MonteCarlo()
{
        HANDLE_ERROR(cudaFree(*ptrDevResult));
        HANDLE_ERROR(cudaFree(*ptrDevTabGeneratorThread));
        ptrDevResult=NULL;
        ptrDevTabGeneratorThread=NULL;
}

void MonteCarlo::process()
{
        int nbDevices = Device::getDeviceCount();
#pragma omp parallel for
        for(int i = 0; i < nbDevices; i++)
        {
                float tmp;
                HANDLE_ERROR(cudaSetDevice(i));
                monteCarloDevice<<<dg, db, sizeSM>>>(ptrDevResult[i], ptrDevTabGeneratorThread[i], nbDarts / nbDevices, n);
                HANDLE_ERROR(cudaMemcpy(&tmp, ptrDevResult[i], sizePI, cudaMemcpyDeviceToHost));
    #pragma omp atomic
                pi += tmp;
        }
        pi /= (float)nbDevices;
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

void MonteCarlo::memoryManagement()
{
        ptrDevResult = NULL;
        sizePI = sizeof(float);
        HANDLE_ERROR(cudaMalloc(&ptrDevResult, sizePI));

        HANDLE_ERROR(cudaMemset(ptrDevResult, 0, sizePI));
}
float MonteCarlo::getPi()
{
        return pi;
}

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
