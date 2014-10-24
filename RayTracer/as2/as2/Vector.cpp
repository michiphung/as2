#include "stdafx.h"
#include <math.h>
#include "Vector.h"
#include "Point.h"
#include <iostream>

float sqr(float x) { return x*x; }

Vector::Vector(){
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float a, float b, float c){
    x = a;
    y = b;
    z = c;
}

Vector Vector::operator+(Vector v){
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v){
    return Vector(x - v.x, y - v.y, z - v.z);
}

Point Vector::operator+(Point p){
	return Point(x + p.x, y + p.y, z + p.z);
}

Point Vector::operator-(Point p){
    return Point(x - p.x, y - p.y, z - p.z);
}

Vector Vector::operator*(float scalar){
    return Vector(scalar * x, scalar * y, scalar * z);
}

Vector operator*(float scalar, Vector &v){
	return v.operator*(scalar);
}

Vector crossProduct(Vector a, Vector b){
	return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
float Vector::operator*(Vector v){ // dot product
	return (x * v.x) + (y * v.y) + (z * v.z);
}

void Vector::normalize(){
    if (x == 0 && y == 0 && z == 0){
        return;
    }
    float total = 0;
    total = sqrt(sqr(x) + sqr(y) + sqr(z));
    x /= total;
    y /= total;
    z /= total;
}

float Vector::length(){
	return sqrt(sqr(x) + sqr(y) + sqr(z));
}

void Vector::print(){
	std::cout << "[" << x << "," << y << "," << z << "]\n";
}
