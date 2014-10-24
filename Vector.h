#ifndef VECTOR_H
#pragma once
#define VECTOR_H

class Point;

class Vector{
public:
	float x, y, z;
	Vector();
	Vector(float x, float y, float z);
	Vector operator+(Vector v);
	Vector operator-(Vector v);
	Point operator+(Point p);
	Point operator-(Point p);
	Vector operator*(float scalar);
	friend Vector operator*(float scalar, Vector &v);
	friend Vector crossProduct(Vector u, Vector v);
	float operator*(Vector v); // dot product
	void normalize();
	float length();
	void print(); // for debugging purposes

};

#endif