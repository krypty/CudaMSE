#include "Saucisson.h"
#include "ReductionTools.h"
#include <iostream>
#include <stdlib.h>
#include "Device.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

extern __global__ void saucissonDevice(float* ptrDevResult,int nbSaucisson,int n);

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/
Saucisson::Saucisson(int nbSaucisson)
{
        this->nbSaucisson = nbSaucisson;

        this->n = 1024;
        this->sizeSM = n*sizeof(float);
        memoryManagement();
        this->dg = dim3(64,1,1);
        this->db = dim3(1,1,1);

}
Saucisson::~Saucisson()
{
        HANDLE_ERROR(cudaFree(ptrDevResult));
        ptrDevResult=NULL;
}

void Saucisson::process()
{
        saucissonDevice<<<dg,db,sizeSM>>>(ptrDevResult,nbSaucisson,n);
        Device::synchronize();
        HANDLE_ERROR(cudaMemcpy(&pi,ptrDevResult,sizePI,cudaMemcpyDeviceToHost));
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

void Saucisson::memoryManagement()
{
        ptrDevResult = NULL;
        sizePI = sizeof(float);
        HANDLE_ERROR(cudaMalloc(&ptrDevResult,sizePI));

        HANDLE_ERROR(cudaMemset(ptrDevResult,0,sizePI));
}
float Saucisson::getPi()
{
        return pi/nbSaucisson;
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
