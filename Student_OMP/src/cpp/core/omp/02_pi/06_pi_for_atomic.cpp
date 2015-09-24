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

bool isPiOMPforAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforAtomic, n, "Pi OMP for atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforAtomic(int n)
    {
    double somme = 0;
    double dx = 1.0/(double)n;
    double x;

    // V2
    #pragma omp parallel for private (x)
	for(int i = 0; i < n; i++)
	    {
	    // V1 : double x = ....
	    x = i * dx;

	    // pas bon ! n * NB_THREAD / NB_THREAD
	    // mais quand meme meilleur que critical for car fpi(x) est fait en parallel et += séquentiellement
	#pragma omp atomic
		somme += fpi(x);
	    }
	return somme/n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

