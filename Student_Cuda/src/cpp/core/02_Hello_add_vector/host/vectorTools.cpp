#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isAddVector_Ok(float* ptrV1, float* ptrV2, float* ptrW, int n);

float* createV1(int n);
float* createV2(int n);

void print(float* ptrV, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void addVectorCPU(float* ptrV1, float* ptrV2, float* ptrW, int n);

static bool isEgale(float* ptrV1, float* ptrV2, int n, float epsilon);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isAddVector_Ok(float* ptrV1, float* ptrV2, float* ptrW, int n)
    {
    float* ptrResult = new float[n];

    addVectorCPU(ptrV1, ptrV2, ptrResult, n);
    bool isOk = isEgale(ptrV1, ptrV2, n, 1e-6);

    delete[] ptrResult;

    return isOk;
    }


/**
 * 1 2 3 4 5
 */
float* createV1(int n)
    {
    float* ptrV = new float[n];

    for (int i = 0; i < n; i++)
	{
	ptrV[i] = i + 1;
	}

    return ptrV;
    }

/**
 * 10 20 30 40 50
 */
float* createV2(int n)
    {
    float* ptrV = new float[n];

    for (int i = 0; i < n; i++)
	{
	ptrV[i] = (i + 1) * 10;
	}

    return ptrV;
    }

void print(float* ptrV, int n)
    {
    cout << endl;
    for (int i = 0; i < n; i++)
	{
	cout << ptrV[i] << "\t";
	}
    cout << endl;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * v1,v2,w same size
 */
void addVectorCPU(float* ptrV1, float* ptrV2, float* ptrW, int n)
    {
    for (int i = 0; i < n; i++)
	{
	ptrW[i] = ptrV1[i] + ptrV2[i];
	}
    }

/**
 * simple
 */
bool isEgale(float* ptrV1, float* ptrV2, int n, float epsilon)
    {
    for (int i = 1; i <= n; i++)
	{
	float delta = fabs(*ptrV1 - *ptrV2);

	if (delta > epsilon)
	    {
	    return false;
	    }

	ptrV1++;
	ptrV2++;
	}

    return true;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

