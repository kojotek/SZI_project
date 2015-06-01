#include "stdafx.h"
#include "Cow.h"
#include "Tile.h"
#include "Application.h"
#include "types.h"

std::vector<Cow*> Cow::allCows;


Cow::Cow(Tile* tile)
{
	allCows.push_back(this);
	startTile = tile;
	current = tile;
	current = tile;
	next = tile;
	finishingNode = NULL;
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



Cow::~Cow()
{
	std::vector<Cow*>::iterator it = std::find(allCows.begin(), allCows.end(), this);
	allCows.erase(it);
}


void Cow::work()
{
	if (! workFinished() )
	{
		if ( findingWay )
		{
			finishingNode = findWay();
			moves = reconstructWay();
			findingWay = false;
			application::gameMap.clearPathfinding();
		}
		else
		{
			if ( currentMove < moves.size() )
			{
				if (!animationStep(current, next, counter))
				{
					counter = 0;			
					current = next;

					current->interaction(this);

					Tile* possibleNextMove = application::gameMap.getTileNeighbour(next, moves[currentMove]);
					bool MovementPossible = true;

					for (int i = 0; allCows[i] != this && i<allCows.size(); i++)
					{
						if (allCows[i]->next == possibleNextMove || allCows[i]->current == possibleNextMove)
						{
							next = current;
							MovementPossible = false;
						}
					}
					if (MovementPossible)
					{
						next = possibleNextMove;
						currentMove++;
					}
					

				}

				counter++;

			}
			else
			{
					finished = true;
					return;
			}

		}
	}
}



bool Cow::animationStep(Tile* from, Tile* to, int step)
{

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



Tile* Cow::findWay()
{
	std::vector<Tile*> openNodes;
	std::vector<Tile*> closedNodes;

	openNodes.push_back(startTile);

	while (!openNodes.empty())
	{

		Tile* Q = openNodes[0];	//wybieramy wezel o najmniejszym F
		
		for (size_t i = 0; i < openNodes.size(); i++)
		{
			if (openNodes[i]->f < Q->f)
			{
				Q = openNodes[i];
			}
		}

		if ( application::gameMap.isTileFinishingLine(Q))
		{
			return Q;
		}

		closedNodes.push_back(Q); //przeniosimy Q do odwiedzonych
		std::vector<Tile*>::iterator it = std::find(openNodes.begin(), openNodes.end(), Q);
		openNodes.erase(it);


		for (int i = 0; i < 4; i++ )	// dla kazdego sasiada
		{
			Tile* neighbour = application::gameMap.getTileNeighbour(Q, i);
			if (neighbour == NULL || neighbour->onList(closedNodes))
			{
				continue;
			}

			int newG = neighbour->weight + Q->g;

			if (newG < neighbour->g || neighbour->g == 0 || !neighbour->onList(openNodes))
			{
				neighbour->h = application::gameMap.getDistanceFromFinish(neighbour);
				neighbour->g = newG;
				neighbour->f = neighbour->g + neighbour->f;
				neighbour->parent = Q;
				neighbour->whichSonAmI = i;
				if (!neighbour->onList(openNodes))
				{
					openNodes.push_back(neighbour);
				}

			}

			
		}
		
	}

	return NULL;
}




std::vector<int> Cow::reconstructWay()
{
	std::vector<int> result;
	for (Tile* n = finishingNode; n->parent != NULL; n = n->parent)
	{
		result.push_back(n->whichSonAmI);
	}
	std::reverse(result.begin(), result.end());
	return result;

}




void Cow::kill()
{
	finished = true;
}