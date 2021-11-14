#pragma once
#include<stack>
#include<ctime>
#include<vector>
struct Cell {
	bool eastWall = true, southWall = true;
};

enum class WallDirection
{
	East = 0,
	South = 1
};
class Maze {
private:
	int m_size;
	const int GRID_UNIT;
	Cell* m_cells;
public:
	std::vector<sf::RectangleShape> walls;
	Maze(int size, int GRID_UNIT):m_size(size), GRID_UNIT(GRID_UNIT) {
		m_cells = new Cell[size*size];
	}
	void Generate() {
		srand(time(NULL));
		int field = m_size*m_size;
		std::pair<int, int> *alreadyVisited = new std::pair<int, int>[field];
		std::stack<std::pair<int, int>> walkHistory;

		*(alreadyVisited + 0) = std::make_pair(0, 0);
		walkHistory.push(std::make_pair(0, 0));
		int alreadyVisitedAmount = 1;
		while (!walkHistory.empty()) {
			std::pair<int, int> current = walkHistory.top();
									//WEST, NORTH, EAST, SOUTH//
			bool possibleToVisit[] = {true, true, true ,true};
			std::pair<int, int> possibleLocation[] = {
				std::pair<int,int>(current.first-1,current.second),
				std::pair<int,int>(current.first,current.second-1),
				std::pair<int,int>(current.first+1,current.second),
				std::pair<int,int>(current.first,current.second+1)
			};
			if (possibleLocation[0].first < 0) {
				possibleToVisit[0] = false;
			}
			if (possibleLocation[1].second < 0) {
				possibleToVisit[1] = false;
			}
			if (possibleLocation[2].first >= m_size) {
				possibleToVisit[2] = false;
			}
			if (possibleLocation[3].second >= m_size) {
				possibleToVisit[3] = false;
			}
			for (int i = 0; i < field; i++) {

				if (possibleToVisit[0]&&alreadyVisited[i]==possibleLocation[0]) {
					possibleToVisit[0] = false;
				}
				if (possibleToVisit[1] && alreadyVisited[i] == possibleLocation[1]) {
					possibleToVisit[1] = false;
				}
				if (possibleToVisit[2] && alreadyVisited[i] == possibleLocation[2]) {
					possibleToVisit[2] = false;
				}
				if (possibleToVisit[3] && alreadyVisited[i] == possibleLocation[3]) {
					possibleToVisit[3] = false;
				}
			}
			std::vector < int > possibilites;
			int amountOfPossibilities=0;
			for (int i = 0; i < 4; i++) {
				if (possibleToVisit[i])
				{
					possibilites.push_back(i);
					amountOfPossibilities++;
				}
			}
			
			if (amountOfPossibilities == 0) {
				walkHistory.pop();
				continue;
			}
			int chosenIndex = rand() % amountOfPossibilities;
			int chosenDirection = possibilites.at(chosenIndex);
			switch (chosenDirection)
			{
			case 0: {
				alreadyVisited[alreadyVisitedAmount] = possibleLocation[0];
				walkHistory.push(possibleLocation[0]);
				GetCellByCords(possibleLocation[0].first, possibleLocation[0].second).eastWall=false;
				break;
			}
			case 1: {
				alreadyVisited[alreadyVisitedAmount] = possibleLocation[1];
				walkHistory.push(possibleLocation[1]);
				GetCellByCords(possibleLocation[1].first, possibleLocation[1].second).southWall = false;
				break;
			}
			case 2: {
				GetCellByCords(current.first,current.second).eastWall = false;
				alreadyVisited[alreadyVisitedAmount] = possibleLocation[2];
				walkHistory.push(possibleLocation[2]);
				break;
			}
			case 3: {
				GetCellByCords(current.first, current.second).southWall = false;
				alreadyVisited[alreadyVisitedAmount] = possibleLocation[3];
				walkHistory.push(possibleLocation[3]);
				break;
			}
			default:
				break;
			}
			alreadyVisitedAmount++;

		}
		for (int y = 0; y < m_size; y++) {
			for (int x = 0; x < m_size; x++) {
				Cell &cell = GetCellByCords(x, y);
				if (cell.eastWall) {
					sf::RectangleShape wallShape = sf::RectangleShape(sf::Vector2f(2, GRID_UNIT));
					wallShape.setPosition(sf::Vector2f(x * GRID_UNIT + GRID_UNIT, y * GRID_UNIT));
					walls.push_back(wallShape);
				}
				if (cell.southWall) {
					sf::RectangleShape wallShape = sf::RectangleShape(sf::Vector2f(GRID_UNIT, 2));
					wallShape.setPosition(sf::Vector2f(x * GRID_UNIT, y * GRID_UNIT + GRID_UNIT));
					walls.push_back(wallShape);
				}
			}
		}
	}
	Cell& GetCellByCords(int x, int y) const {
		return *(m_cells + x + (y * m_size));
	}
	Cell* GetCells() {
		return m_cells;
	}
	void Draw(sf::RenderWindow& window) const {
		int field = m_size * m_size;
		sf::RectangleShape winShape(sf::Vector2f(GRID_UNIT, GRID_UNIT));
		winShape.setFillColor(sf::Color::Green);
		winShape.setPosition(sf::Vector2f((m_size - 1)*GRID_UNIT, (m_size - 1)*GRID_UNIT));
		window.draw(winShape);
		
		int wallsAmount = walls.size();
		for (int i = 0; i < wallsAmount; i++) {
			window.draw(walls.at(i));
		}		
	}
};
