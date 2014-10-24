#pragma once
#include "Transformation.h"
#include "Material.h"
#include "Shape.h"

#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H
class Intersection;

class GeometricPrimitive
{
public:
	Transformation objToWorld, worldToObj;
	Shape* shape;
	Material* mat;
	GeometricPrimitive();
	GeometricPrimitive(Transformation objToWorld, Transformation worldToObj, Shape *shape, Material* mat);
	bool intersect(Ray &ray, float* thit, Intersection* in);
	bool intersectP(Ray &ray);
	void getBRDF(LocalGeo& local, BRDF*brdf);
};

#endif
