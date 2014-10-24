#ifndef LOCALGEO_H
#define LOCALGEO_H

#pragma once

class Point;
class Vector;
class LocalGeo
{
public:
	Point* pos;
	Vector* normal;
	LocalGeo();
	LocalGeo(Point p, Vector normal);
};
#endif
