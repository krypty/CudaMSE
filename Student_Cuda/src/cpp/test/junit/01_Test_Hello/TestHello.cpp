#include "TestHello.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool helloCuda(void);
extern bool isAddScalarGPU_Ok(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

TestHello::TestHello(int deviceId)
    {
    this->deviceId=deviceId;

    TEST_ADD(TestHello::testHelloCuda);
    TEST_ADD(TestHello::testAdd);
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

void TestHello::testHelloCuda(void)
    {
    TEST_ASSERT(helloCuda() == true);
    }

void TestHello::testAdd(void)
    {
    TEST_ASSERT(isAddScalarGPU_Ok() == true);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

