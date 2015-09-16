// Attention : Extension .cu

#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"

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

__host__ bool isAddScalarGPU_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ static int addScalarGPU(int a, int b);
__global__ static void addScalar(int a, int b, int* ptrC);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isAddScalarGPU_Ok(void)
    {
    cout << endl << "[Hello Cuda 2]" << endl;

    int a = 2;
    int b = 7;

    int sumGPU = addScalarGPU(a, b);
    int sumTheorique = a + b;

    cout << "\n[CPU] " << a << " + " << b << " = " << sumGPU << endl;

    return sumGPU == sumTheorique;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ int addScalarGPU(int a, int b)
    {
    int c;
    int* ptrC = &c;	// on host (CPU)
    int* ptrDev_c; 	// on device (GPU)

    // Specifier nb thread : ici 1 thread au total !
    dim3 dg = dim3(1, 1, 1);
    dim3 db = dim3(1, 1, 1);

    // Debug
    //Device::print(dg, db);
    Device::checkDimError(dg, db);

    size_t size = sizeof(int); // octet
    HANDLE_ERROR(cudaMalloc((void** ) &ptrDev_c, size)); // Device memory allocation (*)

    addScalar<<<dg,db>>>(a,b,ptrDev_c); // asynchrone !!
    Device::checkLastCudaError("addScalar"); // facultatif

    //v1
    Device::synchronize(); // Pour printf sur  GPU

    //v2
    // cudaDeviceSynchronize(); // Pour printf sur  GPU

    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(ptrC, ptrDev_c, size, cudaMemcpyDeviceToHost));   // Device -> Host
    HANDLE_ERROR(cudaFree(ptrDev_c)); // device dispose memory in (*)

    return c;
    }

/**
 * Hyp : 1 seul thread, ie dg(1,1,1) et db (1,1,1)
 */
__global__ void addScalar(int a, int b, int* ptrC)
    {
    *ptrC = a + b; // Hyp: 1 seul thread

    // debug
    printf("[GPU] %d + %d = %d", a, b, *ptrC);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

