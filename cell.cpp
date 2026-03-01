#include "cell.hpp"
#include "producer.hpp"

#include <chrono>
#include <random>
#include <vector>

float Random() {
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 2000);
    return 0.001*(distrib(gen)-1000);
}

cell::cell(Coords coords_, cell* parent_) { //�����������, ��� ��� ������
    alive = true;
    coords = coords_;
    parent = parent_;
    
    if ( parent )
        root = parent->getData().root;
    else
        root = this;
}

cell::~cell() { } //����������

void cell::die() {
    alive = false;
}

DATA cell::getData() {
    DATA data;
    data.alive = this->alive;
	data.coords = this->coords;
	data.parent = this->parent;
    data.root = this->root;
    data.children = this->children;
    return data;
}

/*
bool cell::createChild(float child_x, float child_y, CellType type) {
    if (child_count >= MAX_CHILDREN) return false;

    if (!isPositionValid(child_x, child_y)) return false;

    cell* child = nullptr;

    if (type == CELL_ZERO) {
        child = new root(child_x, child_y);
    }
    else if (type == CELL_STEM) {
        child = new stem(child_x, child_y, this);
    }
    else if (type == CELL_PRODUCER) {
        child = new producer(child_x, child_y, this);
    }

    if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children[child_count] = child;
    child_count++;
    return true;
}
*/

/*
bool cell::isPositionValid(float new_x, float new_y) { //�������� ��� �������� �� ����� ����� � ��� ��� � �������� �� ������
    if (new_x == x && new_y == y) { 
        return false; 
    }

    for (int i = 0; i < child_count; ++i) {
        if (children[i]) {
            if (new_x == children[i]->getData().x && new_y == children[i]->getData().y) {
                return false;
            }
        }
    }

    return true;  // ����� ��������!
}
*/