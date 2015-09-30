#ifndef MANDELBROT_PROVIDER_H_
#define MANDELBROT_PROVIDER_H_

#include "ImageFonctionel.h"
#include "AnimableFonctionel_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotProvider
    {
    public:

	static ImageFonctionel* createGL(void);
	static AnimableFonctionel_I* createMOO(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

