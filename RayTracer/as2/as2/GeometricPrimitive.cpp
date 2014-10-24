#include "stdafx.h"
#include "GeometricPrimitive.h"
#include "Intersection.h"
#include "Shape.h"
#include <iostream>

GeometricPrimitive::GeometricPrimitive()
{
}

GeometricPrimitive::GeometricPrimitive(Transformation objToWorld, Transformation worldToObj, Shape *shape, Material* mat){
	this->objToWorld = objToWorld;
	this->worldToObj = worldToObj;
	this->shape = shape;
	this->mat = mat;
}

bool GeometricPrimitive::intersect(Ray &ray, float *thit, Intersection *in){
	Ray oray = worldToObj * ray;
	LocalGeo olocal = LocalGeo();
	if (!shape->intersect(oray, thit, &olocal)) return false;
	in->primitive = this;
	in->localGeo = objToWorld*olocal;
	return true;
}

bool GeometricPrimitive::intersectP(Ray &ray) {
	Ray oray = worldToObj*ray;
	return shape->intersectP(oray);
}

void GeometricPrimitive::getBRDF(LocalGeo &local, BRDF *brdf){
	mat->getBRDF(local, brdf);
}


