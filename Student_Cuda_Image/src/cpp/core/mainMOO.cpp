#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Option.h"

#include "Animateur.h"
#include "AnimateurFonctionel.h"

#include "RipplingProvider.h"

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

int mainFreeGL(Option& option);

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

static int animer(Animable_I* ptrAnimable, int nbIteration);
static int animer(AnimableFonctionel_I* ptrAnimable, int nbIteration);

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

int mainFreeGL(Option& option)
{
        cout << "\n[FreeGL] mode" << endl;

        const int NB_ITERATION = 1000;

        // Rippling
        {
		int maxFPS = -1;
		const int DGDB_LENGTH = 5;
		dim3 arrDg[] = {
			dim3(64, 1, 1),
			dim3(128, 1, 1),
			dim3(64, 4, 1),
			dim3(128, 4, 1),
			dim3(512, 1, 1)
		};

		dim3 arrDb[] = {
			dim3(64, 1, 1),
			dim3(128, 1, 1),
			dim3(64, 4, 1),
			dim3(128, 4, 1),
			dim3(512, 1, 1)
		};

		for(int i = 0; i < DGDB_LENGTH; i++)
		    {
			for(int j = 0; j < DGDB_LENGTH; j++)
			    {
				cout << "------" << endl;
				cout << "dg index: " << i << ", db index: " << j << endl;
				Animable_I* ptrRippling = RipplingProvider::createMOO(arrDg[i], arrDb[j]);
				int fps = animer(ptrRippling, NB_ITERATION);
				maxFPS = maxFPS < fps ? fps : maxFPS;
				cout << "------" << endl;
			    }
		    }

		cout << "MAX FPS: " << maxFPS << endl;
        }

        cout << "\n[FreeGL] end" << endl;

        return EXIT_SUCCESS;
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

int animer(Animable_I* ptrAnimable, int nbIteration)
{
        Animateur animateur(ptrAnimable, nbIteration);
        animateur.run();

        delete ptrAnimable;

        return animateur.getFps();
}

int animer(AnimableFonctionel_I* ptrAnimable, int nbIteration)
{
        AnimateurFonctionel animateur(ptrAnimable, nbIteration);
        animateur.run();

        delete ptrAnimable;

        return animateur.getFps();
}

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
