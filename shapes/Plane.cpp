/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"

namespace rt
{

    Plane::Plane() : Shape() {}
    Plane::~Plane() {}

    /**
     * Computes whether a ray hit the specific instance of a Plane shape and returns the hit data
     *
     * @param ray cast ray to check for intersection with shape
     *
     * @return hit struct containing intersection information
     *
     */
    Hit Plane::intersect(Ray *ray)
    {
        Hit h;
        h.shape = this;
        //-----------to be implemented -------------
        Vec3f normal = ((v0 - v1).crossProduct(v0 - v3)).normalize();
        float distance = (v3 - (ray->origin)).dotProduct(normal) / normal.dotProduct(ray->direction);
        h.t = distance;
        if (distance < 0)
        {
            h.t = INFINITY;
            h.normal = Vec3f(0, 0, 0);
            return h;
        }

        // float t = (v3 - (ray->origin)).dotProduct(normal) / distance;
        Vec3f p = ray->origin + distance * (ray->direction);

        Vec3f height = v1 - v0;
        Vec3f width = v3 - v0;

        Vec3f direction = p - v0;

        float x = direction.dotProduct(width) / width.length();
        // std::cout << "x: " << x << std::endl;
        float y = direction.dotProduct(height) / height.length();
        // std::cout << "y: " << y << std::endl;

        if ((normal.dotProduct(ray->direction)) > 0)
        {
            h.normal = -h.normal;
        }

        if (x >= 0 && x <= width.length() && y >= 0 && y <= height.length())
        {
            h.point = p;
            h.normal = normal;
            return h;
        }
        else
        {
            h.t = INFINITY;
            h.normal = Vec3f(0, 0, 0);
            return h;
        }
    }

    Vec3f Plane::getRayColor(Vec3f hit, Vec3f color)
    {
        printf("Plane getRayColor");
        // Vec2f uv(-1, -1);
        // Vec3f point = (hit - center).normalize();
        // if (material->isTexture)
        // {
        // 	float projection_u = (hitPoint - v3).dotProduct(v2-v3) / (v2-v3).length();
        // 	float u = projection_u / (v2-v3).length();
        //      float projection_v = (hitPoint - v3).dotProduct(v0-v3) / (v0-v3).length();
        //      v = projection_v / (v0-v3).length();
        // 	uv = Vec2f(u, v);
        // }
        // return material->getColor(diffuse, specular, is, dist, uv);
        return 0;
    }

} // namespace rt
