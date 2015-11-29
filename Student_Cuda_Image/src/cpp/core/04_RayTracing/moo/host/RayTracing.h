#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "VariateurI.h"
#include "Sphere.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracing: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	RayTracing(int w, int h, int nSphere, float dt);
	virtual ~RayTracing(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

    	/**
    	 * Call periodicly by the api
    	 */
    	virtual void process(uchar4* ptrDevPixels, int w, int h);
    	/**
    	 * Call periodicly by the api
    	 */
    	virtual void animationStep();

    	virtual float getAnimationPara();
        virtual string getTitle();
    	virtual int getW();
    	virtual int getH();

    private:
        void copySpheresToConstantMemory();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
    float dt;
    int nSphere;

	// Tools
	dim3 dg;
	dim3 db;
    float t;
    Sphere* ptrSpheres;
    Sphere* ptrDevSpheres;
    size_t sizeSpheres;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
