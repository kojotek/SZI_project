#pragma once

#include "NeutralTile.h"
#include "Cow.h"

class NeutralTile : public Tile
{
public:
	NeutralTile();
	void interaction(Cow* cow);
	void setType(int t);
};


