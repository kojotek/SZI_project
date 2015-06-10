#include "stdafx.h"
#include "NeutralTile.h"
#include "Knowledge.h"

NeutralTile::NeutralTile()
{
	shape.setFillColor(sf::Color::Yellow);
	weight = 100;
	rodzaj = 1;
}

void NeutralTile::interaction(Cow* cow)
{
	wpis w(this->getType(), REACTION_NONE, application::gameMap.getTileCoord(this));
	Knowledge::rejestr.push_back(w);
}

void NeutralTile::setType(int t)
{
	type = t;
	shape.setTexture(&texture::neutral[t]);
}
