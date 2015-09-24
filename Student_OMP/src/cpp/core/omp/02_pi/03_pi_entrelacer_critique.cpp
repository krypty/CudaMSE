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

bool isPiOMPEntrelacerCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerCritical(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerCritical, n, "Pi OMP Entrelacer critical");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piOMPEntrelacerCritical(int n)
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

	// section critique
	#pragma omp critical (toto)
	    {
	    somme += sommeThread;
	    }
	}

    return somme / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

