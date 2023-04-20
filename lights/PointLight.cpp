/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"

namespace rt
{

    PointLight::PointLight() : LightSource() {}
    PointLight::~PointLight() {}

    void PointLight::printLightSource()
    {
        printf("I am a point light! \n");
        printf("position: %dpx, %dpx, %d \n", position[0], position[1], position[2]);
    }

    Vec3f PointLight::getPosition()
    {
        return position;
    }

    Vec3f PointLight::getIntensity()  // is
    {
        return intensity;
    }

    Vec3f PointLight::getColor()   // id
    {
        return color;
    }

} // namespace rt
