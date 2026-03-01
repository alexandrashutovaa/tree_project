#ifndef _CELL_H_
#define _CELL_H_

#include <chrono>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

class cell;

struct Coords {
	float x;
	float y;
};

struct DATA {
	bool alive;
	Coords coords;
	cell* parent;
	cell* root;
	std::vector<cell*> children;
};

float Random();

Coords DisplayCoordinates(Coords coords, sf::RenderWindow* window, float scale);

// enum CellType {
// 	CELL_ZERO,
// 	CELL_STEM,
// 	CELL_PRODUCER
// };

class cell {
protected:
	bool alive;
	Coords coords;
	cell* parent;
	cell* root;
	std::vector<cell*> children;

public:
	cell(Coords coords, cell* parent);
	virtual ~cell();
	virtual void tick() = 0;
	void die();
	DATA getData();

	// SFML
    void display_tree(sf::RenderWindow* window, float scale);
};

#endif