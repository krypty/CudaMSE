#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(int w, int h)
	    {
	    dim2 = w / 2;
	    }

	__device__ RipplingMath(const RipplingMath& source)
	    {
	    dim2 = source.dim2;
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(int i, int j, float t, uchar4* ptrColor)
	    {
	    uchar levelGris;
	    f(i, j, t, &levelGris);

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    // ptrColor->w = 255; // alpha opaque
	    }

    private:

	__device__
	void f(int i, int j, float t, uchar* ptrLevelGris)
	    {
	    //TODO:
	    // Step1 : Delete le contenur de ce fichier (si!),
	    // Step2 : Copie-past le contenu de RipplingMath.h de omp,
	    // Step3 : Ajouter __device__  devant methode et constructeur!

	    float dijResult;
	    dij(i,j, &dijResult);

	    *ptrLevelGris = 128 + 127 * ((cos((dijResult/(10.0))-(t/7.0))) / ((dijResult/10.0)+1));
	    }

	__device__
	void dij(int i, int j, float* ptrResult)
	    {
	    float fi = i - this->dim2;
	    float fj = j - this->dim2;
	    *ptrResult = sqrt(fi*fi + fj*fj);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
