#pragma once

#include "iDraw.h"
#include <string>

#define TILE_SIZE 30

class Tile : public iDraw
{
protected:
	std::string type;
	std::string possibleType;

public:
	sf::RectangleShape shape;
	void draw();
	std::string getType();
	void setPossibleType( std::string pt );
	std::string getPossibleType();
	virtual void interaction() = 0;
	Tile();
};

