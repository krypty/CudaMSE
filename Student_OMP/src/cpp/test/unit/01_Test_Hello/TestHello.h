#ifndef TEST_HELLO_OMP_H
#define TEST_HELLO_OMP_H

#include "cpptest.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestHello: public Test::Suite
    {
    public:

	TestHello(void);

    private:

	void testHelloOMP1(void);
	void testHelloOMP2(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

