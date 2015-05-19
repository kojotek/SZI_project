#include "stdafx.h"
#include "Cow.h"
#include "Tile.h"
#include "Application.h"

Cow::Cow(Tile* tile)
{
	current = tile;
	target = tile;
	shape.setPosition( tile->shape.getPosition() );
	shape.setRadius(TILE_SIZE/2);
	shape.setOutlineThickness(2);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);

	timeForDecission = true;
	finished = false;
}


void Cow::work()
{
	if (!finished)
	{
		if (timeForDecission)
		{
			timeForDecission = false;
			makeNextStep();
			counter = 0;
		}
		else
		{
			if (moveAnim())
			{
				timeForDecission = true;
			}
		}
	}
}


void Cow::makeNextStep()
{
	target = application::gameMap.getTileByXY( application::gameMap.getTileCoord(current) + sf::Vector2i(1,0));

	if (target == NULL)
	{
		finished = true;
	}
}


bool Cow::moveAnim()
{
	if (counter < MOVE_FRAMES)
	{
		sf::Vector2f curr(current->shape.getPosition().x, current->shape.getPosition().y);
		sf::Vector2f tar(target->shape.getPosition().x, target->shape.getPosition().y);
		shape.move((tar - curr) / (float)MOVE_FRAMES );
		//std::cout << target->shape.getPosition().x << std::endl;
		counter++;
		return false;
	}
	else
	{
		current = target;
		shape.setPosition( target->shape.getPosition() );
		return true;
	}

}


void Cow::draw()
{
	application::window.draw(shape);
}

bool Cow::isFinished()
{
	return finished;
}