#include <iostream>
#include <stdlib.h>

#include "Settings.h"

#include "Animateur.h"
#include "AnimateurFonctionel.h"

#include "RipplingProvider.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainMOO(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void animer(Animable_I* ptrAnimable, int nbIteration);
static void animer(AnimableFonctionel_I* ptrAnimable, int nbIteration);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainMOO(Settings& settings)
    {
    cout << "\n[FreeGL] mode" << endl;

    const int NB_ITERATION = 1000;

    // Rippling
	{
	Animable_I* ptrRippling = RipplingProvider::createMOO();
	animer(ptrRippling, NB_ITERATION);
	}

    cout << "\n[FreeGL] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void animer(Animable_I* ptrAnimable, int nbIteration)
    {
    Animateur animateur(ptrAnimable, nbIteration);
    animateur.run();

    delete ptrAnimable;
    }

void animer(AnimableFonctionel_I* ptrAnimable, int nbIteration)
    {
    AnimateurFonctionel animateur(ptrAnimable, nbIteration);
    animateur.run();

    delete ptrAnimable;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

