/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"
#include <typeinfo>

namespace rt
{

    TriMesh::TriMesh() : Shape() {}
    TriMesh::~TriMesh() {}
    
    void TriMesh::readPLYFile(Vec3f position, std::string filename, float scale, std::vector<Vec3f *>& topPoint, std::vector<Triangle *>& vectorFace) {
    std::ifstream file(filename);
    if (file.is_open()) {
        // read the file header
        std::string line;
        int nTopPoint = 0, nVectorFace = 0;
        while (std::getline(file, line)) {
            if (line.rfind("element vertex", 0) == 0) {
                nTopPoint = std::stoi(line.substr(15));
            } else if (line.rfind("element face", 0) == 0) {
                nVectorFace = std::stoi(line.substr(13));
            } else if (line.rfind("end_header", 0) == 0) {
                break;
            }
        }

        // read the vertices
        for (int i = 0; i < nTopPoint; i++) {
            float x, y, z;
            file >> x >> y >> z;
            Vec3f *vertex = new Vec3f((x * scale) + position[0], (y * scale) + position[1], (z * scale) + position[2]);
            topPoint.push_back(vertex);
        }

        // read the faces
        for (int i = 0; i < nVectorFace; i++) {
            int nVertices;
            file >> nVertices;
            int vertexIndex1, vertexIndex2, vertexIndex3;
            file >> vertexIndex1 >> vertexIndex2 >> vertexIndex3;
            Vec3f *v0 = topPoint[vertexIndex1];
            Vec3f *v1 = topPoint[vertexIndex2];
            Vec3f *v2 = topPoint[vertexIndex3];
            Triangle *t = new Triangle(*v0, *v1, *v2);
            vectorFace.push_back(t);
        }

        file.close();
    }
}

    Vec3f TriMesh::getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance)
    {
        return material->getColour(color, exponent, direction, distance, Vec2f(-1, -1));
    }

    Hit TriMesh::intersect(Ray *ray)
    {
        // printf("trimesh intersection \n");
        Hit h;
        h.t = INFINITY;

        for (int i = 0; i < vectorFace.size(); i++)
        {
            Hit vectorF = vectorFace[i]->intersect(ray);

            if (vectorF.t > 0 && vectorF.t < h.t)
        {
            h = vectorF;
        }
        }
  
        

        return h;
    }

} // namespace rt

