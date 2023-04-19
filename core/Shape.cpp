/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/Sphere.h"

namespace rt
{
    Shape::~Shape() {}

    Shape *Shape::createShape(Value &shapeSpecs)
    {

        // check if shapeType is defined
        if (!shapeSpecs.HasMember("type"))
        {
            std::cerr << "Shape type not specified" << std::endl;
            exit(-1);
        }

        std::string shapeType = shapeSpecs["type"].GetString();

        // return shape object based on shape specs
        if (shapeType.compare("sphere") == 0)
        {
            std::printf("Creating sphere...\n");
            Sphere *sphere = new Sphere(
                Vec3f(shapeSpecs["center"][0].GetFloat(), shapeSpecs["center"][1].GetFloat(), shapeSpecs["center"][2].GetFloat()),
                shapeSpecs["radius"].GetFloat());

            sphere->material = Material::createMaterial(shapeSpecs["material"]);
            return sphere;
        }
    }

} // namespace rt
