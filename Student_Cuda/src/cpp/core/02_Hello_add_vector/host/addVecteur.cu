#include "cudaTools.h"
#include "Device.h"

#include <iostream>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addVecteurGPU(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__  void addVecteur(float* ptrV1, float* ptrV2, float* ptrW,int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


__host__ void addVecteur(float* ptrV1, float* ptrV2, float* ptrW, int n)
    {
    float* ptrDevV1 = NULL;
    float* ptrDevV2 = NULL;
    float* ptrDevW = NULL;

    size_t size = n * sizeof(float); // octet

    HANDLE_ERROR(cudaMalloc(&ptrDevV1, size));
    HANDLE_ERROR(cudaMalloc(&ptrDevV2, size));
    HANDLE_ERROR(cudaMalloc(&ptrDevW, size));

    HANDLE_ERROR(cudaMemset(ptrDevW, 0, size));

    HANDLE_ERROR(cudaMemcpy(ptrDevV1, ptrV1, size, cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(ptrDevV2, ptrV2, size, cudaMemcpyHostToDevice));

    dim3 dg(16, 2, 1); // disons
    dim3 db(32, 4, 1); // disons

    // Debug
    //Device::print(dg, db);
    Device::checkDimError(dg, db);

    addVecteurGPU<<<dg,db>>>(ptrDevV1, ptrDevV2, ptrDevW, n); // assynchrone
    Device::checkLastCudaError("addVecteur"); // facultatif
    Device::synchronize(); // Temp, only for printf in  GPU

    HANDLE_ERROR(cudaMemcpy(ptrW, ptrDevW, size, cudaMemcpyDeviceToHost)); // barri�re synchronisation implicite

    HANDLE_ERROR(cudaFree(ptrDevV1));
    HANDLE_ERROR(cudaFree(ptrDevV2));
    HANDLE_ERROR(cudaFree(ptrDevW));
    // TODO ptrV2 et ptrW
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

