
//
//  Ray.h
//  as2
//
//  Created by Michelle Hanh Phung on 3/8/14.
//  Copyright (c) 2014 Michelle Hanh Phung. All rights reserved.
//
#pragma once
#ifndef RAY_H
#define RAY_H


class Point;
class Vector;

class Ray{
public:
	Point* o;
	Vector* d;
	float t_min, t_max;
	Ray();
	Ray(Point* pos, Vector* dir, float t_min, float t_max);
    Vector getDirection();
};


#endif

