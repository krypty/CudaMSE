// Attention : Extension .cu

#include <iostream>
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

__host__  bool helloCuda(void); //__host__ facultatif

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ static void kernelHello(void);
__device__ static void doSomethingHello(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * resumer commande cuda:
 * http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/docs/online/index.html
 */
__host__ bool helloCuda(void) //__host__ facultatif
    {
    cout << endl << "[Hello Cuda 1]" << endl;

    // Specifier nb thread : ici 1 thread au total !
    dim3 dg = dim3(1, 1, 1);
    dim3 db = dim3(1, 1, 1);

    // Debug
    //Device::print(dg, db);
     Device::checkDimError(dg,db);

    kernelHello<<<dg,db>>>();  // asynchrone !!
    Device::checkLastCudaError("kernelHello"); // facultatif

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/**
 * output : void
 */
__global__ void kernelHello(void)
    {
    doSomethingHello();
    }

/**
 * Can be call only by device
 * inliner by nvcc (nvidia compiler)
 */
__device__ void doSomethingHello(void)
    {
    // rien
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

