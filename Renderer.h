#pragma once

#include <stdint.h>
#include <iostream>

class Renderer
{
public:
	uint32_t CalcPixel(int pixelX, int pixelY, int screenWidth, int screenHeight);
};

