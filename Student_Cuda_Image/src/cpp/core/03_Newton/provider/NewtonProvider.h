#ifndef NEWTON_PROVIDER_H_
#define NEWTON_PROVIDER_H_

#include "Newton.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class NewtonProvider
    {
    public:

	static Newton* create(void);
	static ImageFonctionel* createGL(void);
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
