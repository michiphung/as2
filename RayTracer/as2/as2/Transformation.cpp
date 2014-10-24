#include "stdafx.h"
#include "Transformation.h"
#include <iostream>


Transformation::Transformation()
{
	m = Matrix();
	minv = Matrix();
	minvt = Matrix();
}

void Transformation::rotation(float x, float y, float z, float degrees){
	m.rotation(x, y, z, degrees);
	minv.rotation(x, y, z, -degrees);
	minvt.rotation(x, y, z, -degrees);
	minvt.transpose();
}

void Transformation::translation(float x, float y, float z){
	m.translation(x, y, z);
	minv.translation(-x, -y, -z);
	minvt.translation(-x, -y, -z);
	minvt.transpose();
}

void Transformation::scale(float x, float y, float z){
	m.scale(x, y, z);
	minv.scale(1.0 / x, 1.0 / y, 1.0 / z);
	minvt.scale(1.0 / x, 1.0 / y, 1.0 / z);
	minvt.transpose();
}

Vector Transformation::operator*(Vector v){
	float x = m.mat[0][0] * v.x + m.mat[0][1] * v.y + m.mat[0][2] * v.z + m.mat[0][3];
	float y = m.mat[1][0] * v.x + m.mat[1][1] * v.y + m.mat[1][2] * v.z + m.mat[1][3];
	float z = m.mat[2][0] * v.x + m.mat[2][1] * v.y + m.mat[2][2] * v.z + m.mat[2][3];
	return Vector(x, y, z);
}

Transformation Transformation::operator*(Transformation t){
	Transformation result = Transformation();
	for (int i = 0; i <4; i++) {
		for (int j = 0; j <4; j++) {
			result.m.mat[i][j] = m.mat[i][0] * t.m.mat[0][j] + m.mat[i][1] * t.m.mat[1][j] + m.mat[i][2] * t.m.mat[2][j] + m.mat[i][3] * t.m.mat[3][j];
		}
	}
	for (int i = 0; i <4; i++) {
		for (int j = 0; j <4; j++) {
			result.minv.mat[i][j] = t.minv.mat[i][0] * minv.mat[0][j] + t.minv.mat[i][1] * minv.mat[1][j] + t.minv.mat[i][2] * minv.mat[2][j] + t.minv.mat[i][3] * minv.mat[3][j];
		}
	}
	for (int i = 0; i <4; i++) {
		for (int j = 0; j <4; j++) {
			result.minvt.mat[i][j] = t.minv.mat[i][j];
			}
	}
	result.minvt.transpose();
	return result;
}



Point Transformation::operator*(Point p){
	float x = m.mat[0][0] * p.x + m.mat[0][1] * p.y + m.mat[0][2] * p.z + m.mat[0][3];
	float y = m.mat[1][0] * p.x + m.mat[1][1] * p.y + m.mat[1][2] * p.z + m.mat[1][3];
	float z = m.mat[2][0] * p.x + m.mat[2][1] * p.y + m.mat[2][2] * p.z + m.mat[2][3];
	return Point(x, y, z);
}

Ray Transformation::operator*(Ray ray){
	Vector v = ray.d;
	float x = m.mat[0][0] * v.x + m.mat[0][1] * v.y + m.mat[0][2] * v.z;
	float y = m.mat[1][0] * v.x + m.mat[1][1] * v.y + m.mat[1][2] * v.z;
	float z = m.mat[2][0] * v.x + m.mat[2][1] * v.y + m.mat[2][2] * v.z;
	return Ray(operator*(ray.o), Vector(x, y, z), 0, 0);
}

LocalGeo Transformation::operator*(LocalGeo localGeo){
	Vector v = localGeo.normal;
	float x = minvt.mat[0][0] * v.x + minvt.mat[0][1] * v.y + m.mat[0][2] * v.z;
	float y = minvt.mat[1][0] * v.x + minvt.mat[1][1] * v.y + m.mat[1][2] * v.z;
	float z = minvt.mat[2][0] * v.x + minvt.mat[2][1] * v.y + m.mat[2][2] * v.z;
	v = Vector(x, y, z);
	v.normalize();
	return LocalGeo(operator*(localGeo.pos), v);
}

void Transformation::print(){ // for debugging purposes
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			std::cout << m.mat[i][j] << " ";
		}
		std::cout << "\n";
	}
}
