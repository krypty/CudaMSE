#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMath(unsigned int w, unsigned int h)
	    {
	    this->dim2 = w / 2;
	    }

	virtual ~RipplingMath(void)
	    {
	    //rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * ptrColor represente le pixel (i,j) de l'image. uchar pour 4 cannaux color (r,g,b,alpha) chacun dans [0,255]
	 */
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    // TODO
	    }

    private:

	void dij(int i, int j, float* ptrResult) // par exmple
	    {
	    //TODO
	    }


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	double dim2; //=dim/2

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
