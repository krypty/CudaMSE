#ifndef MANDELBROT_MOO_H_
#define MANDELBROT_MOO_H_

#include "cudaType.h"
#include "AnimableFonctionel_I.h"

#include "VariateurI.h"
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

	MandelbrotMOO(unsigned int w, unsigned int h);
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

	void initFractalEx1();
	void initFractalEx2();
	void initFractalEx3();
	void initFractalEx4();
	void initFractalEx5();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	unsigned int w;
	unsigned int h;
	DomaineMath domaineMathInit;

	// Outputs
	string title;

	// Tools
	VariateurI* variateurN; // fait varier para animation t
	ParallelPatern parallelPatern;
	MandelbrotMath* mandelbrotMath;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
