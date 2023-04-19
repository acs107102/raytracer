/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt
{

	/*
	 * Ray structure definition
	 */
	enum RayType
	{
		PRIMARY,
		SECONDARY,
		SHADOW
	};

	struct Ray
	{

		RayType raytype;

		//----------Ray variables to be filled------
		Vec3f origin;
		Vec3f direction;
	};

	class Shape;

	struct Hit
	{

		Vec3f point; // point where ray hits a shape
		//----------Hit variables to be filled------
		float t; // at(t) = origin + t * direction
		Vec3f normal;
		int bounces;  //
		Shape *shape; //
	};

}

#endif /* CORE_RAYHITSTRUCTS_H_ */
