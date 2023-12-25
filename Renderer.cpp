#include "Renderer.h"


glm::vec3 Renderer::CalcPixel(int pixelX, int pixelY, int sw, int sh, glm::vec3 rayOrg)
{
	float radius = 0.5f * sw;

	glm::vec3 rayDirection = glm::vec3(pixelX - (sw * 0.5), pixelY - (sh * 0.5), -1.0f * sw);
	// glm::vec3 rayOrigin = glm::vec3(0.0f * sw, 0.0f * sh, 2.0f * sh);
	glm::vec3 rayOrigin = rayOrg;
	//scaling by screen coords
	rayOrigin *= glm::vec3(sw, sh, sw);


	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayOrigin, rayDirection);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		glm::vec3 pixelColor = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::clamp(pixelColor, 1.0f, 0.0f);
		return pixelColor;
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


	glm::vec3 pixelColor = glm::vec3(angle + 0.1f, angle, 0);
	glm::clamp(pixelColor, 1.0f, 0.0f);
	return pixelColor;
}