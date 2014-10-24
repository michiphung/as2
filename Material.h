#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once

class BRDF;
class LocalGeo;

class Material
{
public:
	BRDF* constantBRDF;
	void getBRDF(LocalGeo &local, BRDF *brdf);
	Material();
	Material(BRDF brdf);
};

#endif

