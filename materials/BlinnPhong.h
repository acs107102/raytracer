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
        BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor, std::vector<Vec3f> texture, int tWidth, int tHeight) : ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor), texture(texture), tWidth(tWidth), tHeight(tHeight) {}
        
         //BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor) : ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor){}

        //
        // Destructor
        //
        virtual ~BlinnPhong();

        Vec3f getColour(Vec3f color, float exponent, Vec3f direction, float distance, Vec2f textureXY)
        {
            Vec3f baseColor;
            // baseColor = diffusecolor;
            
            std::cout << "textureXY " << textureXY << std::endl;
            printf("get colour\n");
			if(textureXY.x != -1 && isTexture){
			printf("hi");
				int u = textureXY.x * tWidth;
				int v = textureXY.y * tHeight;
				baseColor = texture[u + (v*tWidth)];
			}
			else{
			printf("here");
				baseColor = diffusecolor;
			}
// std::cout << "check spec: " << exponent << " " << specularexponent << std::endl;
// std::cout << "check dif: " << color << " " << diffusecolor << std::endl;
			Vec3f dif = kd * color ;
			Vec3f spec = (ks * std::pow(exponent,(specularexponent))) * direction;
			return ((dif + spec) * baseColor) /= distance;
			//return (dif + spec) /= distance;
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
        std::vector<Vec3f> texture;
		int tWidth;
		int tHeight;
    };

} // namespace rt

#endif /* BLINNPHONG_H_ */
