#include "stdafx.h"
#include "Matrix.h"
#include <math.h>
#include <iostream>

const double PI = 4.0 * atan(1.0);

Matrix::Matrix() // loads the identity matrix by default
{
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void Matrix::rotation(float x, float y, float z, float degrees){
	float theta = degrees / 180.0 * PI;
	// Implemented as in OpenGL
	// http://www.opengl.org/documentation/specs/version1.1/glspec1.1/node25.html
	if (x == 0 && y == 0 && z == 0){
		return;
	}
	Vector v = Vector(x, y, z);
	v.normalize();
	float S[3][3];

	// First row = [0, -z, y]
	S[0][0] = 0;
	S[0][1] = -v.z;
	S[0][2] = v.y;

	// Second row = [z, 0, -x];
	S[1][0] = v.z;
	S[1][1] = 0;
	S[1][2] = -v.x;

	// Third row = [-y, x, 0];
	S[2][0] = -v.y;
	S[2][1] = v.x;
	S[2][2] = 0;
	float U[3][3] = { { v.x * v.x, v.x * v.y, v.x * v.z },
					  { v.y * v.x, v.y * v.y, v.y * v.z },
					  { v.z * v.x, v.z * v.y, v.z * v.z } };
	U[0][0] = v.x * v.x;
	U[0][1] = v.x * v.y;
	U[0][2] = v.x * v.z;

	U[1][0] = v.y * v.x;
	U[1][1] = v.y * v.y;
	U[1][2] = v.y * v.z;

	U[2][0] = v.z * v.x;
	U[2][1] = v.z * v.y;
	U[2][2] = v.z * v.z;

	float ct = cos(theta);
	float st = sin(theta);
	mat[0][0] = U[0][0] + ct * (1 - U[0][0]);
	mat[0][1] = U[0][1] + ct * -U[0][1] + st * S[0][1];
	mat[0][2] = U[0][2] + ct * -U[0][2] + st * S[0][2];
	mat[0][3] = 0;
	mat[1][0] = U[1][0] + ct * -U[1][0] + st * S[1][0];
	mat[1][1] = U[1][1] + ct * (1 - U[1][1]);
	mat[1][2] = U[1][2] + ct * -U[1][2] + st * S[1][2];
	mat[1][3] = 0;
	mat[2][0] = U[2][0] + ct * -U[2][0] + st * S[2][0];
	mat[2][1] = U[2][1] + ct * -U[2][1] + st * S[2][1];
	mat[2][2] = U[2][2] + (ct * (1 - U[2][2]));
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void Matrix::translation(float x, float y, float z){
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = x;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = y;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = z;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void Matrix::scale(float x, float y, float z){
	mat[0][0] = x;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = y;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = z;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void Matrix::transpose(){
	float tmp;
	tmp = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp;

	tmp = mat[0][2];
	mat[0][2] = mat[2][0];
	mat[2][0] = tmp;

	tmp = mat[0][3];
	mat[0][3] = mat[3][0];
	mat[3][0] = tmp;

	tmp = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = tmp;

	tmp = mat[1][3];
	mat[1][3] = mat[3][1];
	mat[3][1] = tmp;

	tmp = mat[2][3];
	mat[2][3] = mat[3][2];
	mat[3][2] = tmp;
}