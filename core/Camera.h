/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt
{

	class Camera
	{
	public:
		//
		// Constructors
		//
		Camera(){};
		Camera(int height, int width, int fov, Vec3f camPos, Vec3f camView, Vec3f camAxis) : height(height), width(width), fov(fov), camPos(camPos), camView(camView), camAxis(camAxis){};

		//
		// Destructor
		//
		virtual ~Camera();

		//
		// factory function : returns camera instance dynamically based on camera specifications
		//
		static Camera *createCamera(Value &cameraSpecs);

		//
		// print function (to be implemented by the subclasses )
		//
		virtual void printCamera() = 0;

		//
		// other camera functions (to complete)
		//
		virtual Ray *getRay(int x, int y) = 0;

		//
		// Getters and Setters
		//
		int getHeight() const
		{
			return height;
		}

		void setHeight(int height)
		{
			this->height = height;
		}

		int getWidth() const
		{
			return width;
		}

		void setWidth(int width)
		{
			this->width = width;
		}

	protected:
		//
		// camera members
		//
		int height;
		int width;
		int fov; // field of view
		Vec3f camPos;
		Vec3f camView;
		Vec3f camAxis;
	};

} // namespace rt

#endif /* CAMERA_H_ */
