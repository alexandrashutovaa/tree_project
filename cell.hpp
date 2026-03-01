#ifndef _CELL_H_
#define _CELL_H_

#include <chrono>
#include <random>
#include <vector>

float Random();

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
	// cell* getParent(); //������� ������������ ������
	// cell* getRoot(); //������� zero

// protected:
	// virtual void grow() = 0;
	// virtual void produce() = 0;
	// bool createChild(float child_x, float child_y, CellType type);
	// bool isPositionValid(float new_x, float new_y);
};

#endif