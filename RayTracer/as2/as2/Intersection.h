#pragma once
#include "LocalGeo.h"
#include "GeometricPrimitive.h"

#ifndef INTERSECTION_H
#define INTERSECTION_H

class Intersection
{
public:
	LocalGeo localGeo;
	GeometricPrimitive *primitive;
	Intersection();
};

#endif