#include "Renderer.h"

uint32_t Renderer::CalcPixel(int pixelX, int pixelY, int screenWidth, int screenHeight)
{
	
	float x = { (float)pixelX / (float)screenWidth };
	float y = { (float)pixelY / (float)screenHeight };

	uint8_t r = (uint8_t)(x * 255.0f);
	uint8_t g = (uint8_t)(y * 255.0f);

	return (r << 16) | (g << 8) | 0;

}