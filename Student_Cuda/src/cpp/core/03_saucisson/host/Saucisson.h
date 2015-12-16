#ifndef SRC_CPP_CORE_03_SAUCISSON_SAUCISSON_H_
#define SRC_CPP_CORE_03_SAUCISSON_SAUCISSON_H_

#include "cudaTools.h"

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

class Saucisson
{
public:
    Saucisson(int nbSaucisson);
    void process();
    float getPi();
    virtual ~Saucisson();
private:
    void memoryManagement();
    
private:
    int nbSaucisson;
    int n;
    dim3 dg;
    dim3 db;
    size_t sizePI;
    size_t sizeSM;
    float pi;
    float* ptrDevResult;
};

#endif

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
