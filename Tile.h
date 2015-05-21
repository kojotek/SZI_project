#pragma once

#include "iDraw.h"
#include <string>
#include "types.h"

class Tile : public iDraw
{
protected:
	std::bitset<CHROMOSOME_LENGTH> type;

public:
	sf::RectangleShape shape;
	void draw();
	std::bitset<CHROMOSOME_LENGTH> getType();
	void setType(std::bitset<CHROMOSOME_LENGTH> t);
	virtual void interaction() = 0;
	Tile();
};