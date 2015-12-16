#ifndef SRC_TOOLS_REDUCTIONTOOLS_H_
#define SRC_TOOLS_REDUCTIONTOOLS_H_

#include "Indice1D.h"
#include "cudaTools.h"

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/
template<class Tinput,class Toutput>
class ReductionTools
{
public:
__device__
ReductionTools(int n)
{
        this->n=n;
}
__device__
virtual ~ReductionTools()
{

}
__device__
void reduction(Tinput* tabSM,Toutput* ptrDevResult)
{
        reductionIntraBlock(tabSM);
        reductionInterBlock(tabSM,ptrDevResult);
}


private:
__device__
void reductionIntraBlock(Tinput* tabSM)
{
        int moitier = n/2;
        while(moitier >=1)
        {
                ecrasement(tabSM,moitier);
                moitier=moitier/2;
                __syncthreads();
        }
}
__device__
void reductionInterBlock(Tinput* tabSM, Toutput* ptrDevResult)
{
        if(threadIdx.x==0)
        {
                atomicAdd(ptrDevResult,tabSM[0]);
        }
}
__device__
void ecrasement(Tinput* tabSM, int moitier)
{
        //devrait utiliser Indice1D
        const int THREAD_LOCAL_ID =Indice1D::tidLocal();
        const int NB_THREAD_LOCAL= Indice1D::nbThread();
        int s=THREAD_LOCAL_ID;
        while(s<moitier)
        {
                tabSM[s]+=tabSM[s+moitier];
                s+=NB_THREAD_LOCAL;
        }
}

//tools
int n;
};

#endif

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
