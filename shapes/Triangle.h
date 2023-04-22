/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
// #include "shapes/Bounds.h"

namespace rt
{

    class Triangle : public Shape
    {

    public:
        Triangle();
        Triangle(Vec3f v0, Vec3f v1, Vec3f v2) : v0(v0), v1(v1), v2(v2){};

        virtual ~Triangle();

        Hit intersect(Ray *ray);

        Vec3f getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance);
        
        Vec2f getTextureCoordinates(const Vec3f& point);


    public:
        Vec3f v0;
        Vec3f v1;
        Vec3f v2;
    };

} // namespace rt

#endif /* TRIANGLE_H_ */

