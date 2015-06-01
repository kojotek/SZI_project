#pragma once

#include "GrassTile.h"
#include "Cow.h"

class GrassTile : public Tile
{
public:
	GrassTile();
	void interaction(Cow* cow);
};

