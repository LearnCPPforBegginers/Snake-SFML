#include "Snake.h"

int Snake::tailLength = 0;

Snake::Snake(sf::CircleShape *tail)
	:tailElements(tail)
{
	this->sizeOfTail = 1000;
	tailElements = new sf::CircleShape[sizeOfTail];
	

	this->head.setRadius(15.f);
	this->head.setOrigin(this->head.getRadius(), this->head.getRadius());
	
	this->tail.setRadius(10.f);
	this->tail.setFillColor(sf::Color::Green);
	this->tail.setOrigin(this->head.getRadius(), this->head.getRadius() - (this->head.getRadius() - this->tail.getRadius()));
}


Snake::~Snake()
{
	delete[] tailElements;
	tailElements = NULL;
}

void Snake::setHeadPosition(sf::Vector2f &headPosition) // split the radius of the head in 2 so the snake starts at the exact given position
{
	this->head.setPosition(headPosition.x - head.getRadius() / 2, headPosition.y - head.getRadius() / 2);
}

void Snake::incrementTail()
{
	++tailLength;
	for (int i = 0; i < tailLength; i++)
	{
		tailElements[i] = tail;
	}
	sizeOfTail++;
}

void Snake::setTailElementsPos(sf::Vector2f newPosition, int &tailIndex)
{
	this->tailElements[tailIndex].setPosition(newPosition);
}

void Snake::setTailMovement(float angle)
{
	if (angle != tail.getRotation())
		for (int i = 0; i < tailLength; i++)
		{
			tailElements[i].rotate(angle);
		}
}

void Snake::rotateHead(float angle)
{
	if(angle != head.getRotation())
		head.rotate(angle);
}
