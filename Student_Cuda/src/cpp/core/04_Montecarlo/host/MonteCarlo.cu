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

extern __global__ void monteCarloDevice(int* ptrDevResult,curandState* ptrDevTabGeneratorThread,int nbDarts,int n);
extern __global__ void setup_kernel_rand(curandState* ptrDevTabGeneratorThread, int deviceId);

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

MonteCarlo::MonteCarlo(int nbDarts)
{
    this->nbDarts = nbDarts;
    this->n = 1024;
    this->sizeSM = n * sizeof(int);
    this->sizePI = sizeof(int);
    this->dg = dim3(256,1,1);
    this->db = dim3(256,1,1);
    this->piInter = 0;
    this->pi = 0;
    this->nbDevices = 6;
    int nbThread = Device::nbThread(dg, db);

    ptrDevTabGeneratorThread = new curandState*[this->nbDevices];
    ptrDevResult = new int*[this->nbDevices];

    size_t generatorSize = sizeof(curandState) * nbThread;
    for(int i = 0; i < this->nbDevices; i++)
    {
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaMalloc(&ptrDevResult[i], sizePI));

	HANDLE_ERROR(cudaMalloc(&ptrDevTabGeneratorThread[i], generatorSize));
	setup_kernel_rand<<<dg, db>>>(ptrDevTabGeneratorThread[i], i);
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
#pragma omp parallel for
    for(int i = 0; i < nbDevices; i++)
    {
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaMemset(ptrDevResult[i], 0, sizePI));

	int tmp = 0;
	monteCarloDevice<<<dg, db, sizeSM>>>(ptrDevResult[i], ptrDevTabGeneratorThread[i], nbDarts / nbDevices, n);
	HANDLE_ERROR(cudaMemcpy(&tmp, ptrDevResult[i], sizePI, cudaMemcpyDeviceToHost));

//	cout << "result inter: " << tmp << endl;

#pragma omp atomic
	piInter += tmp;
    }
    pi = 4.0f * piInter /((float)nbDarts);
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

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
