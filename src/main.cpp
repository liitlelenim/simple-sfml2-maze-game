#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Maze.h"


void NormalizeDiagonalVector(sf::Vector2f &vector) {
	if (vector.x != 0 && vector.y != 0) {
		vector.x = vector.x/sqrt(2);
		vector.y = vector.y/sqrt(2);
	}
}

int main()
{
	std::string mode;
	std::cout << "Press enter to start:";
	std::getline(std::cin,mode);
	std::cout << std::endl;

	int gridUnitSetting = 40;
	int mazeSizeSetting = 20;
	
	if (mode == "debug") {
		std::cout << "Input grid unit size:";
		std::cin >> gridUnitSetting;
		std::cout << "\nInput maze size setting:";
		std::cin >> mazeSizeSetting;
	}
	
	const int GRID_UNIT = gridUnitSetting;
	int mazeSize = mazeSizeSetting;
	Maze maze(mazeSize, GRID_UNIT);
	maze.Generate();
	Player player(gridUnitSetting, mazeSizeSetting, sf::Vector2f(10, 10),&maze);
	player.SetSpeed(GRID_UNIT*5);
	sf::RectangleShape playerShape(player.shape);
	sf::Clock clock;

	sf::RenderWindow window;
	window.create(sf::VideoMode(mazeSize*GRID_UNIT, mazeSize*GRID_UNIT), "maze");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
#pragma region Input

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: 
				{
					window.close();
					break;
				}
			}
		}

		sf::Vector2f moveDir = sf::Vector2f(0, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			moveDir.x = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			moveDir.x = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			moveDir.y = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			moveDir.y = 1;
		}
		NormalizeDiagonalVector(moveDir);

#pragma endregion

	window.clear();

		//UPDATE 
#pragma region TimeDrivenActions
		sf::Time dTime = clock.getElapsedTime();
		player.Move(sf::Vector2f(moveDir.x*dTime.asSeconds(), moveDir.y*dTime.asSeconds()));
		clock.restart();
#pragma endregion

		playerShape.setPosition(player.GetPosition());
		window.draw(playerShape);
		maze.Draw(window);
		window.display();

	}
	return EXIT_SUCCESS;
}