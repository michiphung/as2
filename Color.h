#ifndef COLOR_H
#define COLOR_H
#pragma once

class Color
{
public:
	float r, g, b;
	Color();
	Color(float r, float g, float b);
	Color operator+(Color c);
	Color operator-(Color c);
	Color operator*(float scalar);
	Color operator*(Color c);
	Color operator/(float scalar);
	void print();
};

const Color BLACK = Color();

#endif

