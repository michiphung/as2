#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H
#pragma once
#include <vector>
class GeometricPrimitive;
class Intersection;
class Ray;
class BRDF;
class LocalGeo;

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
#endif

