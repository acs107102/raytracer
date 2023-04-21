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

    Vec3f Triangle::getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance)
    {
        //printf("Triangle getRayColor");
        Vec2f texture = getTextureCoordinates(hit);
        return material->getColour(color, exponent, direction, distance, texture);
        // return 0;
    }
    
    Vec2f Triangle::getTextureCoordinates(const Vec3f& point){
    Vec2f uv(-1,-1);;
        if(material->isTexture){
            Vec3f edge1 = v1 - v0;
            Vec3f edge2 = v2 - v0;
            Vec3f edge3 = v1 - v2;
            Vec3f dir = point - v0;

            float edge1Length = edge1.length();
            float width = edge1.dotProduct(edge3) / edge1Length;
            float height = edge1.crossProduct(edge2).length() / edge1Length;
            
            if(width<edge1Length) width = edge1Length;

            float v = sqrt(pow(-dir.length(), 2) - pow((-dir.dotProduct(edge1) / edge1Length), 2)) / height;
            float u = -dir.dotProduct(edge1.normalize()) / edge1Length;

            uv = Vec2f(u,v);
        }
        return uv;
    }

} // namespace rt

