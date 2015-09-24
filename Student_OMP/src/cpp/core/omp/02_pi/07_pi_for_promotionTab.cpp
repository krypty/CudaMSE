#include <omp.h>
#include "00_pi_tools.h"
#include "MathTools.h"
#include "OmpTools.h"
#include "stdio.h"
#include "string.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread,int n);
static void syntaxeFull(double* tabSumThread,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double tabSumThread[NB_THREAD]; // toutes les cases a zéro
    memset(tabSumThread, 0, sizeof(double) * NB_THREAD);
    double x = 0;

    double somme = 0;
    const double dx = 1.0/(double)n;

    #pragma omp parallel for private (x)
	for(int i = 0; i < n; i++)
	    {
	    x = i * dx;
	    const int TID = OmpTools::getTid();

	    tabSumThread[TID] += fpi(x);
	    }

	//réduction séquentielle
	for(int i = 0; i < NB_THREAD; i++)
	    {
	    somme += tabSumThread[i];
	    }

	return somme / n;
	}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

