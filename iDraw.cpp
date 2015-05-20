#include "stdafx.h"
#include "iDraw.h"
#include <vector>

std::vector<iDraw*> iDraw::drawVector;

iDraw::iDraw()
{
	drawVector.push_back(this);
}


iDraw::~iDraw()
{
	for (size_t a(0); a < drawVector.size(); a++)
	{
		if (this == drawVector[a])
		{
			drawVector.erase(drawVector.begin()+a);
			break;
		}
	}
}
