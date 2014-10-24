#pragma once
#include "Point.h"
#include "Vector.h"
class LocalGeo
{
public:
	Point pos;
	Vector normal;
	LocalGeo();
	LocalGeo(Point p, Vector normal);
};

