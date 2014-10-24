#pragma once
class Matrix
{
public:
	float mat[4][4];
	Matrix();
	void rotation(float x, float y, float z, float degrees);  
	void translation(float x, float y, float z);
	void scale(float x, float y, float z); 
	void transpose();
};


