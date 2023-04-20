/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace rt
{

	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */

	Sphere::Sphere() : Shape() {}
	Sphere::~Sphere() {}

	Hit Sphere::intersect(Ray *ray)
	{

		Hit h;
		//-----------to be implemented -------------
		h.shape = this;
		Vec3f oc = ray->origin - center;
		double a = ray->direction.dotProduct(ray->direction);
		double b = 2.0 * oc.dotProduct(ray->direction);
		double c = oc.dotProduct(oc) - radius * radius;
		double discriminant = b * b - 4 * a * c;
		if (discriminant < 0)
		{
			h.point = Vec3f(-1, -1, -1);
			h.t = 0;
			h.normal = Vec3f(0, 0, 0);
		}
		else
		{
			// find closer
			// printf("hit shpere");
			float t_max = (-b - sqrt(discriminant)) / (2.0 * a);
			float t_min = (-b + sqrt(discriminant)) / (2.0 * a);
			h.t = std::min(t_max, t_min);
			h.point = ray->origin + (h.t) * (ray->direction);
			h.normal = (h.point - center).normalize();
		}

		return h;
	}

	Vec3f Sphere::getRayColor(Vec3f hit, Vec3f color, float exponent, Vec3f direction, float distance)
	{
		//printf("Sphere getRayColor");
		Vec2f texture(-1, -1);
		// Vec3f point = (hit - center).normalize();
		// if (material->isTexture)
		// {
		// 	float u = 0.5 + atan2(point[0], -point[1]) / (2 * M_PI);
		// 	float v = 0.5 - asin(point[2]) / M_PI;
		// 	uv = Vec2f(u, v);
		// }
		return material->getColour(color, exponent, direction, distance, texture);
		//return 0;
	}

} // namespace rt
