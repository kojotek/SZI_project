#pragma once
#include<vector>
#include <bitset>
#include "stdafx.h"
#include "types.h"


struct wpis
{
	wpis(std::bitset<CHROMOSOME_LENGTH> a, int b)
	{
		type = a;
		reaction = b;
	}

	std::bitset<CHROMOSOME_LENGTH> type;
	int reaction = 0;
};

class Knowledge
{
public:
	static std::vector<wpis> rejestr;
	static std::vector<wpis> temp1; //tymczasowy wektor potrzebny poki krowy niezaczna zrzucac zdarzen do rejestru
	static std::vector<wpis> temp2; //tymczasowy wektor potrzebny poki krowy niezaczna zrzucac zdarzen do rejestru
	static void wyczyscRejestr();
	static int countDangerObject(std::bitset<CHROMOSOME_LENGTH> genotyp);
	static int countNeutralObject(std::bitset<CHROMOSOME_LENGTH> genotyp);
};

