#include "stem.hpp"
#include "cell.hpp"
#include "rootcell.hpp"

#include <iostream>

stem::stem(Coords coords, cell* parent) : cell(coords, parent) { }

stem::~stem() { }

void stem::tick() {
    if ( this->alive )
        if ( Random() >= 0.8 )
            spread();
    
    for (unsigned int i=0; i < this->children.size(); i++)
        children[i]->tick();
}

void stem::spread() {
    if (children.size() >= 4)
        return;

    rootcell* rootptr = (rootcell*)(this->getData().root);
    if ( ! rootptr->SpendRequest(5, 5) )
        return;

    cell* child;
    float dx = 2*Random();
    float dy = 2*Random();
    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len;
    dy /= len;
    dx *= 2;
    dy *= 2;

    child = new stem({this->getData().coords.x + dx, this->getData().coords.y + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);
}