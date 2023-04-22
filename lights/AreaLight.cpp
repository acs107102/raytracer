/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"




namespace rt{
/*
    AreaLight::AreaLight(Vec3f c1, Vec3f c2, Vec3f c3, Vec3f is, Vec3f id):LightSource((c1+c3)*0.5), intensity(is), color(id){
        corner = c2;
        width = c1-c2;
        height = c3-c2;
    }


    void AreaLight::printLightSource()
    {
        printf("I am a point light! \n");
        //printf("position: %dpx, %dpx, %d \n", c1, c2, c3);
    }

    Vec3f AreaLight::getPosition()
    {
        return position;
    }

    Vec3f AreaLight::getIntensity()  // is
    {
        return intensity;
    }

    Vec3f AreaLight::getColor()   // id
    {
        return color;
    }

    Vec3f AreaLight::getSampleP() {
        float rx = rand() / (float)RAND_MAX;
        float ry = rand() / (float)RAND_MAX;
        return (corner + rx*width + ry*height);
    }

*/
} //namespace rt
