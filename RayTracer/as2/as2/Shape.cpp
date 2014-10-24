#include "stdafx.h"
#include "Shape.h"
#include "Point.h"
#include "Vector.h"
#include "LocalGeo.h"
#include <iostream>
using namespace std;

const float epsilon;

Triangle::Triangle(Point v0, Point v1, Point v2){
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}

bool Triangle::intersect(Ray &ray, float* thit, LocalGeo* local){
	// reference: http://people.cs.clemson.edu/~dhouse/courses/405/papers/raytriangle-moeller02.pdf
	float e = 0.00001;
	Vector e1 = v1 - v0;
	Vector e2 = v2 - v0;
	Vector p = crossProduct(ray.d, e2);
	float a = e1 * p;
	if (a > -e && a < e)
		return false;
	float f = 1.0 / a;
	Vector s = ray.o - v0;
	float u = f * (s * p);
	if (u < 0.0 || u > 1.0)
		return false;
	Vector q = crossProduct(s, e1);
	float v = f * (ray.d * q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	float t = f * (e2*q);
	if (t < epsilon){
		return false;
	}
	*thit = t;
	Point pos = ray.o + t*ray.d;
	Vector normal = crossProduct(this->v2 - this->v0, this->v2 - this->v1);
	normal.normalize();
	*local = LocalGeo(pos, normal);
	return true;
}

bool Triangle::intersectP(Ray &ray){
	// reference: http://people.cs.clemson.edu/~dhouse/courses/405/papers/raytriangle-moeller02.pdf
	float e = 0.00001;
	Vector e1 = v1 - v0;
	Vector e2 = v2 - v0;
	Vector p = crossProduct(ray.d, e2);
	float a = e1 * p;
	if (a > -e && a < e)
		return false;
	float f = 1.0 / a;
	Vector s = ray.o - v0;
	float u = f * (s * p);
	if (u < 0.0 || u > 1.0)
		return false;
	Vector q = crossProduct(s, e1);
	float v = f * (ray.d * q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	float t = f * (e2*q);
	if (t < epsilon){
		return false;
	}
	return true;
}

Sphere::Sphere(){

}
Sphere::Sphere(Point center, float radius){
	this->center = center;
	this->radius = radius;
}

bool Sphere::intersect(Ray &ray, float* thit, LocalGeo* local){
	// see http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection for relevant formulae
	Point o = ray.o;
	Vector d = ray.d;
	Point c = center;
	float r = radius;
	float A = d * d;
	float B = 2 * (o - c) * d;
	float C = (o - c) * (o - c) - (r * r);
	float discriminant = B*B - 4.0 * A * C;
	if (discriminant < 0)
		return false;
	float sqrt_disc = sqrt(discriminant);
	float q = (-B - sqrt_disc) / 2.0;
	float t0 = q / A;
	q = (-B + sqrt_disc) / 2.0;
	float t1 = q / A;

	if (t1 < 0)
		return false;

	if (t0 < 0){
		if (t1 < epsilon){
			return false;
		}
		*thit = t1;
		Point p = o + t1*d;
		Vector normal = p - center;
		normal.normalize();
		*local = LocalGeo(p, normal);
		return true;
	}
	if (t0 < epsilon){
		return false;
	}
	*thit = t0;
	Point p = o + t0*d;
	Vector normal = p - center;
	normal.normalize();
	*local = LocalGeo(p, normal);
	return true;
}

bool Sphere::intersectP(Ray &ray){
	// see http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection for relevant formulae
	Point o = ray.o;
	Vector d = ray.d;
	Point c = center;
	float r = radius;
	float A = d * d;
	float B = 2 * (o - c) * d;
	float C = (o - c) * (o - c) - (r * r);
	float discriminant = B*B - 4.0 * A * C;
	if (discriminant < 0)
		return false;
	float sqrt_disc = sqrt(discriminant);
	float q = (-B - sqrt_disc) / 2.0;
	float t0 = q / A;
	q = (-B + sqrt_disc) / 2.0;
	float t1 = q / A;

	if (t1 < 0)
		return false;

	if (t0 < 0){
		if (t1 < epsilon){
			return false;
		}
		return true;
	}
	if (t0 < epsilon){
		return false;
	}
	return true;
}

SmoothTriangle::SmoothTriangle(Point v0, Point v1, Point v2, Vector n0, Vector n1, Vector n2){
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
	this->n0 = n0;
	this->n1 = n1;
	this->n2 = n2;
}

bool SmoothTriangle::intersect(Ray &ray, float* thit, LocalGeo* local){
	// reference: http://people.cs.clemson.edu/~dhouse/courses/405/papers/raytriangle-moeller02.pdf
	float e = 0.00001;
	Vector e1 = v1 - v0;
	Vector e2 = v2 - v0;
	Vector p = crossProduct(ray.d, e2);
	float a = e1 * p;
	if (a > -e && a < e)
		return false;
	float f = 1.0 / a;
	Vector s = ray.o - v0;
	float u = f * (s * p);
	if (u < 0.0 || u > 1.0)
		return false;
	Vector q = crossProduct(s, e1);
	float v = f * (ray.d * q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	float t = f * (e2*q);
	if (t < epsilon){
		return false;
	}
	*thit = t;
	Vector normal = Vector(0, 0, 0);
	normal = (1.0 - (u + v)) *  n0 + u * n1 + v * n2;
	// cout << normal.x << " " << normal.y << " " << normal.z << "\n";
	Point pos = ray.o + t*ray.d;
	normal.normalize();
	*local = LocalGeo(pos, normal);
	return true;
}

bool SmoothTriangle::intersectP(Ray &ray){
	float e = 0.01;
	Vector e1 = v1 - v0;
	Vector e2 = v2 - v0;
	Vector p = crossProduct(ray.d, e2);
	float a = e1 * p;
	if (a > -e && a < e)
		return false;
	float f = 1.0 / a;
	Vector s = ray.o - v0;
	float u = f * (s * p);
	if (u < 0.0 || u > 1.0)
		return false;
	Vector q = crossProduct(s, e1);
	float v = f * (ray.d * q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	float t = f * (e2*q);
	if (t < epsilon){
		return false;
	}
	return true;
}

