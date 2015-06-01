#include "stdafx.h"
#include "GrassTile.h"

GrassTile::GrassTile()                       
{
	shape.setFillColor(sf::Color::Green);
	type = 0;
	weight = 1;
}

void GrassTile::interaction(Cow* cow)
{
}