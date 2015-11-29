#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"
#include "Option.h"
#include "Viewer.h"
#include "ViewerZoomable.h"

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "NewtonProvider.h"
#include "RayTracingProvider.h"
#include "HeatTransfertProvider.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

int mainGL(Option& option);

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

int mainGL(Option& option)
{
        cout << "\n[OpenGL] mode" << endl;

        GLUTImageViewers::init(option.getArgc(), option.getArgv());

        // Viewer : (int,int,boolean) : (px,py,isAnimation=true)
        // Viewer<RipplingProvider> rippling(10, 10);
        // ViewerZoomable<MandelbrotProvider> mandelbrot(10, 10);
        // ViewerZoomable<NewtonProvider> newton(10, 10);
        // Viewer<RayTracingProvider> rayTracing(10, 10);
        Viewer<HeatTransfertProvider> heatTransfert(10, 10);
        // add here other viewer

        GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

        return EXIT_SUCCESS;
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
