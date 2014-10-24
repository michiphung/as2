#pragma once
#include <vector>
#include "GeometricPrimitive.h"


using namespace std;

class AggregatePrimitive
{
public:
	vector<GeometricPrimitive*> list;
	AggregatePrimitive();
	AggregatePrimitive(vector<GeometricPrimitive*> list);
	bool intersect(Ray &ray, float *thit, Intersection *in);
	bool intersectP(Ray &ray);
	void getBRDF(LocalGeo &local, BRDF* brdf);
};

