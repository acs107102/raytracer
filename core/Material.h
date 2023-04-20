/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"
#include "rapidjson/document.h"
#include <vector>
using namespace rapidjson;

namespace rt
{

    class Material
    {
    public:
        //
        // Constructors
        //
        Material(){};
        // Material(Vec3f color) : color(color){};
        // Material(Vec3f color, float ks, float kd, float exponent, float kr) : color(color), ks(ks), kd(kd), exponent(exponent), kr(kr), isTexture(false){};
        // Material(Vec3f color, float ks, float kd, float exponent, float kr, std::string texture, int tWidth, int tHeight);

        //
        // Destructor
        //
        virtual ~Material();

        static Material *createMaterial(Value &materialSpecs);

        virtual Vec3f getColour(Vec3f color, float exponent, Vec3f direction, float distance, Vec2f texture) = 0;
        //virtual Vec3f getColour(Vec3f diffuse, float specular, Vec3f is, float dist) = 0;
        virtual Vec3f getAmbient() = 0;
        virtual float getReflect() = 0;

        // static std::vector<Vec3f> readTexture(std::string file, int h, int w);

    private:
        // bool isTexture;
        // float ks;
        // float kd;
        // float kr;
        // float exponent;
        // Vec3f color;
        // std::vector<Vec3f> texture;
        // int tWidth;
        // int tHeight;
    };

} // namespace rt

#endif /* MATERIAL_H_ */
