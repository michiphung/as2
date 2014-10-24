#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "LocalGeo.h"
#include <math.h>

class Shape
{
public:
	virtual bool intersect(Ray &ray, float* thit, LocalGeo* local) = 0;
	virtual bool intersectP(Ray &ray) = 0;
};

class Triangle: public Shape{
public:
	Point v0;
	Point v1;
	Point v2;
	Triangle(Point v0, Point v1, Point v2);
	bool intersect(Ray &ray, float* thit, LocalGeo* local);
	bool intersectP(Ray &ray);
};

class Sphere : public Shape{
public:
	Point center;
	float radius;
	Sphere();
	Sphere(Point center, float radius);
	bool intersect(Ray &ray, float* thit, LocalGeo* local);
    bool intersectP(Ray &ray);
};

// Used for Phong shading, unlike Triangle, which uses flat shading.
class SmoothTriangle : public Shape{
public:
	Point v0;
	Point v1;
	Point v2;
	Vector n0;
	Vector n1;
	Vector n2;
	SmoothTriangle(Point v0, Point v1, Point v2, Vector n0, Vector n1, Vector n2);
	bool intersect(Ray &ray, float* thit, LocalGeo* local);
	bool intersectP(Ray &ray);
};

