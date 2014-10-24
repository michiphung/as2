#pragma once
#ifndef SAMPLER_H
#define SAMPLER_H

struct Sample{
	int x, y;
};

class Sampler
{
public:
	int width, height;
	int x;
	int y;
	Sampler();
	Sampler(int width, int height);
	bool generateSample(Sample *sample);
};

#endif

