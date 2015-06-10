#include "stdafx.h"
#include "GrassTile.h"

GrassTile::GrassTile()                       
{
	shape.setFillColor(sf::Color::Green);
	shape.setTexture(&texture::grass);
	type = 0;
	weight = 1;
	rodzaj = 0;
}

void GrassTile::interaction(Cow* cow)
{
}

void GrassTile::setType(int t)
{
	type = t;
}