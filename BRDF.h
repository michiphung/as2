#pragma once
#ifndef BRDF_H
#define BRDF_H
#include "Color.h"
class Color;
class BRDF
{
public:
	Color kd, ks, ka, kr;
	float p;
	BRDF();
	BRDF(Color kd, Color ks, Color ka, Color kr, float p);
};
#endif
