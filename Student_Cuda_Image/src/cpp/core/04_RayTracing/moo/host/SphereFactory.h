#ifndef SPHEREFACTORY_H
#define SPHEREFACTORY_H

#include <cstdlib>
#include <time.h>
#include "cudaTools.h"
#include "Sphere.h"

class SphereFactory
{
public:
    __host__
    static Sphere* createSpheres(int n, int w, int h, int margin)
    {
        // init random
        srand(time(NULL));

        Sphere* ptrSpheres = new Sphere[n];

        for(int i = 0; i < n; i++)
        {
            float3 center;
            center.x = getRandomFloat(margin, h - margin);
            center.y = getRandomFloat(margin, w - margin);
            center.z = getRandomFloat(10.0f, 2.0f * w);

            float radius = getRandomFloat(20.0f, w/10.0f);
            float hue = getRandomFloat(0.0f, 1.0f);

            ptrSpheres[i] = Sphere(center, radius, hue);
        }

        return ptrSpheres;
    }

private:
    static float getRandomFloat(float min, float max)
    {
        return ((max - min) * ((float)rand()/RAND_MAX)) + min;
    }

};
#endif
