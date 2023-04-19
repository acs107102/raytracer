/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"

namespace rt
{

    class PointLight : public LightSource
    {
    public:
        //
        // Constructors
        //
        PointLight();
        PointLight(Vec3f position, Vec3f intensity, Vec3f color) : position(position), intensity(intensity), color(color){};

        //
        // Destructor
        //
        virtual ~PointLight();

        //
        // print function (to be implemented by the subclasses )
        //
        void printLightSource();

        //
        // other LightSource functions (to complete)
        //
        Vec3f getIntensity();
        Vec3f getColor();
        Vec3f getPosition();

    private:
        Vec3f position;
        Vec3f intensity;
        Vec3f color;
    };

} // namespace rt

#endif /* POINTLIGHT_H_ */
