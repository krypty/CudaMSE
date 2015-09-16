#include "00_pi_tools.h"
#include <iostream>
#include "Chrono.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

double fpi(double x)
    {
    return 4 / (1 + x * x);
    }

bool isAlgoPI_OK(AlgoPI algoPI, int n, string title)
    {
    cout << endl << "[" << title << " running ...]" << endl;
    cout << "n=" << n << endl;

    Chrono chrono;
    double piHat = algoPI(n);
    chrono.stop();

    cout.precision(8);
    cout << "Pi hat  = " << piHat << endl;
    cout << "Pi true = " << PI << endl;

    bool isOk = MathTools::isEquals(piHat, PI, 1e-6);
    cout << "isOk = " << isOk << endl;

    cout.precision(3);
    chrono.print("time : ");

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

