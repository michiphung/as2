
//
//  Light.h
//  as2
//
//  Created by Michelle Hanh Phung on 3/8/14.
//  Copyright (c) 2014 Michelle Hanh Phung. All rights reserved.
//
#include "stdafx.h"
#pragma once
#ifndef LIGHT_h
#define LIGHT_h
#include "Light.h"
#include "Color.h"
#include "Ray.h"
#include "LocalGeo.h"

using namespace std;

class Point;

class Light{
public:
	bool isPoint; // 1 for Point, 0 for directional light
	Point pos; // x y z coordinates
	Color color;
	Light(bool type, float x, float y, float z, float r, float g, float b);
	void generateLightRay(LocalGeo &local, Ray *lray, Color *lcolor);
	void print();
};


#endif
