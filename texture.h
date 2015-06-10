#pragma once
#include "stdafx.h"
#include "types.h"

class texture
{
	protected:
		std::string intToStr(int n);

	public:
		texture();
		static sf::Texture grass;
		static sf::Texture danger[NUMBER_OF_DANGER_OBJECTS];
		static sf::Texture neutral[NUMBER_OF_NEUTRAL_OBJECTS];
};
