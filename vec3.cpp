#include "vec3.h"

void vec3::createVec3(float vec[3], float x, float y, float z)
{
	vec[0] = x;

	vec[1] = y;

	vec[2] = z;
}
float vec3::dot(float vector1[3], float vector2[3])

{
	return (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]) + (vector1[2] * vector2[2]);
}

void vec3::clamp(float vector[3], float high, float low)
{
	for (int i = 0; i < 2; i++)
	{
		if (vector[i] > high)
		{
			vector[i] = high;
		}
		else if (vector[i] < low)
		{
			vector[i] = low;
		}
	}
}

void vec3::normalize(float vector1[3], float vector2[3])
{
	float magnitude = std::sqrt(vector1[0] * vector1[0] + vector1[1] * vector1[1] + vector1[2] * vector1[2]);
	if (magnitude > 0) {
		vector2[0] = vector1[0] / magnitude;
		vector2[1] = vector1[1] / magnitude;
		vector2[2] = vector1[2] / magnitude;
	}
}
