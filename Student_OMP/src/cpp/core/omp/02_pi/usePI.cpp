#include <iostream>
#include <limits.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool isPiSequentiel_OK(int n);
extern bool isPiOMPEntrelacerPromotionTab_Ok(int n);
extern bool isPiOMPEntrelacerCritical_Ok(int n);
extern bool isPiOMPEntrelacerAtomic_Ok(int n);
extern bool isPiOMPforCritical_Ok(int n);
extern bool isPiOMPforAtomic_Ok(int n);
extern bool isPiOMPforPromotionTab_Ok(int n);
extern bool isPiOMPforReduction_Ok(int n);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool usePI(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool usePI(void)
    {
    cout << endl << "[PI]" << endl;

    int n = INT_MAX / 10;

    bool isOk = true;
    isOk &= isPiSequentiel_OK(n);
    isOk &= isPiOMPEntrelacerPromotionTab_Ok(n);
    isOk &= isPiOMPEntrelacerCritical_Ok(n);
    isOk &= isPiOMPEntrelacerAtomic_Ok(n);
    isOk &= isPiOMPforCritical_Ok(n);
    isOk &= isPiOMPforAtomic_Ok(n);
    isOk &= isPiOMPforPromotionTab_Ok(n);
    isOk &= isPiOMPforReduction_Ok(n);

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

