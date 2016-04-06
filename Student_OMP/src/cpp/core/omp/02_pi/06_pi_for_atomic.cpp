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
{ // 1 set global variables, NB_THREADS, etc.
  double sum = 0;
  const double dx = 1.0 / (double) n;

  // 2 set parallel region with thread-local variables
  #pragma omp parallel
  {
    double partialSum = 0; // implicitly thread-private

    // 3 do some parallel computations
    #pragma omp for
    for (int i = 0; i < n ; i++)
    {
      partialSum += fpi ( i * dx );
    }

    /* 4 reduce partial results (atomic)
     *   atomic reduction are sequential for read-add-write
     */
    #pragma omp atomic
    sum += partialSum;
  }
  return sum / n;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

