/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

namespace rt
{
	int RayTracer::width = 0;
	int RayTracer::height = 0;

	/**
	 * Performs ray tracing to render a photorealistic scene
	 *
	 * @param camera the camera viewing the scene
	 * @param scene the scene to render, including objects and lightsources
	 * @param nbounces the number of bounces to consider for raytracing  (光線追蹤的深度)
	 *
	 * @return a pixel buffer containing pixel values in linear RGB format
	 */
	Vec3f *RayTracer::render(Camera *camera, Scene *scene, int nbounces)
	{
		RayTracer::width = camera->getWidth();
		RayTracer::height = camera->getHeight();
		// Vec3f *pixelbuffer = new Vec3f[width * height];
		Vec3f *pixelbuffer = new Vec3f[camera->getWidth() * camera->getHeight()];

		//----------main rendering function to be filled------
		printf("pixelbuffer: ", pixelbuffer);
		printf("camera: ", camera->getWidth());
		int index = 0;
		for (int i = 0; i < RayTracer::width; i++)
		{
			for (int j = 0; j < RayTracer::height; j++)
			{
				// create ray
				Ray *ray = camera->getRay(j, i);
				// ray in scene
				Vec3f color = scene->rayCasting(ray);
				// cross in the scene
				index++;
				pixelbuffer[index] = color;
			}
		}

		return pixelbuffer;
	}

	/**
	 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
	 *
	 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
	 *
	 * @return the tonemapped image
	 */
	Vec3f *RayTracer::tonemap(Vec3f *pixelbuffer)
	{

		//---------tonemapping function to be filled--------
		printf("tone map : pixelbuffer size ", RayTracer::width * RayTracer::height);
		float max = 0;
		for (int i = 0; i < RayTracer::width * RayTracer::height; ++i)
		{
			// avoid too bright
			if (pixelbuffer[i][0] > max)
				max = pixelbuffer[i][0];
			if (pixelbuffer[i][1] > max)
				max = pixelbuffer[i][1];
			if (pixelbuffer[i][2] > max)
				max = pixelbuffer[i][2];
		}

		// normalize and times 256
		for (int i = 0; i < RayTracer::width * RayTracer::height; ++i)
		{
			pixelbuffer[i] = (pixelbuffer[i] /= max) * 256;
		}

		return pixelbuffer;
	}

} // namespace rt
