#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#pragma once
#include "Matrix.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Vector.h"

class Ray;
class Transformation
{
public:
	Matrix m;
	Matrix minv;
	Matrix minvt;
	Transformation();
	void rotation(float x, float y, float z, float degrees);
	void translation(float x, float y, float z);
	void scale(float x, float y, float z);
	Vector operator*(Vector v);
	Point operator*(Point p);
	Ray operator*(Ray ray);
	LocalGeo operator*(LocalGeo localGeo);
	Transformation operator*(Transformation t);
	void print(); // for debugging purposes;
};

const Transformation IDENTITY = Transformation();

#endif