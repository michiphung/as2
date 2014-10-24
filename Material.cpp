#include "Material.h"
#include "BRDF.h"
#include "LocalGeo.h"

Material::Material()
{
}

Material::Material(BRDF brdf){
	this->constantBRDF = &brdf;
}

void Material::getBRDF(LocalGeo &local, BRDF *brdf){
	*brdf = *constantBRDF;
}
