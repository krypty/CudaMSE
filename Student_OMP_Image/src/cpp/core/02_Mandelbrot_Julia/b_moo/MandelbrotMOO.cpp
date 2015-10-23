#include <iostream>
#include <math.h>

#include "MandelbrotMOO.h"

#include "OmpTools.h"
#include "MathTools.h"

#include "IndiceTools.h"
#include "JuliaMath.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * variateurT: 	fait varier t in [0,2pi] par increment de dt,
 * 		d'abord de mani�re croissante jusqua 2PI, puis de maniere decroissante jusqua 0, puis en boucle a l'infini selon ce procede
 */
MandelbrotMOO::MandelbrotMOO(unsigned int w, unsigned int h)
    {
    // Inputs
    this->w = w;
    this->h = h;

    /* décommenter un des ces exemples pour changer de fractal (Mandelbrot ou Julia)
     Ces exemples correspondent au PDF 06_TP_MandelBrot_Julia_006.pdf.
     */
//    initFractalEx1();
//    initFractalEx2();
//    initFractalEx3();
//    initFractalEx4();
    initFractalEx5();

// Outputs
    this->title = "Mandelbrot_OMP (Zoomable)";

    // Tools
    this->parallelPatern = OMP_MIXTE;

    // OMP (facultatif)
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    cout << "\n[Mandelbrot] nbThread = " << NB_THREADS << endl;
    ;
    }

MandelbrotMOO::~MandelbrotMOO(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 */
void MandelbrotMOO::process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    switch (parallelPatern)
	{

	case OMP_ENTRELACEMENT: // Plus lent sur CPU
	    {
	    entrelacementOMP(ptrTabPixels, w, h, domaineMath);
	    break;
	    }

	case OMP_FORAUTO: // Plus rapide sur CPU
	    {
	    forAutoOMP(ptrTabPixels, w, h, domaineMath);
	    break;
	    }

	case OMP_MIXTE: // Pour tester que les deux implementations fonctionnent
	    {
	    // Note : Des saccades peuvent apparaitre � cause de la grande difference de fps entre la version entrelacer et auto
	    static bool isEntrelacement = true;
	    if (isEntrelacement)
		{
		entrelacementOMP(ptrTabPixels, w, h, domaineMath);
		}
	    else
		{
		forAutoOMP(ptrTabPixels, w, h, domaineMath);
		}
	    isEntrelacement = !isEntrelacement; // Pour swithcer a chaque iteration
	    break;
	    }
	}
    }

/**
 * Override
 */
void MandelbrotMOO::animationStep()
    {
    variateurN->varierAndGet();
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

/**
 * Override
 */
float MandelbrotMOO::getAnimationPara()
    {
    return variateurN->get();
    }

/**
 * Override
 */
string MandelbrotMOO::getTitle()
    {
    return title;
    }

/**
 * Override
 */
int MandelbrotMOO::getW()
    {
    return w;
    }

/**
 * Override
 */
int MandelbrotMOO::getH()
    {
    return h;
    }

/**
 * Override
 */
DomaineMath* MandelbrotMOO::getDomaineMathInit(void)
    {
    return &domaineMathInit;
    }

/*-------------*\
 |*     set	*|
 \*------------*/

void MandelbrotMOO::setParallelPatern(ParallelPatern parallelPatern)
    {
    this->parallelPatern = parallelPatern;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Code naturel et direct OMP
 */
void MandelbrotMOO::forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    //int s = i * W + j;
	    int s = IndiceTools::toS(w, i, j); // i[0,H[ j[0,W[  --> s[0,W*H[

	    workPixel(&ptrTabPixels[s], i, j, s, domaineMath, mandelbrotMath);
	    }
	}
    }

/**
 * Code entrainement Cuda
 */
void MandelbrotMOO::entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel

	const int TID = OmpTools::getTid();
	int s = TID; // in [0,...

	int i;
	int j;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    workPixel(&ptrTabPixels[s], i, j, s, domaineMath, mandelbrotMath);

	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [1,h]
 * j in [1,w]
 * code commun �
 * 	entrelacementOMP
 * 	forAutoOMP
 */
void MandelbrotMOO::workPixel(uchar4* ptrColorIJ, int i, int j, int s, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    float n = variateurN->get();
    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, domaineMath, n); // in [01]
    }

void MandelbrotMOO::initFractalEx1()
    {
    int nMin = 12;
    int nMax = 100;
    this->variateurN = new VariateurI(IntervalI(nMin, nMax), 1);

    this->mandelbrotMath = new MandelbrotMath();
    this->domaineMathInit = DomaineMath(-2.1, -1.3, 0.8, 1.3);
    }

void MandelbrotMOO::initFractalEx2()
    {
    int nMin = 30;
    int nMax = 110;
    this->variateurN = new VariateurI(IntervalI(nMin, nMax), 1);

    this->mandelbrotMath = new MandelbrotMath();
    this->domaineMathInit = DomaineMath(-1.3968, -0.03362, -1.3578, 0.0013973);
    }

void MandelbrotMOO::initFractalEx3()
    {
    int nMin = 30;
    int nMax = 110;
    float c1 = -0.12f;
    float c2 = 0.85f;
    this->variateurN = new VariateurI(IntervalI(nMin, nMax), 1);

    this->mandelbrotMath = new JuliaMath(c1, c2);
    this->domaineMathInit = DomaineMath(-1.3, -1.4, 1.3, 1.4);
    }

void MandelbrotMOO::initFractalEx4()
    {
    int nMin = 80;
    int nMax = 300;
    float c1 = -0.745f;
    float c2 = 0.1f;
    this->variateurN = new VariateurI(IntervalI(nMin, nMax), 1);

    this->mandelbrotMath = new JuliaMath(c1, c2);
    this->domaineMathInit = DomaineMath(-1.7, -1.0, 1.7, 1.0);
    }

void MandelbrotMOO::initFractalEx5()
    {
    int nMin = 15;
    int nMax = 110;
    float c1 = -0.52f;
    float c2 = 0.57f;
    this->variateurN = new VariateurI(IntervalI(nMin, nMax), 1);

    this->mandelbrotMath = new JuliaMath(c1, c2);
    this->domaineMathInit = DomaineMath(-1.7, -1.2, 1.7, 1.2);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

