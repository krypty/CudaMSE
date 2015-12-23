#include <iostream>
#include <assert.h>

#include "RayTracing.h"
#include "Device.h"
#include "MathTools.h"
#include "SphereFactory.h"
#include "ConstantMemoryLink.h"

using cpu::IntervalI;

/* on fait des define car conditions ne bougent plus à l'exécution et c'est plus performant que les IF qui doivent être évalués à chaque itération
 * Ces valeurs doivent être cohérente avec celles présentes dans RayTracingDevice.cu
*/
//TODO PROF: jouer avec ces valeurs. Attention: Il doit y avoir une seule et unique valeur a true.
#define USE_GM false
#define USE_CM false
#define USE_SM true

#define LENGTH 1000
__constant__ Sphere TAB_DATA_CM[LENGTH];

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

extern __global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, Sphere* ptrDevSpheres, int n, float t);

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

/*-------------------------*\
|*	Constructeur	    *|
\*-------------------------*/

RayTracing::RayTracing(int w, int h, int nSphere, float dt)
{
        // Inputs
        this->w = w;
        this->h = h;
        this->nSphere = nSphere;
        this->dt = dt;

        // Tools
        this->dg = dim3(16, 2, 1); // disons a optimiser
        this->db = dim3(32, 4, 1); // disons a optimiser

        int margin = 50;
        this->ptrSpheres = SphereFactory::createSpheres(nSphere, w, h, margin);

        this->t = 0.0f;

        //Outputs
        this->title = "RayTracing_CUDA";

        // Check:
        //print(dg, db);
        Device::assertDim(dg, db);

    #if USE_CM
        copySpheresToConstantMemory();
    #endif

        sizeSpheres = sizeof(Sphere) * LENGTH;

    #if USE_GM == true || USE_SM == true
        HANDLE_ERROR(cudaMalloc(&ptrDevSpheres, sizeSpheres));
        HANDLE_ERROR(cudaMemcpy(ptrDevSpheres, ptrSpheres, sizeSpheres, cudaMemcpyHostToDevice));
    #endif
}

RayTracing::~RayTracing()
{
        delete[] this->ptrSpheres;
        HANDLE_ERROR(cudaFree(ptrDevSpheres));
}

/*-------------------------*\
|*	Methode		    *|
\*-------------------------*/

ConstantMemoryLink constantMemoryLink(void)
{
        Sphere* ptrDevTabData;
        size_t sizeAll = LENGTH * sizeof(Sphere);
        HANDLE_ERROR(cudaGetSymbolAddress((void ** )&ptrDevTabData, TAB_DATA_CM));
        ConstantMemoryLink cmLink =
        {
                (void**) ptrDevTabData, LENGTH, sizeAll
        };
        return cmLink;
}

void RayTracing::copySpheresToConstantMemory()
{
        ConstantMemoryLink cmLink = constantMemoryLink();
        this->ptrDevSpheres = (Sphere*) cmLink.ptrDevTab;
        size_t sizeALL = cmLink.sizeAll;

        HANDLE_ERROR(cudaMemcpy(ptrDevSpheres, ptrSpheres, sizeALL, cudaMemcpyHostToDevice));
}

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::process(uchar4* ptrDevPixels, int w, int h)
{
        // rayTracing<<<dg,db>>>(ptrDevPixels, w, h, ptrDevSpheres, this->nSphere, t);

        #if USE_GM == true || USE_CM == true
        rayTracing<<<dg, db>>>(ptrDevPixels, w, h, ptrDevSpheres, this->nSphere, t);
        #endif

        #if USE_SM
        rayTracing<<<dg, db, sizeSpheres>>>(ptrDevPixels, w, h, ptrDevSpheres, this->nSphere, t);
        #endif
}

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
{
        t += dt;
}

/*--------------*\
|*	get	 *|
\*--------------*/

/**
 * Override
 */
float RayTracing::getAnimationPara(void)
{
        return t;
}

/**
 * Override
 */
int RayTracing::getW(void)
{
        return w;
}

/**
 * Override
 */
int RayTracing::getH(void)
{
        return h;
}

/**
 * Override
 */
string RayTracing::getTitle(void)
{
        return title;
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
