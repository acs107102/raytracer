/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"

namespace rt
{

	class ThinLens : public Camera
	{
	public:
		//
		// Constructors
		//
		ThinLens() : Camera(){};
		ThinLens(int width, int height, int fov, Vec3f camPos, Vec3f camView, Vec3f camAxis);

		//
		// Destructor
		//
		~ThinLens(){};

		//
		// print function (implementing abstract function of base class)
		//
		void printCamera();

		Ray *getRay(int x, int y);
	};

} // namespace rt

#endif /* THINLENS_H_ */
