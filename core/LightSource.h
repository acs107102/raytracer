/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "math/geometry.h"
#include "rapidjson/document.h"

using namespace rapidjson;

namespace rt
{

    class LightSource
    {
    public:
        //
        // Constructors
        //
        LightSource(){};

        //
        // Destructor
        //
        virtual ~LightSource();

        //
        // factory function : returns camera instance dynamically based on camera specifications
        //
        static LightSource *createLightSource(Value &lightSpecs);

        //
        // print function (to be implemented by the subclasses )
        //
        virtual void printLightSource() = 0;

        //
        // other LightSource functions (to complete)
        //

        // Getters and Setters
        //
        virtual Vec3f getPosition() = 0;
        virtual Vec3f getIntensity() = 0;
        virtual Vec3f getColor() = 0;
    };

} // namespace rt

#endif /* LIGHTSOURCE_H_ */
