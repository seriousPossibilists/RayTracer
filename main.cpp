
#include <SFML/Graphics.hpp>

int width = 800;
int height = 600;
std::vector<sf::Uint8> image(width* height * 4);

void setupTex()
// set pixel (x, y):
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < width; y++)
		{
			double r = ((double)rand() / (RAND_MAX));
			image[(x + y * width) * 4 + 0] = r;
			 r = ((double)rand() / (RAND_MAX));
			image[(x + y * width) * 4 + 1] = r;
			 r = ((double)rand() / (RAND_MAX));
			image[(x + y * width) * 4 + 2] = r;
			//alpha channel is 1
			image[(x + y * width) * 4 + 3] = 1.0f;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Not Tetris");

	sf::Texture texture;

	setupTex();
	// update texture:
	texture.update(image.data());

	sf::Sprite sprite;
	sprite.setTexture(texture);

		// inside the main loop, between window.clear() and window.display()


	sf::Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}
		window.draw(sprite);
	}

	return 0;
}
