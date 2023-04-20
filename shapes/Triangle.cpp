/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"

namespace rt
{

    Triangle::Triangle() : Shape() {}
    Triangle::~Triangle() {}

    Hit Triangle::intersect(Ray *ray)
    {
        Hit h;
        h.shape = this;
        Vec3f normal = ((v0 - v1).crossProduct(v0 - v2)).normalize();

        float distance = (v2 - (ray->origin)).dotProduct(normal) / normal.dotProduct(ray->direction);
        h.t = distance;
        if (distance < 0)
        {
            h.t = INFINITY;
            h.normal = Vec3f(0, 0, 0);
            return h;
        }

        // float t = (*v0 - (ray->origin)).dotProduct(normal) / distance;
        Vec3f p = ray->origin + distance * (ray->direction);

        // three edge
        Vec3f v01 = v1 - v0;
        Vec3f v12 = v2 - v1;
        Vec3f v02 = v0 - v2;

        // three direction
        Vec3f direction1 = p - v0;
        Vec3f direction2 = p - v1;
        Vec3f direction3 = p - v2;

        if ((normal.dotProduct(ray->direction)) > 0)
        {
            h.normal = -h.normal;
        }

        if (normal.dotProduct(v01.crossProduct(direction1)) > 0 &&
            normal.dotProduct(v12.crossProduct(direction2)) > 0 &&
            normal.dotProduct(v02.crossProduct(direction3)) > 0)
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

    // Vec3f Triangle::getMaterialColor(Vec3f hitPoint, Vec3f diffuse, float specular, Vec3f is, float dist)
    Vec3f Triangle::getRayColor(Vec3f hit, Vec3f color)
    {
        printf("Triangle getRayColor");
        // Vec2f uv(-1, -1);
        // if (material->hasTexture)
        // {
        //     // get u,v coordinate Vec2f
        //     Vec3f bottomEdge = *v1 - *v0;
        //     Vec3f N = bottomEdge.crossProduct(*v2 - *v0);
        //     float area = N.length() / 2;
        //     float height = 2 * area / bottomEdge.length();
        //     float width = (*v1 - *v2).dotProduct(bottomEdge) / bottomEdge.length();

        //     if (width < bottomEdge.length())
        //         width = bottomEdge.length();

        //     Vec3f widthVec = bottomEdge.normalize() * width;
        //     float heightVec = pow((hitPoint - *v0).length(), 2) - pow(((hitPoint - *v0).dotProduct(bottomEdge) / bottomEdge.length()), 2);
        //     heightVec = sqrt(heightVec);

        //     float v = heightVec / height;
        //     float u = (hitPoint - *v0).dotProduct(widthVec) / widthVec.length();
        //     u = u / width;
        //     uv = Vec2f(1 - u, v);
        // }
        // return material->getColor(diffuse, specular, is, dist, uv);
        return 0;
    }

} // namespace rt

