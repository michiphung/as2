#pragma once
#include "Ray.h"
#include "Color.h"
#include "Intersection.h"
#include "Light.h"
#include "AggregatePrimitive.h"

class RayTracer
{
public:
	int depth = 5;
	AggregatePrimitive ag;
	vector<Light*> lights;
	RayTracer(); 
	RayTracer(AggregatePrimitive &ag, vector<Light*> lights, int depth);
	void trace(Ray &ray, int depth, Color* color);
};

