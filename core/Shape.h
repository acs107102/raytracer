/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"

namespace rt
{

	class Shape
	{
	public:
		//
		// Constructors
		//
		Shape(){};

		//
		// Destructor
		//
		virtual ~Shape();

		//
		// Shape abstract methods
		//
		virtual Hit intersect(Ray *) = 0;

		static Shape *createShape(Value &shapeSpecs);

		// virtual Vec2f textureCoordinates(Vec3f point) = 0;
		// virtual Vec3f getRayColor(Vec3f hit, Vec3f color); //, float exponent, Vec3f direction, float distance) = 0;

		Vec3f getMaterialColor(Vec3f diffuse, float specular, Vec3f is, float dist) const
		{
			return material->getColour(diffuse, specular, is, dist);
		}

		Vec3f getAmbient() const
		{
			return material->getAmbient();
		}

		float getReflect() const
		{
			return material->getReflect();
		}

	protected:
		Material *material;
	};

} // namespace rt

#endif /* SHAPE_H_ */
