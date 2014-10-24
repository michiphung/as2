#include "RayTracer.h"
#include "Ray.h"
#include "Light.h"
#include "Vector.h"
#include "Intersection.h"
#include "AggregatePrimitive.h"

RayTracer::RayTracer(AggregatePrimitive &ag, vector<Light*> lights, int depth)
{
	this->ag = &ag;
	this->lights = lights;
	this->depth = depth;
}

void RayTracer::trace(Ray &ray, int depth, Color* color){
	if (depth >= this->depth) {
		*color = BLACK;
		return;
	}
	float thit = INFINITY;
	Intersection in;
	if (!ag->intersect(ray, &thit, &in)){
		*color = BLACK;
		return;
	}
	BRDF brdf;
	in.primitive->getBRDF(in.localGeo, &brdf);
	for (int i = 0; lights.size(); i++){
		Ray lray;
		Color lcolor;
		lights[i]->generateLightRay(in.localGeo, &lray, &lcolor);

		if (!ag->intersectP(lray)){
			Color ret = BLACK;
			Vector l = *lray.d;
			l.normalize();
			Vector n = in.localGeo.normal;

			ret = brdf.kd * (l * n);
		}
	}
}