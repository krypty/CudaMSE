#ifndef SPHERE_H
#define SPHERE_H

#include "cudaTools.h"

#ifndef PI
#define PI 3.141592653589793f
#endif

class Sphere
{
public:
    __host__
    Sphere(float3 center, float radius, float hue)
    {
        //inputs
        this->center = center;
        this->r = radius;
        this->hueStart = hue;

        //tools
        this->rSquared = this->r * this->r;
        this->T = asin(2.0f * hueStart - 1.0f) - (3.0f * PI / 2.0f);
    }
    /*
    * required by example for new Sphere[n]
    */
    __host__
    Sphere()
    {
        // nothing
    }

    __device__
    float hSquared(float2 xyFloor)
    {
        float a = (center.x - xyFloor.x);
        float b = (center.y - xyFloor.y);
        return a * a + b * b;
    }

    __device__
    bool isBelow(float hSquared)
    {
        return hSquared < this->rSquared;
    }

    __device__
    float dz(float hSquared)
    {
        return sqrt(this->rSquared - hSquared);
    }

    __device__
    float brightness(float dz)
    {
        return dz / this->r;
    }

    __device__
    float distance(float dz)
    {
        return this->center.z - dz;
    }

    __device__
    float getHueStart()
    {
        return this->hueStart;
    }

    __device__
    float hue(float t) // useful for animation
    {
        return 0.5f + 0.5f * sin(t + ((3.0f * PI) / 2.0) + T);
    }

private:
    //inputs
    float r;
    float3 center;
    float hueStart;

    //tools
    float rSquared;
    float T;

};
#endif
