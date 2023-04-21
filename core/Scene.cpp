/*
 * Scene.cpp
 *
 */
#include "Scene.h"

namespace rt
{

	/**
	 * Parses json scene object to generate scene to render
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::createScene(Value &scenespecs)
	{

		//----------parse json object to populate scene-----------
		Value &sceneShapes = scenespecs["shapes"];
		Value &sceneLightsources = scenespecs["lightsources"];

		// background color
		background = Vec3f(scenespecs["backgroundcolor"][0].GetFloat(), scenespecs["backgroundcolor"][1].GetFloat(), scenespecs["backgroundcolor"][2].GetFloat());

		// shapes
		std::cout << "'scene shapes size: " << sceneShapes.Size() << std::endl;
		for (SizeType i = 0; i < sceneShapes.Size(); i++)
		{
			printf("sceneShapes[%d] = %s\n", i, sceneShapes[i].GetObject()["type"].GetString());
			shapes.push_back(Shape::createShape(sceneShapes[i]));
		}

		// havn't implement
		// printf("making bvh shape\n");
		// bvh = Shape::bvhShape(shapes);

		// lightsources
		std::cout << "scene lightsources size: " << sceneLightsources.Size() << std::endl;
		for (SizeType i = 0; i < sceneLightsources.Size(); i++)
		{
			// std::cout << "here " << sceneLightsources[i].GetObject()["type"].GetString() << std::endl;
			printf("sceneLightsources[%d] = %s\n", i, sceneLightsources[i].GetObject()["type"].GetString());
			lightSources.push_back(LightSource::createLightSource(sceneLightsources[i]));
			// std::cout << "hi " << std::endl;
		}
	}

	Vec3f Scene::rayCasting(Ray *ray)
	{
		float t = INFINITY;
		Vec3f colorOfHit = background;
		
// std::cout << "shape: " << shapes.size() << std::endl;
		for (int i = 0; i < shapes.size(); i++)
		{
			Hit hit = shapes[i]->intersect(ray);
			Vec3f intensity(0, 0, 0);
			Vec3f ll, N, V, R, H, diffuse;
			float distance, specular;

			if (hit.t != 0)
			{
				// closer
				if (hit.t < t)
				{
				//std::cout << "t: " << t << std::endl;
				//std::cout << "hit.t: " << hit.t << std:: endl;
					colorOfHit = shapes[i]->getAmbient();
					// printf("color %f %f %f \n",colorOfHit[0],colorOfHit[1],colorOfHit[2]);
					Vec3f L = lightSources[0]->getPosition();
					N = hit.normal.normalize(); // n_hat
					V = (ray->origin - (hit.point)).normalize();	// v_hat

					//for (int m = 0; m < lightSources.size(); m++)
					//{
					//std::cout << "m: " << m << std::endl;
						ll = (L - (hit.point)).normalize(); // l_hat
						H = (ll + V).normalize();	// h_hat
						distance = (L - (hit.point)).length();

						diffuse = (std::max(0.f, (N.dotProduct(ll)))) * (lightSources[0]->getColor());
						specular = std::max(0.f, N.dotProduct(H));

						intensity = intensity + shapes[i]->getRayColor(hit.point, diffuse, specular, lightSources[0]->getIntensity(), distance);
					//}
					
					

					if (ray->raytype == PRIMARY)
					{
						// reflect
						float materialReflectness = shapes[i]->getReflect();
						if (materialReflectness > 0)
						{
							//printf("REFLECTNESS %f \n",materialReflectness);
							R = ray->direction - (2 * ((ray->direction).dotProduct(N)) * N);
							// Vec3f noise = (1e-4 * hit.normal);
							Ray *rayMirror = new Ray();
							rayMirror->raytype = SECONDARY;
							rayMirror->origin = hit.point + 1e-4 * hit.normal;
							rayMirror->direction = -R.normalize();
							// rayMirror->bounces = 0;
							Vec3f reflectedColor = materialReflectness * rayCasting(rayMirror);
							// printf("REFLECTwed %f %f %f \n",reflectedColor[0],reflectedColor[1],reflectedColor[2]);

							intensity = intensity + reflectedColor;
						}
					}
				t = hit.t;

				colorOfHit = intensity;
				}
				
			}
			
		}
		
		return colorOfHit;
	}

	float Scene::getClosestIntersectionT(Ray *ray)
	{
		float closestT = INFINITY;
		bool hasMissed = true;

		// for now assuming 1 lightsource
		for (int i = 0; i < shapes.size(); i++)
		{
			Hit h = shapes[i]->intersect(ray);
			if (h.t > 0 && h.t < closestT)
			{
				closestT = h.t;
				hasMissed = false;
			}
		}

		return closestT;
	}

	// Vec3f Scene::rayCasting(Ray *ray)
	// {
	// 	float t = INFINITY;
	// 	Vec3f colorOfHit = background;

	// 	for (int i = 0; i < shapes.size(); i++)
	// 	{
	// 		Hit hit = shapes[i]->intersect(ray);
	// 		Vec3f intensity(0, 0, 0);
	// 		Vec3f L_m, N, V, R, H, diffuse;
	// 		float dist, specular;

	// 		if (hit.t > 0)
	// 		{
	// 			// if it hits the object and if it is closer hit then previous one
	// 			if (hit.t < t)
	// 			{
	// 				colorOfHit = hit.shape->Ambient();
	// 				t = hit.t;
	// 				N = hit.normal.normalize();
	// 				V = (ray->origin - (hit.point)).normalize();

	// 				for (int m = 0; m < lightSources.size(); m++)
	// 				{
	// 					L_m = (lightSources[m]->getPosition() - (hit.point)).normalize();
	// 					H = (L_m + V) /= ((L_m + V).length());
	// 					dist = (lightSources[m]->getPosition() - (hit.point)).length();
	// 					diffuse = (std::max(0.f, (N.dotProduct(L_m)))) * (lightSources[m]->getColor());
	// 					specular = std::max(0.f, N.dotProduct(H));
	// 					intensity = intensity + hit.point.getRayColor(hit.point, diffuse); //, specular, lightSources[m]->getIntensity(), dist);
	// 				}

	// 				// if (ray->raytype == PRIMARY)
	// 				// {
	// 				// 	// CHECK FOR REFLECTIONS IF MATERIAL IS REFLECTIVE
	// 				// 	float materialReflectness = hit.dest->getReflectness();
	// 				// 	if (materialReflectness > 0)
	// 				// 	{
	// 				// 		R = ray->direction - (2 * ((ray->direction).dotProduct(N)) * N);
	// 				// 		Vec3f noise = (1e-4 * hit.normal);
	// 				// 		Ray *rayMirror = new Ray();
	// 				// 		rayMirror->raytype = SECONDARY;
	// 				// 		rayMirror->origin = hit.point + noise;
	// 				// 		rayMirror->direction = R.normalize();
	// 				// 		Vec3f reflectedColor = materialReflectness * castRay(rayMirror);
	// 				// 		intensity = intensity + reflectedColor;
	// 				// 	}
	// 				// }

	// 				// CHECK FOR OBSTRUCTIONS
	// 				// Ray *rayLight = new Ray();
	// 				// int lightPositionSampleCount = 100;
	// 				// float shadowStrength = 0;
	// 				// Vec3f noise = (1e-3 * hit.normal.normalize());
	// 				// rayLight->origin = hit.point + noise;

	// 				// for (int n = 0; n < lightPositionSampleCount; n++)
	// 				// {
	// 				// 	Vec3f lightPosSample = lightSources[0]->getPosition();
	// 				// 	rayLight->direction = (lightPosSample - hit.point).normalize();
	// 				// 	float lightDistance = (lightPosSample - hit.point).length();
	// 				// 	if (getClosestIntersectionT(rayLight) >= lightDistance)
	// 				// 	{
	// 				// 		shadowStrength++;
	// 				// 	}
	// 				// }
	// 				// shadowStrength = shadowStrength / lightPositionSampleCount;
	// 				// colorOfHit = (intensity * shadowStrength);
	// 			}
	// 		}
	// 	}
	// 	return colorOfHit;
	// }

} // namespace rt
