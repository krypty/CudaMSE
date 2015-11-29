#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"
#include "Sphere.h"

// on fait des define car conditions ne bougent plus à l'exécution et c'est plus performant que les IF qui doivent être évalués à chaque itération
// Il ne peut y avoir qu'une seule valeur a true possible
#define USE_GM false
#define USE_CM false
#define USE_SM true

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, Sphere* ptrDevSpheres, int n, float t);

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

static __device__ void copyGMtoSM(Sphere* tabSpheresSM, Sphere* ptrDevSpheresGM, int n);

static __device__ void work(int w, int h, int n, float t, Sphere* ptrSpheres, uchar4* ptrDevPixels);

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

__global__
void rayTracing(uchar4* ptrDevPixels, int w, int h, Sphere* ptrDevSpheresGM, int n, float t)
{
 #if USE_SM
        extern __shared__ Sphere tabSpheresSM[];
        copyGMtoSM(tabSpheresSM, ptrDevSpheresGM, n);
        __syncthreads();
        work(w, h, n, t, tabSpheresSM, ptrDevPixels);
 #else
        work(w, h, n, t, ptrDevSpheresGM, ptrDevPixels);
 #endif

}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

__device__
void work(int w, int h, int n, float t, Sphere* ptrDevSpheres, uchar4* ptrDevPixels)
{
        RayTracingMath rayTracingMath = RayTracingMath(ptrDevSpheres, n, t);
        const int WH = w * h;
        const int NB_THREAD = Indice2D::nbThread();
        const int TID = Indice2D::tid();
        int s = TID;
        int i;
        int j;
        uchar4 color;
        while (s < WH)
        {
                IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[
                // rayTracingMath.color(i, j, t, ptrDevPixels[s]);
                rayTracingMath.colorIJ(&color,i, j);  // update color
                ptrDevPixels[s] = color;
                s += NB_THREAD;
        }
}

__device__
void copyGMtoSM(Sphere* tabSpheresSM, Sphere* ptrDevSpheresGM, int n)
{
        const int TID_LOCAL = Indice2D::tidLocal();
        const int NB_THREAD_BLOCK = Indice2D::nbThreadBlock();

        int s = TID_LOCAL;

        while (s < n)
        {
                tabSpheresSM[s] = ptrDevSpheresGM[s];
                s += NB_THREAD_BLOCK;
        }
}

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
