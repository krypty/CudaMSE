#include <iostream>
#include <assert.h>

#include "HeatTransfert.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void ecrasement(float* ptrImageInOutput, float* ptrImageHeater, int w, int h);
extern __global__ void diffusion(float* ptrImageInput, float* ptrImageOutput, int w, int h);
extern __global__ void toScreenImageHSB(uchar4* ptrDevPixels, float* ptrImageInput, int w, int h);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

HeatTransfert::HeatTransfert(int w, int h, float dt)
    {

    // Inputs
    this->w = w;
    this->h = h;
    this->dt = dt;

    // Tools
    this->dg = dim3(32, 4, 1);
    this->db = dim3(64, 8, 1);
    this->t = 0;
    this->isImageAInput = true;
    this->NB_ITERATION_AVEUGLE = 50;
    this->nbIterations = 0;

    // Outputs
    this->title = "HeatTransfert_Cuda";

    initImages();
    memoryManagment();

    //print(dg, db);
    Device::assertDim(dg, db);
    }

HeatTransfert::~HeatTransfert()
    {
    delete[] imageHeater;
    delete[] imageInit;

    HANDLE_ERROR(cudaFree(ptrDevImageHeater));
    HANDLE_ERROR(cudaFree(ptrDevImageInit));

    this->ptrDevImageInit = NULL;
    this->ptrDevImageHeater = NULL;
    this->ptrDevImageA = NULL;
    this->ptrDevImageB = NULL;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

void HeatTransfert::initImages()
    {
    imageHeater = new float[IMAGEWIDTH * IMAGEHEIGHT];

    for (int i = 0; i < IMAGEWIDTH; i++)
	{
	for (int j = 0; j < IMAGEHEIGHT; j++)
	    {

	    //Carré chaud au milieu
	    if (i > 350 && i < 450 && j > 350 && j < 450)
		imageHeater[i * IMAGEWIDTH + j] = 1.0;

	    //Petit carré froid en diagonale
	    if (i >= 280 && i <= 520 && (i <= 310 || i >= 490) && j >= 280 && j <= 520 && (j <= 310 || j >= 490))
		imageHeater[i * IMAGEWIDTH + j] = -0.2;

	    //Petit carré chaud
	    if (i >= 179 && i <= 621 && (i <= 195 || i >= 605 || (i >= 392 && i <= 408)) && j >= 179 && j <= 621 && (j <= 195 || j >= 605 || (j >= 392 && j <= 408)))
		imageHeater[i * IMAGEWIDTH + j] = 1.0;

	    }

	}

    imageInit = new float[IMAGEWIDTH * IMAGEHEIGHT];

    }

void HeatTransfert::memoryManagment()
    {
    //Global Memory

    this->ptrDevImageInit = NULL;
    this->ptrDevImageHeater = NULL;
    this->ptrDevImageA = NULL;
    this->ptrDevImageB = NULL;
    int size = IMAGEWIDTH * IMAGEHEIGHT * sizeof(float);

    HANDLE_ERROR(cudaMalloc(&ptrDevImageInit, size));
    HANDLE_ERROR(cudaMalloc(&ptrDevImageHeater, size));
    HANDLE_ERROR(cudaMalloc(&ptrDevImageA, size));
    HANDLE_ERROR(cudaMalloc(&ptrDevImageB, size));

    HANDLE_ERROR(cudaMemset(ptrDevImageA, 0, size));
    HANDLE_ERROR(cudaMemset(ptrDevImageB, 0, size));

    HANDLE_ERROR(cudaMemcpy(ptrDevImageInit, this->imageInit, size, cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(ptrDevImageHeater, this->imageHeater, size, cudaMemcpyHostToDevice));

    }

/**
 * Override
 */
void HeatTransfert::process(uchar4* ptrDevPixels, int w, int h)
    {

    float* ptrImageInput = NULL;
    float* ptrImageOutput = NULL;
    if (this->isImageAInput)
	{
	ptrImageInput = ptrDevImageA;
	ptrImageOutput = ptrDevImageB;
	}
    else
	{
	ptrImageInput = ptrDevImageB;
	ptrImageOutput = ptrDevImageA;
	}

    diffusion<<<dg,db>>>(ptrImageInput, ptrImageOutput, IMAGEWIDTH, IMAGEHEIGHT);

    ecrasement<<<dg,db>>>(ptrImageOutput, ptrDevImageHeater, IMAGEWIDTH, IMAGEHEIGHT);

    if(nbIterations % NB_ITERATION_AVEUGLE == 0)
	{
	    toScreenImageHSB<<<dg,db>>>(ptrDevPixels, ptrImageOutput, IMAGEWIDTH, IMAGEHEIGHT);
	}

    isImageAInput = !isImageAInput;
    nbIterations++;

    }

/**
 * Override
 */
void HeatTransfert::animationStep()
    {
    t += dt;
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float HeatTransfert::getAnimationPara(void)
    {
    return t;
    }

/**
 * Override
 */
int HeatTransfert::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int HeatTransfert::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string HeatTransfert::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
