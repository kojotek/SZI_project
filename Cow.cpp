#include "stdafx.h"
#include "Cow.h"
#include "Tile.h"
#include "Application.h"

Cow::Cow(Tile* tile)
{
	startTile = tile;
	current = tile;
	next = tile;
	shape.setPosition( tile->shape.getPosition() );
	shape.setRadius(TILE_SIZE/2);
	shape.setOutlineThickness(2);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);

	findingWay = true;
	finished = false;
	currentMove = 0;
	counter = 0;
}


void Cow::work()
{
	if (! workFinished() )
	{
		if ( findingWay )
		{
			moves = findWay();
			findingWay = false;
		}
		else
		{
			if ( currentMove < moves.size() )
			{
				if (!animationStep(current, next, counter))
				{
					counter = 0;
					current = next;
					next = application::gameMap.getTileNeighbour(next, moves[currentMove]);
					
					//zrob interakcje z polem
					//if krowa.martwa { finished = true; return; }
					
					if (application::gameMap.isTileFinishingLine(current))
					{
						finished = true;
						return;
					}
					else
					{
						currentMove++;
					}
				}

				counter++;

			}

		}
	}
}



bool Cow::animationStep(Tile* from, Tile* to, int step)
{

	if (to == NULL)
	{
		std::cout << moves.size() << std::endl;
		system("pause");
	}

	if (step < MOVE_FRAMES)
	{
		sf::Vector2f fromCoord(from->shape.getPosition().x, from->shape.getPosition().y);
		sf::Vector2f toCoord(to->shape.getPosition().x, to->shape.getPosition().y);
		shape.setPosition(fromCoord + (float)step * ( (toCoord - fromCoord) / (float)MOVE_FRAMES) );
		return true;
	}
	else
	{
		shape.setPosition( to->shape.getPosition() );
		return false;
	}

}


void Cow::draw()
{
	application::window.draw(shape);
}



bool Cow::workFinished()
{
	return finished;
}



std::vector<direction> Cow::findWay()
{
	std::vector<direction> temp;
	for (size_t i = 0; i < application::gameMap.mapSize.x; i++)
	{
		temp.push_back(RIGHT);
	}
	return temp;
}