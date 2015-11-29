#ifndef HEAT_TRANSFERT_PROVIDER_H_
#define HEAT_TRANSFERT_PROVIDER_H_

#include "HeatTransfert.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class HeatTransfertProvider
    {
    public:

	static HeatTransfert* createMOO(void);
	static Image* createGL(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

