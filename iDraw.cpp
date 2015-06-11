#include "stdafx.h"
#include "iDraw.h"

std::vector<iDraw*> iDraw::drawVector;

iDraw::iDraw()
{
	drawVector.push_back(this);
}


iDraw::~iDraw()
{
	std::vector<iDraw*>::iterator it = std::find(drawVector.begin(), drawVector.end(), this);
	if (it != drawVector.end())
	{
		drawVector.erase(it);
	}
}
