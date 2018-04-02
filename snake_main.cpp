#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "Snake.h"


float snakeSpeed = 3.5;
unsigned playerScore = 0;
bool gameOver = false;
bool askPlayAgain = true;

sf::Vector2f windowCenter;

void movementHandling(Snake &snakeObj, float &speed); // Get user input (W,A,S,D) and turn it into vectors

struct Wall
{
	sf::RectangleShape top, bottom, left, right;
};

int main()
{
	srand((unsigned)time(NULL));
	sf::RenderWindow window(sf::VideoMode(1024, 720), "Snake", sf::Style::Default); // Create the window for the game
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	windowCenter = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f); // variable for window center position

	Snake snake(0); // Create our snake object
	snake.setHeadPosition(windowCenter); // Set the starting position of the snake
	
	sf::CircleShape fruit(10.f, 6);
	fruit.setOutlineThickness(1.f);
	fruit.setFillColor(sf::Color::Red);
	fruit.setOutlineColor(sf::Color(200,100,100,255));
	
	fruit.setPosition(rand() % 300 + 100.f, rand() % 300 + 100.f);
	
	Wall wall;
	// Top wall properties and position
	wall.top.setSize(sf::Vector2f(window.getSize().x - 20.f, 10.f));
	wall.top.setPosition(sf::Vector2f(10.f, 30.f));
	wall.top.setFillColor(sf::Color::Yellow);
	
	// Bottom wall properties and position
	wall.bottom.setSize(sf::Vector2f(window.getSize().x - 20.f, 10.f));
	wall.bottom.setPosition(sf::Vector2f(10.f, window.getSize().y - 20.f));
	wall.bottom.setFillColor(sf::Color::Yellow);

	// Left wall properties and position
	wall.left.setSize(sf::Vector2f(10.f, window.getSize().y - 20.f));
	wall.left.setPosition(sf::Vector2f(10.f, 10.f));
	wall.left.setFillColor(sf::Color::Yellow);

	// Right wall properties position
	wall.right.setSize(sf::Vector2f(10.f, window.getSize().y - 20.f));
	wall.right.setPosition(sf::Vector2f(window.getSize().x - 20.f, 10.f));
	wall.right.setFillColor(sf::Color::Yellow);
	
	// Text properties and position
	sf::Font arial;
	try
	{
		if (!arial.loadFromFile("Fonts/Arial.ttf"))
			throw 1;
	}
	catch (int exceptThrown)
	{
		if (exceptThrown == 1)
		{
			std::ofstream log;
			log.open("warnings_log.txt");
			log << "Can not load font Arial.tff\n";
			log.close();
		}
			
	}
	
	sf::Text score;
	score.setFont(arial);
	score.setFillColor(sf::Color::White);
	score.setPosition(30.f, 5.f);
	std::string tmpScore = "Score: " + std::to_string(playerScore);
	score.setString(tmpScore);
	score.setCharacterSize(20);

	sf::Text gameoverText;
	gameoverText.setFont(arial);
	gameoverText.Bold;
	gameoverText.setPosition(window.getSize().x - window.getSize().x / 1.2f, window.getSize().y - (window.getSize().y / 1.5f));
	gameoverText.setString("Game Over");
	gameoverText.setCharacterSize(150);

	sf::Text playAgain;
	playAgain.setFont(arial);
	playAgain.Bold;
	playAgain.setPosition(window.getSize().x - window.getSize().x / 1.3f, window.getSize().y - (window.getSize().y / 3.f));
	playAgain.setString("Play Again");
	playAgain.setCharacterSize(50);

	sf::Text quitGame;
	quitGame.setFont(arial);
	quitGame.Bold;
	quitGame.setPosition(window.getSize().x - window.getSize().x / 2.f, window.getSize().y - (window.getSize().y / 3.f));
	quitGame.setString("Quit Game");
	quitGame.setCharacterSize(50);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//Dont stretch the window contents when its resized
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
			}
			break;
			//Dont stretch the window contents when its resized
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(visibleArea));
			}
			break;
			}
		}
		//Update
		if (!gameOver && askPlayAgain)
		{
			snake.moveStart();
			movementHandling(snake, snakeSpeed);

			if (snake.getCollision().intersects(wall.top.getGlobalBounds())
				|| snake.getCollision().intersects(wall.bottom.getGlobalBounds())
				|| snake.getCollision().intersects(wall.left.getGlobalBounds())
				|| snake.getCollision().intersects(wall.right.getGlobalBounds()))
			{
				playAgain.setPosition(window.getSize().x - window.getSize().x / 1.3f, window.getSize().y - (window.getSize().y / 3.f));
				gameOver = true;
			}
			else if (snake.getCollision().intersects(fruit.getGlobalBounds()))
			{
				playerScore += 10;
				std::string tmpScore = "Score: " + std::to_string(playerScore);
				score.setString(tmpScore);
				
				fruit.setPosition(rand() % window.getSize().x + 0.f, rand() % window.getSize().y + 0.f);
				while (fruit.getPosition().x < 30 || fruit.getPosition().x >(window.getSize().x - 30)
					|| fruit.getPosition().y < 40 || fruit.getPosition().y >(window.getSize().y - 30))
				{
					fruit.setPosition(rand() % window.getSize().x + 0.f, rand() % window.getSize().y + 0.f);
				}
				
				snake.incrementTail();
			}

			//Draw
			window.clear();

			//Draw everything
				// draw the snake object
			window.draw(fruit);
			window.draw(snake.drawHead());
			
			// ingame walls
			std::string tmpScore = "Score: " + std::to_string(playerScore);
			score.setString(tmpScore);
			
			window.draw(score);
			window.draw(wall.top);
			window.draw(wall.bottom);
			window.draw(wall.left);
			window.draw(wall.right);
			
			for (int i = 0; i < snake.getTailLength(); i++)
			{
				float headX = snake.getHeadPosition().x + snake.drawHead().getRadius()/2 + snake.drawTail().getRadius() + (i+1) * 15;
				float headY = snake.getHeadPosition().y;
				snake.setTailElementsPos(sf::Vector2f(headX, headY), i);
				snake.tailMove();
				window.draw(snake.getTailElements(i));
			}
		}
		else
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosF((float)mousePos.x, (float)mousePos.y);
			if (playAgain.getGlobalBounds().contains(mousePosF))
			{
				playAgain.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					playAgain.setFillColor(sf::Color::Red);
					playAgain.setPosition(window.getSize().x - window.getSize().x / 1.3f, window.getSize().y - (window.getSize().y / 3.1f));
					askPlayAgain = true;
					gameOver = false;
					
					snake.setHeadPosition(windowCenter);
					snake.setMoveDirection(sf::Vector2f(0.f, 0.f));
					snake.setTailLength(0);

					playerScore = 0;
					std::string tmpScore = "Score: " + std::to_string(playerScore);
					score.setString(tmpScore);
					
					fruit.setPosition(rand() % 300 + 100.f, rand() % 300 + 100.f);
				}
			}
			else
			{
				playAgain.setFillColor(sf::Color::White);
			}
			window.draw(gameoverText);
			window.draw(playAgain);
			window.draw(quitGame);
		}
		window.display();
	}
	return 0;
}

void movementHandling(Snake &snakeObj, float &speed)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Move up
	{
		snakeObj.setMoveDirection(sf::Vector2f(0.f, -speed));
		snakeObj.rotateHead(90.f);
		//snakeObj.setTailMovement(90.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Move down
	{
		snakeObj.setMoveDirection(sf::Vector2f(0.f, speed));
		snakeObj.rotateHead(-90.f);
		//snakeObj.setTailMovement(-90.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Move left
	{
		snakeObj.setMoveDirection(sf::Vector2f(-speed, 0.f));
		snakeObj.rotateHead(180.f);
		//snakeObj.setTailMovement(180.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Move right
	{
		snakeObj.setMoveDirection(sf::Vector2f(speed, 0.f));
		snakeObj.rotateHead(-180.f);
		//snakeObj.setTailMovement(-180.f);
	}
}
