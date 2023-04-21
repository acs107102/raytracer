/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"
#include <iostream>
#include <fstream>
#include "parsers/PPMWriter.h"
#include <string>
using namespace std;

namespace rt
{

    Material::~Material(){};

    /**
     * Factory function that returns Material subclass based on shape specifications
     *
     * @param materialSpecs material specifications json object
     *
     * @return Material subclass instance
     *
     */
    Material *Material::createMaterial(Value &materialSpecs)
    {
        float Ks = 0, Kd = 0, Kr = 0, exponent = 0;
        Vec3f color(0, 0, 0);
        string texPath;
        int texWidth, texHeight = 0;
        vector<Vec3f> texture;

        // Ks
        if (materialSpecs.HasMember("ks"))
        {
            Ks = materialSpecs["ks"].GetFloat();
        }

        // Kd
        if (materialSpecs.HasMember("kd"))
        {
            Kd = materialSpecs["kd"].GetFloat();
        }

        // kr
        if (materialSpecs.HasMember("kr"))
        {
            Kr = materialSpecs["kr"].GetFloat();
        }

        // specularexponent
        if (materialSpecs.HasMember("specularexponent"))
        {
            exponent = materialSpecs["specularexponent"].GetFloat();
        }

        // diffusecolor
        if (materialSpecs.HasMember("diffusecolor"))
        {
            color = Vec3f(materialSpecs["diffusecolor"][0].GetFloat(), materialSpecs["diffusecolor"][1].GetFloat(), materialSpecs["diffusecolor"][2].GetFloat());
        }

        if (materialSpecs.HasMember("tPath"))
        {
            texPath = materialSpecs["tPath"].GetString();
            texWidth = materialSpecs["tWidth"].GetInt();
            texHeight = materialSpecs["tHeight"].GetInt();
            
            printf("find");
            std::cout << "find " << texPath << " " << texWidth << " " << texHeight << std::endl;

            vector<Vec3f> pixelbuffer;

            std::string line;
            texPath = texPath.substr(0, texPath.find_last_of('.')) + ".ppm";
            std::ifstream stream(texPath);
            int R, G, B;

            if (stream.is_open())
            {
                getline(stream, line);
                getline(stream, line);
                getline(stream, line);
                getline(stream, line);

                while (getline(stream, line))
                {
                    R = stoi(line.c_str());
                    getline(stream, line);
                    G = stoi(line.c_str());
                    getline(stream, line);
                    B = stoi(line.c_str());
                    pixelbuffer.push_back(Vec3f(R / 255.0, G / 255.0, B / 255.0));
                }

                stream.close();
            }
            texture = pixelbuffer;
        }

        Material *material = new BlinnPhong(Ks, Kd, Kr, exponent, color, texture, texWidth, texHeight);
        material->isTexture = materialSpecs.HasMember("tPath");
        //std::cout << "aa" << material->isTexture << std::endl;
        return material;
        //return new BlinnPhong(Ks, Kd, Kr, exponent, color);
    }

    // vector<Vec3f> Material::readTexture(string path, int height, int width)
    // {
    //     vector<Vec3f> pixelbuffer;

    //     string line;
    //     path = path.substr(0, path.find_last_of('.')) + ".ppm";
    //     ifstream stream(path);
    //     int R, G, B;

    //     getline(stream, line);
    //     getline(stream, line);
    //     getline(stream, line);
    //     getline(stream, line);

    //     while (getline(stream, line))
    //     {
    //         R = stoi(value.c_str());
    //         getline(stream, line);
    //         G = stoi(value.c_str());
    //         getline(stream, line);
    //         B = stoi(value.c_str());
    //         pixelbuffer.push_back(Vec3f(R / 255.0, G / 255.0, B / 255.0));
    //     }

    //     stream.close();
    //     return pixelbuffer;
    // }

} // namespace rt
