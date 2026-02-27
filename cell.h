#ifndef _CELL_H_
#define _CELL_H_

const int MAX_CHILDREN = 5;

struct TASK {
	class cell* whereTo;
	unsigned int howMuchE;
	unsigned int howMuchW;
};

struct DATA {
	bool alive;
	float x;
	float y;
	unsigned int E;
	unsigned int W;
	TASK task;
	class cell* parent;
	class cell** children;
	unsigned int child_count;
};

enum CellType {
	CELL_ZERO,
	CELL_STEM,
	CELL_PRODUCER
};

class cell {
private:
	bool alive;
	float x;
	float y;
	unsigned E;
	unsigned W;
	cell* parent;
	cell** children;
	TASK curTask;
	unsigned int child_count;

public:

	cell(float x, float y, cell* parent);
	virtual ~cell();
	DATA getData();
	//void task();
	void tick();
	void die();
	void get(unsigned int e, unsigned int w);
	bool isAlive();
	cell* getParent(); //находит родительскую клетку
	cell* getRoot(); //находит zero

protected:
	virtual void grow() = 0;
	virtual void produce() = 0;
	bool createChild(float child_x, float child_y, CellType type);
	bool isPositionValid(float new_x, float new_y);

};

#endif