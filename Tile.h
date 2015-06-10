#pragma once

#include "iDraw.h"
#include "Cow.h"
#include "types.h"
#include "application.h"
#include "texture.h"

class Cow;

class Tile : public iDraw
{
protected:
	int type;

public:
	int f, g, h;
	int rodzaj;
	Tile* parent;
	int whichSonAmI;
	int weight;
	sf::RectangleShape shape;
	void draw();
	int getType();
	virtual void setType(int t) = 0;
	virtual void interaction(Cow* cow) = 0;
	bool onList(std::vector<Tile*> nodes);

	Tile();
};