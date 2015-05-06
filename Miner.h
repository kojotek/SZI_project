#pragma once
#include "iWork.h"

class Miner : public iWork
{
private:
	int counter;

public:
	void work();
	Miner();
};

