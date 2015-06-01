#include "stdafx.h"
#include "NeutralTile.h"
#include "Knowledge.h"

NeutralTile::NeutralTile()
{
	shape.setFillColor(sf::Color::Yellow);
	weight = 100;
}


void NeutralTile::interaction(Cow* cow)
{
	wpis w(this->getType(), REACTION_NONE);
	Knowledge::rejestr.push_back(w);
}
