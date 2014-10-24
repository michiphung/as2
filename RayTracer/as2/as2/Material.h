#pragma once
#include "BRDF.h"
#include "LocalGeo.h"
class Material
{
public:
	BRDF constantBRDF;
	void getBRDF(LocalGeo &local, BRDF *brdf);
	Material();
	Material(BRDF brdf);
};

