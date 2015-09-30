#ifndef MANDELBROT_MOO_H_
#define MANDELBROT_MOO_H_

#include "cudaType.h"
#include "AnimableFonctionel_I.h"

#include "VariateurF.h"
#include "MandelbrotMath.h" // car use dans .h
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMOO: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMOO(unsigned int w, unsigned int h, float dt, int n);
	virtual ~MandelbrotMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);
	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

	virtual float getAnimationPara();
	virtual int getW();
	virtual int getH();
	virtual string getTitle(void);
	virtual DomaineMath* getDomaineMathInit(void);

	virtual void setParallelPatern(ParallelPatern parallelPatern);

    private:

	void forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);
	void entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

	void workPixel(uchar4* ptrColorIJ, int i, int j, int s, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	unsigned int w;
	unsigned int h;
	DomaineMath domaineMathInit;

	// Outputs
	string title;

	// Tools
	VariateurF variateurT; // fait varier para animation t
	ParallelPatern parallelPatern;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
