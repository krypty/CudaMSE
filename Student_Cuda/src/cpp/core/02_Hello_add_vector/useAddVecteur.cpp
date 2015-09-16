
#include <iostream>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void addVecteur(float* ptrV1, float* ptrV2, float* ptrW,int n);

extern float* createV1(int n);
extern float* createV2(int n);
extern void print(float* ptrV, int n);
extern bool isAddVector_Ok(float* ptrv1, float* ptrv2, float* ptrW, int n);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useAddVecteur(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useAddVecteur()
    {
    int n = 9;

    float* ptrV1 = createV1(n);
    float* ptrV2 = createV2(n);
    float* ptrW = new float[n];

    addVecteur(ptrV1, ptrV2, ptrW, n);

    print(ptrW, n); // check result

    bool isOk=isAddVector_Ok(ptrV1,ptrV2,ptrW,n);

    delete[] ptrV1;
    delete[] ptrV2;
    delete[] ptrW;

    return isOk;
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

