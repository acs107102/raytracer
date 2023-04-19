/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace rt
{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f camPos, Vec3f camView, Vec3f camAxis) : Camera(width, height, fov, camPos, camView, camAxis)
	{

		// to fill
		// camera axis vector
		Vec3f front = camView.normalize();
		Vec3f side = (front).crossProduct(camAxis.normalize()).normalize();
		Vec3f up = side.crossProduct(front).normalize();

		camWorld = Matrix44f(side.x, side.y, side.z, camPos.x,
							 up.x, up.y, up.z, camPos.y,
							 front.x, front.y, front.z, camPos.z,
							 0, 0, 0, 1);
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera()
	{
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	Ray *Pinhole::getRay(int X, int Y)
	{
		double theta = fov * M_PI / 180;
		float halfHeight = static_cast<float>(tan(theta / 2));

		float normX = (X + 0.5) / (float)width;
		float normY = (Y + 0.5) / (float)height;

		float screenX = (2 * normX - 1) * halfHeight;
		float screenY = (1 - 2 * normY) * halfHeight;

		Vec3f direction = (Vec3f(screenX, screenY, 1)).normalize();
		Vec3f worldDirection;
		camWorld.multDirMatrix(direction, worldDirection);
		worldDirection = worldDirection.normalize();
		Ray *ray = new Ray();
		ray->raytype = PRIMARY;
		ray->origin = camPos;
		ray->direction = worldDirection;
		return ray;
	}

} // namespace rt
