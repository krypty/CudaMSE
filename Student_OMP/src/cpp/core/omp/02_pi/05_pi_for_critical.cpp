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

bool isPiOMPforCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforCritique(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforCritique, n, "Pi OMP for critique");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforCritique(int n)
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
	#pragma omp critical (toto)
		{
		somme += fpi(x);
		}
	    }
	return somme/n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

