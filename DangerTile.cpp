#include "stdafx.h"
#include "DangerTile.h"
#include "GrassTile.h"
#include "Application.h"
#include "Knowledge.h"


DangerTile::DangerTile()
{
	shape.setFillColor(sf::Color::Red);
	rodzaj = 2;
}

void DangerTile::interaction(Cow* cow)
{
	cow->kill();
	wpis w(this->getType(), REACTION_EXPLOSION, application::gameMap.getTileCoord(this));
	Knowledge::rejestr.push_back(w);
	application::gameMap.setTileByXY( application::gameMap.getTileCoord(this), new GrassTile());
}

void DangerTile::setType(int t)
{
	type = t;
	shape.setTexture(&texture::danger[t]);
}