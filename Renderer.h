#pragma once

#include <iostream>
#include <glm/glm.hpp>


class Renderer
{
public:
	glm::vec3 CalcPixel(int pixelX, int pixelY, int sw, int sh, glm::vec3 rayOrg);
};