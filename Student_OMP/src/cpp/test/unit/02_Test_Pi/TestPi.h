#ifndef TEST_PI_H
#define TEST_PI_H

#include "cpptest.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/


class TestPi: public Test::Suite
    {
    public:

	TestPi(void);

    private:

	void testSequentiel(void);
	void testEntrelacerPromotionTab(void);
	void testEntrelacerAtomic(void);
	void testEntrelacerCritical(void);
	void testCritical(void);
	void testAtomic(void);
	void testPromotionTab(void);
	void testForReduction(void);

    private:

	int n;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

