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

bool isPiOMPEntrelacerAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerAtomic,  n, "Pi OMP Entrelacer atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
double piOMPEntrelacerAtomic(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double somme = 0;
    const double dx = 1.0/(double)n;

    #pragma omp parallel
    {
    int TID = OmpTools::getTid();
    int s = TID;
    double sommeThread = 0;
    double x;

    while(s < n)
	{
	x = s * dx;
	sommeThread += fpi(x);
	s += NB_THREAD;
	}

    // un seul thread a la fois qui peut faire une opération (+)
    #pragma omp atomic
	somme += sommeThread;
    }

    return somme / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

