#include "Renderer.h"
#include <glm/glm.hpp>


uint32_t Renderer::CalcPixel(int pixelX, int pixelY, int screenWidth, int screenHeight)
{
	float radius = 0.5f * 1000;

	glm::vec3 rayDirection = glm::vec3(pixelX - 500, pixelY - 500, -1.0f * 1000);
	glm::vec3 rayOrigin = glm::vec3(0, 0.0f * 1000, 2.0f * 1000);


	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayOrigin, rayDirection);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		glm::vec3 pixelColor = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::clamp(pixelColor, 1.0f, 0.0f);
		return ((int)(pixelColor.x * 255) << 16) | ((int)(pixelColor.y * 255) << 8) | (int)(pixelColor.z * 255);
	};

	// ray has hit sphere; computing hit position;
	//float t0 = (-b + std::sqrt(discriminant)) / (2.0f * a);

	float closestT = (-b - std::sqrt(discriminant)) / (2.0f * a);

	//this is also the normal as sphere origin is 0; (only after normalizing)
	//closestT is the smallest solution in all cases as "a" is always positive (a is a sum of squares)


	glm::vec3 hitPoint = rayOrigin + rayDirection * closestT;

	glm::vec3 normal = glm::normalize(hitPoint);

	glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -1));
	//making lightDirection an outgoing vector

	float angle = glm::max(glm::dot(normal, -lightDirection), 0.0f); // = cos(angle)


	glm::vec3 pixelColor = glm::vec3(angle, angle, 0);



	return ((int)(pixelColor.x * 255) << 16) | ((int)(pixelColor.y * 255) << 8) | (int)(pixelColor.z * 255);
}