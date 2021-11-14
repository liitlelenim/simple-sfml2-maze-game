#pragma once
#include "Maze.h"
class Player {
private:
	void PrintVector(const sf::Vector2f &vector) {
		std::cout << "x: " << vector.x << " y:" << vector.y << std::endl;
	}
	sf::Vector2f m_Position;
	int m_Speed;
	int GRID_UNIT=20;
	int mazeSize=20;
	Maze *maze;
public:
	sf::Vector2f shape;
	Player(int gridUnitSize, int mazeSize, sf::Vector2f shape, Maze *maze){
		m_Position = sf::Vector2f(0, 0);
		m_Speed = 0;
		this->GRID_UNIT = gridUnitSize;
		this->mazeSize = mazeSize;
		this->shape = shape;
		this->maze = maze;
	}
	sf::Vector2f GetPosition() const{
		return m_Position;
	}
	void Move(const sf::Vector2f &movement) {
		sf::Vector2f nextPosition = sf::Vector2f(m_Position.x + movement.x *m_Speed, m_Position.y + movement.y * m_Speed);
		PreventOutBounding(nextPosition);
		PreventCollsiion(m_Position,nextPosition);
		m_Position = nextPosition;
	}
	void SetSpeed(int speed) {
		m_Speed = speed;
	}
	void PreventOutBounding(sf::Vector2f &nextPosition)  {


		if (nextPosition.x < 0) {
			nextPosition.x = 0;
		}
		if (nextPosition.x + shape.x > GRID_UNIT*mazeSize)
		{
			nextPosition.x = GRID_UNIT * mazeSize-shape.x;
		}

		if (nextPosition.y < 0) {
			nextPosition.y = 0;

		}
		if (nextPosition.y+shape.y > GRID_UNIT*mazeSize)
		{
			nextPosition.y = GRID_UNIT * mazeSize-shape.y;
 
		}
	}
	void PreventCollsiion(const sf::Vector2f &currentPosition, sf::Vector2f &nextPosition) {
		int wallsAmount = maze->walls.size();
		
		for (int i = 0; i < wallsAmount; i++) {
			sf::RectangleShape wall = maze->walls.at(i);
			bool vertical = wall.getSize().y > wall.getSize().x;
			
			
				if(currentPosition.x > wall.getPosition().x && currentPosition.x  < wall.getPosition().x + wall.getSize().x)
				{
					if (currentPosition.y+shape.y< wall.getPosition().y && nextPosition.y+shape.y > wall.getPosition().y)
					{
						nextPosition.y = currentPosition.y;
					}
					else if (currentPosition.y > wall.getPosition().y && nextPosition.y < wall.getPosition().y)
					{
						nextPosition.y = currentPosition.y;
					}
				}
				if (currentPosition.y > wall.getPosition().y  && currentPosition.y < wall.getPosition().y + wall.getSize().y)
				{
					if (currentPosition.x + shape.x< wall.getPosition().x && nextPosition.x + shape.x > wall.getPosition().x)
					{
						nextPosition.x = currentPosition.x;
					}
					else if (currentPosition.x > wall.getPosition().x && nextPosition.x < wall.getPosition().x)
					{
						nextPosition.x = currentPosition.x;
					}
				}
				
			
		}
	}
};