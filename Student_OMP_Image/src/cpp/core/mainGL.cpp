#include <iostream>

#include "GLUTImageViewers.h"
#include "Settings.h"

#include "ViewerZoomable.h"
#include "Viewer.h"

#include "RipplingProvider.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(Settings& settings);

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

int mainGL(Settings& settings)
    {
    cout << "\n[OpenGL] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); // call once

    // Viewer : (int,int,boolean) : (px,py,isAnimation=true)
    Viewer<RipplingProvider> rippling( 0, 0);
    // add other viewer here!

    GLUTImageViewers::runALL();  // Bloquant, Tant qu'une fenetre est ouverte

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

