#ifndef RIPPLING_H_
#define RIPPLING_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Rippling: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Rippling(int w, int h, float dt);
	virtual ~Rippling(void);

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

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	float dt;

	// Tools
	dim3 dg;
	dim3 db;
	float t;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
