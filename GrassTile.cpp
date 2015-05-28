#include "stdafx.h"
#include "grassTile.h"
#include "application.h"

GrassTile::GrassTile()                       
{
	shape.setFillColor(sf::Color::Green);
	type = 0;
	weight = 1;
}

void GrassTile::interaction()
{
}