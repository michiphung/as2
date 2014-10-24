#include "AggregatePrimitive.h"
#include <vector>
#include "Intersection.h"
#include <iostream>

using namespace std;

AggregatePrimitive::AggregatePrimitive(){

}
AggregatePrimitive::AggregatePrimitive(vector<GeometricPrimitive*> list)
{
	this->list = list;
}

// Assume *thit is INFINITY when input
bool AggregatePrimitive::intersect(Ray &ray, float *thit, Intersection* in){
	float tcurr = INFINITY;	
	Intersection currIn[1];
	for (int i = 0; i < list.size();  i++){
		if (list[i]->intersect(ray, &tcurr, currIn)){
			if (tcurr < *thit){
				*thit = tcurr;
				*in = *currIn;
			}
		}
	}

	if (*thit == INFINITY){
		return false;
	}
	return true;
}

bool AggregatePrimitive::intersectP(Ray &ray){
	for (int i = 0; i < list.size(); i++){
		if (list[i]->intersectP(ray))
			return true;
	}
	return false;
}
