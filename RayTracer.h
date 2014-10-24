#ifndef RAYTRACER_H
#define RAYTRACER_H
#pragma once
#include <vector>
class Vector;
class Point;
class Light;
class Ray;
class AggregatePrimitive;
class Color;
using namespace std;


class RayTracer
{
public:
	int depth = 5;
	AggregatePrimitive* ag;
	vector<Light*> lights;
	RayTracer(); 
	RayTracer(AggregatePrimitive &ag, vector<Light*> lights, int depth);
	void trace(Ray &ray, int depth, Color* color);
};
#endif

