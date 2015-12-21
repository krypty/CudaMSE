#ifndef RIPPLING_PROVIDER_H_
#define RIPPLING_PROVIDER_H_

#include "Rippling.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

class RipplingProvider
{
public:
        static Rippling* createMOO(dim3 dg, dim3 db);
        static Rippling* createMOO();
        static Image* createGL(void);

};

#endif

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
