#pragma once
#include <vector>
#include <cmath>
#include <iostream>

using std::vector;

class vec3
{
public:
	float dot(float vector1[3], float vector2[3]);

	void clamp(float vector[3], float high, float low);

	void createVec3(float vec[3], float x, float y, float z);

	void normalize(float vector1[3], float vector2[3]);
};

