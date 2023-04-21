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
        Vec3f normal = ((v0 - v1).crossProduct(v0 - v2)).normalize();
        float distance = (v3 - (ray->origin)).dotProduct(normal) / normal.dotProduct(ray->direction);
        
        if (distance < 0 || (normal.dotProduct(ray->direction)) == 0)
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



        if (x >= 0 && x <= width.length() && y >= 0 && y <= height.length())
        {
            h.point = p;
            //h.normal = normal;
            h.t = distance;
            if (normal.dotProduct(ray->direction) < 0) h.normal = normal;
            else h.normal = -normal;
            return h;
        }
        else
        {
            h.t = INFINITY;
            h.normal = Vec3f(0, 0, 0);
            return h;
        }
    }

    Vec3f Plane::getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance)
    {
        //printf("Plane getRayColor");
        
        Vec2f texture = getTextureCoordinates(hit);
        return material->getColour(color, exponent, direction, distance, texture);
        //return 0;
    }
    
    Vec2f Plane::getTextureCoordinates(const Vec3f& point)
{
    Vec2f uv(-1, -1);

  //std::cout << material->isTexture << std::endl;
    if (material->isTexture)
    {
        Vec3f dir = point - v0;
        Vec3f width = v1 - v0;
        Vec3f height = v3 - v0;
        float projectionU = dir.dotProduct(width) / width.length();
        float u = projectionU / width.length();
        float projectionV = dir.dotProduct(height) / height.length();
        float v = projectionV / height.length();
        uv = Vec2f(u, v);
    }

    return uv;
}
    
    

} // namespace rt
