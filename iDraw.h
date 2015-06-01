#pragma once


class iDraw
{
public:
	static std::vector<iDraw*> drawVector;

	virtual void draw()=0;
	iDraw();
	~iDraw();
};

