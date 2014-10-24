#pragma once
#include "Color.h"
class BRDF
{
public:
	Color kd, ks, ka, kr;
	float p;
	BRDF();
	BRDF(Color kd, Color ks, Color ka, Color kr, float p);
};

