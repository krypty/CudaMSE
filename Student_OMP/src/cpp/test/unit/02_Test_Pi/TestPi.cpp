#include "TestPi.h"
#include <limits.h>

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

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


TestPi::TestPi(void)
    {
    this->n=INT_MAX/10;

    TEST_ADD(TestPi::testSequentiel);

    TEST_ADD(TestPi::testEntrelacerPromotionTab);
    TEST_ADD(TestPi::testEntrelacerAtomic);
    TEST_ADD(TestPi::testEntrelacerCritical);

    TEST_ADD(TestPi::testAtomic);
    TEST_ADD(TestPi::testCritical);
    TEST_ADD(TestPi::testPromotionTab);
    TEST_ADD(TestPi::testForReduction);
    }

void TestPi::testSequentiel(void)
    {
    TEST_ASSERT(isPiSequentiel_OK(n)==true);
    }

void TestPi::testEntrelacerPromotionTab(void)
    {
    TEST_ASSERT(isPiOMPEntrelacerPromotionTab_Ok(n)==true);
    }

void TestPi::testEntrelacerAtomic(void)
    {
    TEST_ASSERT(isPiOMPEntrelacerAtomic_Ok(n)==true);
    }

void TestPi::testEntrelacerCritical(void)
    {
    TEST_ASSERT(isPiOMPEntrelacerCritical_Ok(n)==true);
    }

void TestPi::testCritical(void)
    {
    TEST_ASSERT(isPiOMPforCritical_Ok(n)==true);
    }

void TestPi::testAtomic(void)
    {
    TEST_ASSERT(isPiOMPforAtomic_Ok(n)==true);
    }

void TestPi::testPromotionTab(void)
    {
    TEST_ASSERT(isPiOMPforPromotionTab_Ok(n)==true);
    }

void TestPi::testForReduction(void)
    {
    TEST_ASSERT(isPiOMPforReduction_Ok(n)==true);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

