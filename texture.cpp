#include "texture.h"


texture::texture()
{
	for (int i = 1; i <= NUMBER_OF_DANGER_OBJECTS; i++)
	{
		danger[i].loadFromFile("miny\\" + intToStr(i) + ".jpg");
	}

	for (int i = 1; i <= NUMBER_OF_NEUTRAL_OBJECTS; i++)
	{
		neutral[i].loadFromFile("obiekty\\" + intToStr(i) + ".jpg");
	}

	grass.loadFromFile("grass.jpg");
}

std::string texture::intToStr(int n)
{
	std::string tmp, ret;
	if (n < 0) {
		ret = "-";
		n = -n;
	}
	do {
		tmp += n % 10 + 48;
		n -= n % 10;
	} while (n /= 10);
	for (int i = tmp.size() - 1; i >= 0; i--)
		ret += tmp[i];
	return ret;
}

sf::Texture texture::grass;
sf::Texture texture::danger[NUMBER_OF_DANGER_OBJECTS];
sf::Texture texture::neutral[NUMBER_OF_DANGER_OBJECTS];


