#include "LocalGeo.h"

LocalGeo::LocalGeo(){

}

LocalGeo::LocalGeo(Point p, Vector normal){
	this->pos = p;
	this->normal = normal;
}