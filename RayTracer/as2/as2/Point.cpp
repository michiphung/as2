#include "stdafx.h"
#include "Point.h"
#include <math.h>
#include "Vector.h"
#include <iostream>

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

Point Point::operator+(Vector a) {
    return Point(x + a.x, y + a.y, z + a.z);
}

Point Point::operator-(Vector a) {
    return Point(x - a.x, y - a.y, z - a.z);
}

Vector Point::operator-(Point a) {
    return Vector(x - a.x, y -a.y, z - a.z);
}

void Point::print(){ 
	std::cout << "[" << x << "," << y << "," << z << "]\n";
}

