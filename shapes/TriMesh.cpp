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


    Hit TriMesh::intersect(Ray *ray)
    {
        // printf("Hit triMesh\n");
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
    
    Vec3f TriMesh::getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance)
    {
        //Vec2f texture = getTextureCoordinates(hit);
        return material->getColour(color, exponent, direction, distance, Vec2f(-1, -1));
    }

    Vec2f TriMesh::getTextureCoordinates(const Vec3f& point)
    {
      Vec2f uv(-1, -1);
      std::cout << "texture: " << material->isTexture << std::endl;
      if (material->isTexture){
        std::cout << "vector face: " << vectorFace.size() << std::endl;
        for (int i = 0; i < vectorFace.size(); i++) {
          const Vec3f& v0 = vectorFace[i]->v0;
          const Vec3f& v1 = vectorFace[i]->v1;
          const Vec3f& v2 = vectorFace[i]->v2;
          
          if (isPointInsideTriangle(point, v0, v1, v2)) {
            Vec3f edge1 = v1 - v0;
            Vec3f edge2 = v2 - v0;
            Vec3f edge3 = v1 - v2;
            Vec3f dir = point - v0;

            float edge1Length = edge1.length();
            float width = edge1.dotProduct(edge3) / edge1Length;
            float height = edge1.crossProduct(edge2).length() / edge1Length;
        
            if(width < 0) width = 0;
            if(width > edge1Length) width = edge1Length;
            if(height < 0) height = 0;

            float v = sqrt(pow(-dir.length(), 2) - pow((-dir.dotProduct(edge1) / edge1Length), 2)) / height;
            float u = -dir.dotProduct(edge1.normalize()) / edge1Length;

            uv = Vec2f(u,v);

            std::cout << "trimesh uv " << uv << std::endl;
            break;
          }   
        }
      
      }
      return uv;
    }

    bool TriMesh::isPointInsideTriangle(const Vec3f& point, const Vec3f& v0, const Vec3f& v1, const Vec3f& v2) {
    // Calculate the vectors representing the edges of the triangle
      Vec3f edge1 = v1 - v0;
      Vec3f edge2 = v2 - v0;
      Vec3f edge3 = point - v0;

    // Calculate the dot products
      float dot11 = edge1.dotProduct(edge1);
      float dot22 = edge2.dotProduct(edge2);
      float dot12 = edge1.dotProduct(edge2);
      float dot13 = edge1.dotProduct(edge3);
      float dot23 = edge2.dotProduct(edge3);

    // Calculate the barycentric coordinates
      float invDenom = 1.0f / (dot11 * dot22 - dot12 * dot12);
      float u = (dot22 * dot13 - dot12 * dot23) * invDenom;
      float v = (dot11 * dot23 - dot12 * dot13) * invDenom;

    // Check if the point is inside the triangle
      return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
  }


} // namespace rt

