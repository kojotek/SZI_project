#include "Knowledge.h"

std::vector<wpis> Knowledge::rejestr;

//tymczasowe wektory potrzebne poki krowy niezaczna zrzucac zdarzen do rejestru
std::vector<wpis> Knowledge::temp1; //dla obiektow niebezpiecznych
std::vector<wpis> Knowledge::temp2; //dla obiektow neutralnych

void Knowledge::wyczyscRejestr()
{
	rejestr.clear();
	temp1.clear();
	temp2.clear();
}

int Knowledge::countDangerObject(std::bitset<CHROMOSOME_LENGTH> genotyp)
{
	//brak danych o pszemarszu krow - jak narazie ocena losowo
	int result = std::rand() % NUMBER_OF_COWS;
	bool dodaj = true;

	for (int i = 0; i < temp1.size(); i++)
	{
		if (temp1.at(i).type == genotyp)
		{
			result = temp1.at(i).reaction;
			dodaj = false;
			break;
		}
	}

	if (dodaj) temp1.push_back(wpis(genotyp, result));

	return result;
}

int Knowledge::countNeutralObject(std::bitset<CHROMOSOME_LENGTH> genotyp)
{
	//brak danych o pszemarszu krow - jak narazie ocena losowo
	int result = std::rand() % NUMBER_OF_COWS;
	bool dodaj = true;

	for (int i = 0; i < temp2.size(); i++)
	{
		if (temp2.at(i).type == genotyp)
		{
			result = temp2.at(i).reaction;
			dodaj = false;
			break;
		}
	}

	if (dodaj) temp2.push_back(wpis(genotyp, result));

	return result;
}
