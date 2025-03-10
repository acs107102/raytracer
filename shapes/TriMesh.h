/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "shapes/Triangle.h"
// #include "shapes/BVH.h"

#include <fstream>	// for read file

using namespace std;

namespace rt
{

    class TriMesh : public Shape
    {

    public:
        TriMesh();
        TriMesh(Vec3f position, std::string ply, float scale) : position(position)
        {
            readPLYFile(position, ply, scale, topPoint, vectorFace);
        };

        virtual ~TriMesh();

        Hit intersect(Ray *ray);

        Vec3f getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance);
        
        Vec2f getTextureCoordinates(const Vec3f& point);
        float interpolate(const Vec3f& point, const Vec3f& v0, const Vec3f& v1, const Vec3f& v2, float minValue, float maxValue, bool isXAxis);
        bool isPointInsideTriangle(const Vec3f& point, const Vec3f& v0, const Vec3f& v1, const Vec3f& v2);
    private:
        void readPLYFile(Vec3f position, std::string filename, float scale, std::vector<Vec3f *>& topPoint, std::vector<Triangle *>& vectorFace) ;
        Vec3f position;
        vector<Vec3f *> topPoint;
        vector<Triangle *> vectorFace;
    };

} // namespace rt

#endif /* TRIMESH_H_ */

