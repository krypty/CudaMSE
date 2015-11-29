#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools.h"
#include "ColorTools.h"
#include "CalibreurF.h"
#include "IntervalF_GPU.h"

using std::cout;
using std::endl;
using gpu::IntervalF;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void toScreenImageHSB(uchar4* ptrDevPixels, float* ptrImageInput, int w, int h);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void toScreenImageHSB(uchar4* ptrDevPixels, float* ptrImageInput, int w, int h)
    {
    const int WH = w * h;

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    int s = TID;

    float heatMax = 1.0;
    float heatMin = -0.2;
    float hueMax = 0;
    float hueMin = 0.66;

    CalibreurF calibreur(IntervalF(heatMin,heatMax),IntervalF(hueMin,hueMax));

    while (s < WH)
	{
	float hue = ptrImageInput[s];
	calibreur.calibrer(hue);
	uchar4 p;
	ColorTools::HSB_TO_RVB(hue,1,1,&p.x,&p.y,&p.z);
	ptrDevPixels[s] = p;
	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

