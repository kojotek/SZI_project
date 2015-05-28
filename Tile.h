#pragma once

#include "iDraw.h"
#include <string>
#include "types.h"

class Tile : public iDraw
{
protected:
	std::bitset<CHROMOSOME_LENGTH> type;

public:
	int f, g, h;
	Tile* parent;
	int whichSonAmI;
	int weight;
	sf::RectangleShape shape;
	void draw();
	std::bitset<CHROMOSOME_LENGTH> getType();
	void setType(std::bitset<CHROMOSOME_LENGTH> t);
	virtual void interaction() = 0;
	bool onList(std::vector<Tile*> nodes);

	Tile();
};