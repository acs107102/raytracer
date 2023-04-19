/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"
#include "core/RayHitStructs.h"

namespace rt
{

    class BlinnPhong : public Material
    {
    public:
        //
        // Constructors
        //
        BlinnPhong();
        // BlinnPhong(Vec3f diffusecolor);
        // ka * ia + for each light: kd(L_m * N)*id_m  + ks(R_m * V)^exponent * is_m
        // ^ ambient + sum(m in light) diffuse_m + specular_m
        // R is mirror reflection direction
        BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor) : ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor)
        {
            // printf("creating blinnphong %f %f %f \n", diffusecolor[0], diffusecolor[1], diffusecolor[2]);

            // this->diffusecolor = diffusecolor;
        }

        //
        // Destructor
        //
        virtual ~BlinnPhong();

        Vec3f getColour(Vec3f diffuse, float specular, Vec3f is, float dist)
        {
            Vec3f intensity(0, 0, 0);

            Vec3f dif = kd * diffuse * diffusecolor;
            Vec3f spec = (ks * std::pow(specular, (specularexponent))) * is;
            // if(kr!=0){
            //     reflection = kr * castRay(hitPoint + hitNormal * options.bias, R, objects, lights, options, depth + 1);
            // }
            return ((dif /= dist) + (spec /= dist));
        }

        Vec3f getAmbient()
        {
            return diffusecolor;
        }

        float getReflect()
        {
            return kr;
        }

        // float getKs(){
        // 	return ks;
        // }

        // float getKd(){
        // 	return kd;
        // }

        // float getKr(){
        // 	return kr;
        // }

        // float getExponent(){
        // 	return specularexponent;
        // }

        // Vec3f getColor(){
        // 	return diffusecolor;
        // }

    private:
        float ks;
        float kd;
        float kr;
        float specularexponent;
        Vec3f diffusecolor;
    };

} // namespace rt

#endif /* BLINNPHONG_H_ */
