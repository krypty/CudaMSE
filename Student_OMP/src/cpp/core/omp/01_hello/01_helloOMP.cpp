#include <iostream>
#include <stdio.h>
#include "omp.h"
#include "OmpTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void helloOMP1(void)
    {
    cout << endl << "[HelloOMP 1]" << endl;

    // OMP (facultatif)
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    cout << "\n[HELLO] nbThread = " << NB_THREADS << endl;

#pragma omp parallel
	{
	int tid = OmpTools::getTid();

	//cout << "tid=" << tid << endl; // ligne couper
	printf("tid=%i\n", tid); //ligne non couper
	}
    }

void helloOMP2(void)
    {
    cout << endl << "[HelloOMP 2]" << endl;

    // OMP (facultatif)
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    cout << "\n[CBI] nbThread = " << NB_THREADS << endl;

    int n = 20;
#pragma omp parallel for
    for (int i = 1; i <= n; i++)
	{
	//cout << "HelloOMP(" << i << ")" << endl; // ligne couper
	printf("HelloOMP(%i)\n", i); // ligne non couper
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

