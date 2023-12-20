#include "Renderer.h"
#include "vec3.h"

vec3 vectorObj;


uint32_t Renderer::CalcPixel(int pixelX, int pixelY, int screenWidth, int screenHeight)
{
	float radius = 0.5f * 800;
	float rayDirection[3];
	float rayOrigin[3];
	float hitPoint[3];
	float lightDirection[3];
	float normal[3];
	float pixelColor[3]; // alpha for all colors equals 1 (due to windows api) // pixelColor of the form rgb
	vectorObj.createVec3(rayDirection, pixelX -500, pixelY - 500, -1.0f * 800);
	vectorObj.createVec3(rayOrigin, 0, 0, 2.0f * 800);


	float a = vectorObj.dot(rayDirection, rayDirection);
	float b = 2.0f * vectorObj.dot(rayOrigin, rayDirection);
	float c = vectorObj.dot(rayOrigin, rayOrigin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		vectorObj.createVec3(pixelColor, 0.0f, 0.0f, 0.0f);
		vectorObj.clamp(pixelColor, 1.0f, 0.0f);
		return ((int)(pixelColor[0] * 255) << 16) | ((int)(pixelColor[1] * 255) << 8) | (int)(pixelColor[2] * 255);
	};

	// ray has hit sphere; computing hit position;
	//float t0 = (-b + std::sqrt(discriminant)) / (2.0f * a);

	float closestT = (-b - std::sqrt(discriminant)) / (2.0f * a);

	//this is also the normal as sphere origin is 0; (only after normalizing)
	//closestT is the smallest solution in all cases as "a" is always positive (a is a sum of squares)


	vectorObj.createVec3(hitPoint, rayOrigin[0] + rayDirection[0] * closestT, rayOrigin[1] + rayDirection[1] * closestT, rayOrigin[2] + rayDirection[2] * closestT);

	vectorObj.normalize(hitPoint, normal);
	vectorObj.createVec3(lightDirection, -1.0f, -1.0f, -1.0f);
	vectorObj.normalize(lightDirection, lightDirection);

	//making lightDirection an outgoing vector

	lightDirection[0] *= -1.0f;
	lightDirection[1] *= -1.0f;
	lightDirection[2] *= -1.0f;

	float angle = vectorObj.dot(normal, lightDirection);
	if (angle < 0.0f)
	{
		angle = 0.0f;
	}

	vectorObj.createVec3(pixelColor, angle, angle, 0);


	vectorObj.clamp(pixelColor, 1.0f, 0.0f);
	return ((int)(pixelColor[0] * 255) << 16) | ((int)(pixelColor[1] * 255) << 8) | (int)(pixelColor[2] * 255);
}