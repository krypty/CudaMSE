#include <iostream>
#include <assert.h>

#include "Rippling.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

extern __global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

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

Rippling::Rippling(int w, int h, float dt, dim3 dg, dim3 db)
{
        assert(w == h);

        // Inputs
        this->w = w;
        this->h = h;
        this->dt = dt;

        // Tools

        // Indice2D
        // this->dg = dim3(64*4, 4, 1);
        // this->db = dim3(32*4, 8, 1);
        // this->dg = dim3(96, 4, 1);
        // this->db = dim3(128, 4, 1);
        this->dg = dg;
        this->db = db;


        // Indice1D
//    this->dg = dim3(512, 1, 1);
//    this->db = dim3(1024, 1, 1);

//    // pattern 1-1
//    this->dg = dim3(64, 64, 1);
//    this->db = dim3(16, 16, 1);

        this->t = 0;

        // Outputs
        this->title = "Rippling_Cuda";

        //print(dg, db);
        Device::assertDim(dg, db);
}

Rippling::Rippling(int w, int h, float dt):Rippling(w, h, dt, dim3(96, 4, 1), dim3(128, 4, 1)) {}

Rippling::~Rippling()
{
        // rien
}

/*-------------------------*\
|*	Methode		    *|
\*-------------------------*/


/**
 * Override
 */
void Rippling::process(uchar4* ptrDevPixels, int w, int h)
{
        rippling<<<dg, db>>>(ptrDevPixels, w, h, t);
}


/**
 * Override
 */
void Rippling::animationStep()
{
        this->t += this->dt;
}

/*--------------*\
|*	get	 *|
\*--------------*/

/**
 * Override
 */
float Rippling::getAnimationPara(void)
{
        return t;
}

/**
 * Override
 */
int Rippling::getW(void)
{
        return w;
}

/**
 * Override
 */
int Rippling::getH(void)
{
        return h;
}

/**
 * Override
 */
string Rippling::getTitle(void)
{
        return title;
}


/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
