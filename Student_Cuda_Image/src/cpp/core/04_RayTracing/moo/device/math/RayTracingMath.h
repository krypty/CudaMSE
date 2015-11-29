#ifndef RAYTRACING_MATH_H_
#define RAYTRACING_MATH_H_

#include <math.h>
#include <cfloat>
#include "ColorTools.h"
#include "Sphere.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	RayTracingMath(Sphere* ptrDevSpheres, int n, float t)
	    {
        this->ptrDevSpheres = ptrDevSpheres;
        this->n = n;
        this->t = t;
	    }

	__device__
	virtual ~RayTracingMath(void)
	    {
	    //nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, float i, float j)
	    {
            float nearestZ = 0;
            int nearestZindex = -1;
            float nearestDz = 0;

            for(int k = 0; k < this->n; k++)
            {
                Sphere* s = &ptrDevSpheres[k];
                float2 xy;
                xy.x = i;
                xy.y = j;
                float hSquared = s->hSquared(xy);

                if(s->isBelow(hSquared))
                {
                    float dz = s->dz(hSquared);
                    float z = s->distance(dz);

                    if (z < nearestZ || nearestZindex < 0)
                    {
                        nearestZ = z;
                        nearestZindex = k;
                        nearestDz = dz;
                    }
                }

                ptrColor->w = 255; // opaque
            }

            // is the pixel below a sphere ?
            if (nearestZindex >= 0)
            {
                Sphere* s = &this->ptrDevSpheres[nearestZindex];
                ColorTools::HSB_TO_RVB(s->hue(t), 1.0f, s->brightness(nearestDz), ptrColor);
            }
            else
            {
                ptrColor->x = 0;
                ptrColor->y = 0;
                ptrColor->z = 0;
            }
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

 private:
     // inputs
     Sphere* ptrDevSpheres;
     int n;
     float t;

     // tools

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
