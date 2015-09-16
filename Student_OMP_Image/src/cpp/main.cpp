#include <iostream>
#include <stdlib.h>

#include "Settings.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern int mainGL(Settings& settings);
extern int mainMOO(Settings& settings);

/*--------------------------------------*\
 |*		Public			*|
  \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int start(Settings& settings);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv)
    {
    cout<<"main"<<endl;

    bool IS_GL = true;
    Settings settings(IS_GL,argc,argv);

    return start(settings);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int start(Settings& settings)
    {
    if (settings.isGL())
	{
	return mainGL(settings); // Bloquant, Tant qu'une fenetre est ouverte
	}
    else
	{
	return mainMOO(settings); // FreeGL
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

