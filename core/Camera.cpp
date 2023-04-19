/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt
{

	Camera::~Camera(){};

	/**
	 * Factory function that returns camera subclass based on camera specifications
	 *
	 * @param cameraSpecs camera specifications json object
	 *
	 * @return camera subclass instance
	 *
	 */
	Camera *Camera::createCamera(Value &cameraSpecs)
	{

		// check if cameratype is defined

		if (!cameraSpecs.HasMember("type"))
		{
			std::cerr << "Camera type not specified" << std::endl;
			exit(-1);
		}

		std::string cameraType = cameraSpecs["type"].GetString();

		// return camera object based on camera specs
		if (cameraType.compare("pinhole") == 0)
		{
			return new Pinhole(cameraSpecs["width"].GetInt(),
							   cameraSpecs["height"].GetInt(),
							   cameraSpecs["fov"].GetInt(),
							   Vec3f(cameraSpecs["camPos"][0].GetFloat(), cameraSpecs["camPos"][1].GetFloat(), cameraSpecs["camPos"][2].GetFloat()),
							   Vec3f(cameraSpecs["camView"][0].GetFloat(), cameraSpecs["camView"][1].GetFloat(), cameraSpecs["camView"][2].GetFloat()),
							   Vec3f(cameraSpecs["camAxis"][0].GetFloat(), cameraSpecs["camAxis"][1].GetFloat(), cameraSpecs["camAxis"][2].GetFloat()));
		}
		else if (cameraType.compare("thinlens") == 0)
		{
			return new ThinLens();
		}

		return 0;
	}

} // namespace rt
