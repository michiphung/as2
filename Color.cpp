#include "Color.h"
#include <iostream>
Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
}

Color Color::operator+(Color c){
	return Color(this->r + c.r, this->g + c.g, this->b + c.b);
}

Color Color::operator-(Color c){
	return Color(this->r + c.r, this->g + c.g, this->b + c.b);
}

Color Color::operator*(float scalar){
	return Color(scalar * this->r, scalar * this->g, scalar * this->b);
}

Color Color::operator*(Color c){
	return Color(this->r * c.r, this->g * c.g, this->b * c.b);
}

Color Color::operator/(float scalar){
	return Color(scalar / this->r, scalar / this->g, scalar / this->b);
}

void Color::print(){
	std::cout << "[" << r << "," << g << "," << b << "]\n";
}



