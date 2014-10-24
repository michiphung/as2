#include "Ray.h"
#include "Vector.h"
#include "Point.h"

Ray::Ray(){
    /*this->o = new Point(0,0,0);
    this->d = new Vector(0,0,0);
    this->t_min = 0;
    this->t_max = 0;
     */
}

Ray::Ray(Point* pos, Vector* dir, float t_min, float t_max)
{
	this->o = pos;
	this->d = dir;
	this->t_min = t_min;
	this->t_max = t_max;
}

Vector Ray::getDirection()
{
    return *this->d;
}