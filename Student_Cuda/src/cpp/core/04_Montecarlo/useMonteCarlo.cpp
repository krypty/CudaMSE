#include <iostream>
#include <limits.h>
#include <math.h>
#include "MathTools.h"
#include "MonteCarlo.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

bool useMonteCarlo(void);

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/



bool useMonteCarlo(void)
{
        cout << endl << "[MonteCarlo]" << endl;

        bool isOK = true;

        //int n = INT_MAX;
        int n = 16777216;
        MonteCarlo mc(n);
        mc.process();

        cout << "MonteCarlo pi: " << mc.getPi() << endl;

        isOK &= MathTools::isEquals(mc.getPi(), M_PI, 1e-3);

        return isOK;
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/
