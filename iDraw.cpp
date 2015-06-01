#include "stdafx.h"
#include "iDraw.h"

std::vector<iDraw*> iDraw::drawVector;

iDraw::iDraw()
{
	drawVector.push_back(this);
}


iDraw::~iDraw()
{
	for (int a(0); a < drawVector.size(); a++)
	{
		if (this == drawVector[a])
		{
			drawVector.erase(drawVector.begin()+a);
			break;
		}
	}
}
