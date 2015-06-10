#pragma once

#include "DangerTile.h"
#include "Cow.h"

class DangerTile : public Tile
{
public:
	DangerTile();
	void interaction(Cow* cow);
	void setType(int t);
};

