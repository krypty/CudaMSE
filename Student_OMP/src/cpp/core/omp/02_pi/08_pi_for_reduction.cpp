#include <omp.h>
#include "00_pi_tools.h"
#include "OmpTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforReduction_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforReduction(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforReduction_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforReduction, n, "Pi OMP for reduction-integrer");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern omp usefull : idem desyncronisation-promotionTab ,mais avec syntaxe plus courte!
 * Si on enleve le pragma, le code est le meme que le sequentiel!
 */
double piOMPforReduction(int n)
    {
    double somme = 0;
    double dx = 1.0/(double)n;
    double x;

#pragma omp parallel for private(x) reduction (+:somme)
    for(int i = 0; i < n; i++)
	{
	x = i * dx;
	somme += fpi(x);
	}
    return somme/n;
    }




/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

