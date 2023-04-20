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

        Vec3f getColour(Vec3f color, float exponent, Vec3f direction, float distance, Vec2f texture)
        {
            Vec3f baseColor;
            baseColor = diffusecolor;
            /*
			if(texture.x != -1 && hasTexture){
				//use texture instead if there is one to set the base color
				int u = texture.x * tWidth;
				int v = texture.y * tHeight;
				baseColor = texture[u + (v*tWidth)];
			}
			else{
				baseColor = diffusecolor;
			}
*/
			Vec3f dif = kd * color ;
			Vec3f spec = (ks * std::pow(exponent,(exponent))) * direction;
			// can also divide by dist*dist as explained in report
			return ((dif + spec) * baseColor) /= distance;
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
