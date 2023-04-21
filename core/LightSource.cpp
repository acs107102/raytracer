/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "lights/AreaLight.h"
#include "lights/PointLight.h"

namespace rt
{

    LightSource::~LightSource(){};
    LightSource *LightSource::createLightSource(Value &lightSpecs)
    {
        if (!lightSpecs.HasMember("type"))
        {
            std::cerr << "Lightsource type not specified" << std::endl;
            exit(-1);
        }

        std::string lightType = lightSpecs["type"].GetString();

        if (lightType.compare("pointlight") == 0)
        {
            printf("creating pointlight.. \n");
            std::cout << "position: " << lightSpecs["position"][0].GetFloat() << lightSpecs["position"][1].GetFloat() << lightSpecs["position"][2].GetFloat() << std::endl;
            return new PointLight(
                Vec3f(lightSpecs["position"][0].GetFloat(), lightSpecs["position"][1].GetFloat(), lightSpecs["position"][2].GetFloat()),
                Vec3f(lightSpecs["is"][0].GetFloat(), lightSpecs["is"][1].GetFloat(), lightSpecs["is"][2].GetFloat()),
                Vec3f(lightSpecs["id"][0].GetFloat(), lightSpecs["id"][1].GetFloat(), lightSpecs["id"][2].GetFloat()));
        }
        // else if (lightType.compare("arealight") == 0)
        // {
        //     printf("creating arealight.. \n");
        //     return new AreaLight(
        //         Vec3f(lightSpecs["p0"][0].GetFloat(), lightSpecs["p0"][1].GetFloat(), lightSpecs["p0"][2].GetFloat()),
        //         Vec3f(lightSpecs["p1"][0].GetFloat(), lightSpecs["p1"][1].GetFloat(), lightSpecs["p1"][2].GetFloat()),
        //         Vec3f(lightSpecs["p2"][0].GetFloat(), lightSpecs["p2"][1].GetFloat(), lightSpecs["p2"][2].GetFloat()),
        //         Vec3f(lightSpecs["intensity"][0].GetFloat(), lightSpecs["intensity"][1].GetFloat(), lightSpecs["intensity"][2].GetFloat()),
        //         Vec3f(lightSpecs["color"][0].GetFloat(), lightSpecs["color"][1].GetFloat(), lightSpecs["color"][2].GetFloat()));
        // }
        return 0;
    }

} // namespace rt
