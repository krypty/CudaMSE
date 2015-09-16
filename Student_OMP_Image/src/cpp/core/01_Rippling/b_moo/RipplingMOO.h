#ifndef RIPPLING_MOO_H_
#define RIPPLING_MOO_H_

#include "cudaType.h"
#include "Animable_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMOO: public Animable_I
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMOO(unsigned int w, unsigned int h, float dt);
	virtual ~RipplingMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/*--------------------------------------*\
	|*	Override Animable_I		*|
	 \*-------------------------------------*/

	virtual void process(uchar4* ptrDevImageGL, int w, int h);
	virtual void animationStep();

	virtual float getAnimationPara();
	virtual int getW();
	virtual int getH();
	virtual string getTitle();

	virtual void setParallelPatern(ParallelPatern parallelPatern);

    private:

	void entrelacementOMP(uchar4* ptrTabPixels,int w,int h); 	// Code entrainement Cuda
	void forAutoOMP(uchar4* ptrTabPixels,int w,int h); 		// Code naturel et direct OMP, plus performsnt

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double dt;
	unsigned int w;
	unsigned int h;

	// Tools
	double t;
	ParallelPatern parallelPatern;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
