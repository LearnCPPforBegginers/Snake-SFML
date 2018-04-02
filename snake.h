#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

class Snake
{
public:
	Snake(sf::CircleShape *tail);
	~Snake();
	
	sf::CircleShape drawHead() { return head; }
	sf::CircleShape drawTail() { return tail; }
	sf::Vector2f getHeadPosition() { return head.getPosition(); }

	int getTailLength() { return tailLength; }
	
	void setHeadPosition(sf::Vector2f &headPosition);
	void incrementTail();
	void setTailElementsPos(sf::Vector2f newPosition, int &tailIndex);
	void setTailPosition() { tail.setPosition(head.getPosition().x - 20, head.getPosition().y); }
	void setTailLength(int tailLength) { this->tailLength = tailLength; }
	void setTailMovement(float angle);
	void rotateHead(float angle);
	//void setLastHeadPosition(sf::Vector2f lastHeadPosition) { this->lastHeadPosition = lastHeadPosition; };

	sf::CircleShape getTailElements(int &index) { return tailElements[index]; };

	// Snake movement
	void setMoveDirection(sf::Vector2f moveDirection) { this->moveDirection = moveDirection; }; // set the direction the snake must move
	void moveStart() { head.move(this->moveDirection.x, this->moveDirection.y); } // makes the snake move continously in a direction
	void tailMove() { tail.move(this->moveDirection.x, this->moveDirection.y); }

	sf::FloatRect getCollision() { return head.getGlobalBounds(); } // return the size of the collision box around snake head

private:
	
	static int tailLength;
	int sizeOfTail;
	//sf::Vector2f lastHeadPosition;

	sf::CircleShape head, tail; // snake body components
	sf::Vector2f moveDirection;

	sf::CircleShape *tailElements; // total number of tail objects cumulated while eating stuff
	
};
