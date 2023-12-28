#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Renderer.h"


int width = 1000;
int height = 1000;
std::vector<sf::Uint8> image(width* height * 4);
glm::vec3 rayOrigin = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 directionVector = glm::vec3(0.0f, 0.0f, 0.0f);

bool leftKeyPressed = false;
bool rightKeyPressed = false;

Renderer renderer;

void setupTex(int w, int h, glm::vec3 rayOrigin)
{
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			//height - y as sfml uses flipped coordinates for the y axis
			glm::vec3 color = renderer.CalcPixel(x, height - y, w, h, rayOrigin);

			sf::Uint8 r = color.x * 255.0f;

			image[(x + y * width) * 4 + 0] = r;

			r = color.y * 255.0f;

			image[(x + y * width) * 4 + 1] = r;

			r = color.z * 255.0f;

			image[(x + y * width) * 4 + 2] = r;
			//alpha channel is 1
			image[(x + y * width) * 4 + 3] = 255;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer");
	sf::Texture texture;
	texture.create(width, height);


	setupTex(width, height, rayOrigin);
	// update texture:
	texture.update(image.data());

	sf::Sprite sprite;
	sprite.setTexture(texture);

		// inside the main loop, between window.clear() and window.display()
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	float fps;

	sf::Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			start = std::chrono::high_resolution_clock::now();

			if (event.type == sf::Event::Closed) {

				window.close();

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// move left..
				leftKeyPressed = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// move right...
				/*
				rayOrigin.x += 0.05f;
				setupTex(width, height, rayOrigin);
				texture.update(image.data());

				window.draw(sprite);
				window.display(); */
				rightKeyPressed = true;
				directionVector.x = 0.05f;

			}

		}
		rayOrigin += directionVector;
		setupTex(width, height, rayOrigin);
		texture.update(image.data());


		window.draw(sprite);
		window.display();
		end = std::chrono::high_resolution_clock::now();
		fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << fps << "\n";
	}

	return 0;
}
