#include "Ray.h"

Ray::Ray(){

}

Ray::Ray(Point pos, Vector dir, float t_min, float t_max)
{
	this->o = pos;
	this->d = dir;
	this->t_min = t_min;
	this->t_max = t_max;
}

