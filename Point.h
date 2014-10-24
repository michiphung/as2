#pragma once
#ifndef POINT_H
#define POINT_H

class Vector;

class Point {
public:
	float x, y, z;
    Point();
	Point(float x, float y, float z);
	Point operator+(Vector a);
	Point operator-(Vector a);
	Vector operator-(Point a);
	void print(); // for debugging purposes
};

#endif

