#include "Light.h"
#include "Color.h"
#include "Ray.h"
#include "LocalGeo.h"
#include <math.h>
#include <iostream>
#include "Vector.h"

Light::Light(bool type, float x, float y, float z, float r, float g, float b)
{
	isPoint = type;
	pos = Point(x, y, z);
	color = Color(r, g, b);
}

void Light::generateLightRay(LocalGeo &local, Ray *lray, Color *lcolor){
	Point o = local.pos;

	Vector d;
	if (isPoint)
		d = this->pos - o;
	else
		d = Vector(-pos.x, -pos.y, -pos.z);
	*lray = Ray(&o, &d, 0, INFINITY);
	*lcolor = this->color;
}

void Light::print(){
	color.print();
}