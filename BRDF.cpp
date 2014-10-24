#include "BRDF.h"
#include "Color.h"


BRDF::BRDF()
{
	p = 1;
	kd = BLACK;
	ks = BLACK;
	ka = BLACK;
	kr = BLACK;
}

BRDF::BRDF(Color kd, Color ks, Color ka, Color kr, float p = 1){
	this->p = p;
	this->kd = kd;
	this->ks = ks;
	this->ka = ka;
	this->kr = kr;
}
