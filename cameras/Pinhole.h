/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "core/RayHitStructs.h"

namespace rt
{

	class Pinhole : public Camera
	{
	public:
		//
		// Constructors
		//
		Pinhole();
		Pinhole(int width, int height, int fov, Vec3f camPos, Vec3f camView, Vec3f camAxis);

		//
		// Destructor
		//
		~Pinhole(){};

		//
		// print function (implementing abstract function of base class)
		//
		void printCamera();

		Ray *getRay(int x, int y);

		Matrix44f camWorld;
	};

} // namespace rt

#endif /* PINHOLE_H_ */
