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

        // Bounds getBounds()
        // {
        //     float max_x = std::max((*v0)[0], std::max((*v1)[0], (*v2)[0]));
        //     float max_y = std::max((*v0)[1], std::max((*v1)[1], (*v2)[1]));
        //     float max_z = std::max((*v0)[2], std::max((*v1)[2], (*v2)[2]));
        //     Vec3f max(max_x, max_y, max_z);

        //     float min_x = std::min((*v0)[0], std::min((*v1)[0], (*v2)[0]));
        //     float min_y = std::min((*v0)[1], std::min((*v1)[1], (*v2)[1]));
        //     float min_z = std::min((*v0)[2], std::min((*v1)[2], (*v2)[2]));
        //     Vec3f min(min_x, min_y, min_z);

        //     return Bounds(min, max);
        // }

    private:
        Vec3f v0;
        Vec3f v1;
        Vec3f v2;
    };

} // namespace rt

#endif /* TRIANGLE_H_ */

