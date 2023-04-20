/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"

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
        else if (shapeType.compare("plane") == 0)
        {
            std::printf("Creating plane...\n");

            Plane *plane = new Plane(
                Vec3f(shapeSpecs["v0"][0].GetFloat(), shapeSpecs["v0"][1].GetFloat(), shapeSpecs["v0"][2].GetFloat()),
                Vec3f(shapeSpecs["v1"][0].GetFloat(), shapeSpecs["v1"][1].GetFloat(), shapeSpecs["v1"][2].GetFloat()),
                Vec3f(shapeSpecs["v2"][0].GetFloat(), shapeSpecs["v2"][1].GetFloat(), shapeSpecs["v2"][2].GetFloat()),
                Vec3f(shapeSpecs["v3"][0].GetFloat(), shapeSpecs["v3"][1].GetFloat(), shapeSpecs["v3"][2].GetFloat()));

            plane->material = Material::createMaterial(shapeSpecs["material"]);
            return plane;
        }
        else if (shapeType.compare("triangle") == 0)
        {
            std::printf("Creating triangle...\n");

            Triangle *triangle = new Triangle(
                Vec3f(shapeSpecs["v0"][0].GetFloat(), shapeSpecs["v0"][1].GetFloat(), shapeSpecs["v0"][2].GetFloat()),
                Vec3f(shapeSpecs["v1"][0].GetFloat(), shapeSpecs["v1"][1].GetFloat(), shapeSpecs["v1"][2].GetFloat()),
                Vec3f(shapeSpecs["v2"][0].GetFloat(), shapeSpecs["v2"][1].GetFloat(), shapeSpecs["v2"][2].GetFloat()));

            triangle->material = Material::createMaterial(shapeSpecs["material"]);
            return triangle;
        }
    }

} // namespace rt
