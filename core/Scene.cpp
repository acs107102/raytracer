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
			Vec3f ll, n_hat, v_hat, R, h_hat, diffuse;
			float distance, specular;

			if (hit.t > 0)
			{
				// closer
				if (hit.t < t)
				{
				//std::cout << "t: " << t << std::endl;
				//std::cout << "hit.t: " << hit.t << std:: endl;
					
					t = hit.t;
					Vec3f L;
					n_hat = hit.normal.normalize(); // n_hat
					v_hat = (ray->origin - (hit.point)).normalize();	// v_hat
					colorOfHit = shapes[i]->getAmbient();

					for (int m = 0; m < lightSources.size(); m++)
					{
					//std::cout << "m: " << m << std::endl;
					        L = lightSources[m]->getPosition();
						ll = (L - hit.point).normalize(); // l_hat
						h_hat = (ll + v_hat).normalize();	// h_hat
						distance = (L - hit.point).length();

						diffuse =(lightSources[m]->getColor()) * (std::max(0.f, (ll.dotProduct(n_hat))));
						specular = std::max(0.f, h_hat.dotProduct(n_hat));
						// specular = (std::max(0.f, N.dotProduct(H))) * (lightSources[0]->getIntensity());

						intensity = intensity + shapes[i]->getRayColor(hit.point, diffuse, specular, lightSources[m]->getIntensity(), distance);
					}
					
					

					if (ray->raytype == PRIMARY)
					{
						// reflect
						float kr = shapes[i]->getReflect();
						if (kr > 0)
						{
							//printf("REFLECTNESS %f \n",materialReflectness);
							R = ray->direction - (2 * ((ray->direction).dotProduct(n_hat)) * n_hat);
							// Vec3f noise = (1e-4 * hit.normal);
							Ray *rayMirror = new Ray();
							rayMirror->raytype = SECONDARY;
							rayMirror->origin = hit.point + 1e-4 * hit.normal;
							rayMirror->direction = R.normalize();
							// rayMirror->bounces = 0;
							Vec3f reflectedColor = rayCasting(rayMirror);
							// printf("REFLECTwed %f %f %f \n",reflectedColor[0],reflectedColor[1],reflectedColor[2]);

							intensity = intensity + kr * reflectedColor;
						}
					}
					//t = hit.t;

				colorOfHit = intensity;
				/*
				// obstructiob failed 
				Ray* rayLight = new Ray();
				rayLight->raytype = SHADOW;
				Vec3f noise = (1e-4 * hit.normal.normalize());
				rayLight->origin = hit.point + noise;
				rayLight->direction = (lightSources[0]->getPosition() - rayLight->origin).normalize();
				Vec3f shadowColor = rayCasting(rayLight);

				colorOfHit = (intensity * shadowColor);//colorOfHit + colorOfHit*(intensity.normalize());
				*/
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

} // namespace rt
