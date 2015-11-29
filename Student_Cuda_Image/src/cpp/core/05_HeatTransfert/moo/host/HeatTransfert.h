#ifndef HEAT_TRANSFERT_H_
#define HEAT_TRANSFERT_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"

#define IMAGEWIDTH 800
#define IMAGEHEIGHT 800

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class HeatTransfert: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	HeatTransfert(int w, int h, float dt);
	virtual ~HeatTransfert(void);

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

	void initImages();
	void memoryManagment();

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
	int t;
	bool isImageAInput;
	int nbIterations;
	int NB_ITERATION_AVEUGLE;

	float* imageHeater;
	float* imageInit;
	float* ptrDevImageInit;
	float* ptrDevImageHeater;
	float* ptrDevImageA;
	float* ptrDevImageB;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
