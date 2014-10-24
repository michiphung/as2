#include "Sampler.h"
#include <iostream>

Sampler::Sampler()
{

}

Sampler::Sampler(int width, int height){
	this->width = width;
	this->height = height;
	this->x = 0;
	this->y = 0;
}

bool Sampler::generateSample(Sample *sample){
	if (sample->x == width && sample->y == height)
		return false;
	if (sample->x < width){
		sample->x++;
		return true;
	}
	else{
		sample->y++;
		sample->x = 0;
		return true;
	}
}
