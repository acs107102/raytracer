/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>

#include "ThinLens.h"

namespace rt
{

	//
	// ThinLens constructor (example)
	//
	ThinLens::ThinLens(int width, int height, int fov, Vec3f camPos, Vec3f camView, Vec3f camAxis) : Camera(width, height, fov, camPos, camView, camAxis)
	{

		// to fill
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void ThinLens::printCamera()
	{
		printf("I am a thin lens camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	Ray *ThinLens::getRay(int X, int Y) { return 0; }

} // namespace rt
