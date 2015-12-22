#ifndef SRC_CPP_CORE_03_MONTECARLO_MONTECARLO_H_
#define SRC_CPP_CORE_03_MONTECARLO_MONTECARLO_H_

#include "cudaTools.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

class MonteCarlo
{
public:
    MonteCarlo(int nbDarts);
    void process();
    float getPi();
    virtual ~MonteCarlo();
private:
    void memoryManagement();

private:
    int nbDarts;
    int n;
    dim3 dg;
    dim3 db;
    size_t sizePI;
    size_t sizeSM;
    int resultatInter;
    int piInter;
    float pi;
    int** ptrDevResult;
    curandState** ptrDevTabGeneratorThread;
};

#endif

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
