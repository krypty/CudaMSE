#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include "cpptest.h"

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestVector: public Suite
    {
    public:

	TestVector(int deviceId);

    private:

	void testAdd(void);

    private:

	int deviceId;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

